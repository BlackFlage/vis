//
// Created by BlackFlage on 01.10.2021.
//

#include "Application.h"
#include <GL/wglew.h>
#include <exception>

#include "managers/ResourcesManager.h"
#include "TPool.h"
#include "ImGui/imgui_impl_opengl3.h"

namespace vis
{
    Application*       Application::m_instance;
    Window*            Application::m_window;
    WindowResizeEvent* Application::m_resize_event;
    Input*             Application::m_input;
    bool               Application::m_running;
    bool               Application::m_gl_context_should_resize;
    bool               Application::m_opengl_initialized;
    bool               Application::m_layers_attached;
    bool               Application::m_minimized;

    Application::Application()
    {
        recalculate_refresh_interval();
    }

    Application::~Application()
    {
        m_layer_stack.clear_stack();
        m_global_register->shut_down_managers();
        TPool::shutdown();

        delete m_window;
        delete m_resize_event;
    }

    void Application::run()
    {
        std::optional<int> windowRetValue;

        start_opengl_thread();
        while(windowRetValue != APPLICATION_CLOSED && m_running)
        {
            windowRetValue = m_window->pull_events();

            if(m_layers_attached)
            {
                on_update();
            }
        }
    }

    void Application::initialize()
    {
        m_window                   = nullptr;
        m_resize_event             = nullptr;
        m_running                  = false;
        m_gl_context_should_resize = false;
        m_opengl_initialized       = false;
        m_layers_attached          = false;
        m_minimized                = false;
        m_main_window_open         = true;
        m_refresh_rate             = 60.0f;
        m_refresh_interval         = 0.0f;

        m_window           = Window::create_window({1920, 1080, "Shark"});
        m_global_register  = std::make_unique<GlobalRegister>();
        m_input            = new Input(0.0f, 0.0f);

        if(!m_window)
        {
            LOG_ERROR("Failed to initialize application!");
            return;
        }

        TPool::initialize();

        INPUT->reset_states();
        recalculate_refresh_interval();
        m_global_register->register_manager(ResourcesManager::get());

        m_global_register->start_up_managers();

        m_running = true;
    }

    void Application::on_event(Event& a_event)
    {
        EventDispatcher dispatcher(a_event);
        dispatcher.dispatch<KeyPressEvent>([this](auto&& event) { on_key_press_event(std::forward<decltype(event)>(event)); });

        if(m_opengl_initialized)
        {
            for(const auto& l : m_layer_stack.get_layers())
            {
                l->on_event(a_event);
            }
        }
    }

    void Application::on_update()
    {
        float delta_time = m_timer.get_delta_time();
        while(delta_time > m_refresh_interval) {
            POINT cursor_pos;
            if(GetCursorPos(&cursor_pos))
            {
                m_input->set_mouse_pos(cursor_pos.x, cursor_pos.y);
            }

            m_layer_stack.update_all_layers(delta_time);

            delta_time -= m_refresh_interval;
            m_timer.new_time_stamp();
        }
    }

    void Application::on_render()
    {
        if(!m_minimized)
        {
            for(const auto& layer : m_layer_stack.get_layers())
            {
                layer->on_render();
            }
        }
    }

    void Application::push_layer(Layer *a_layer)
    {
        if(a_layer != nullptr)
        {
            m_layer_stack.push_layer(a_layer);
        }
        else
        {
            LOG_ERROR("Failed to push layer! Layer can't be nullptr.");
        }
    }

    void Application::detach_layer(Layer *a_layer)
    {
        if(a_layer != nullptr)
        {
            m_layer_stack.detach_layer(a_layer);
        }
        else
        {
            LOG_ERROR("Failed to detach layer. Layer can't be nullptr!");
        }
    }

    void Application::recalculate_refresh_interval()
    {
        m_refresh_interval = 1.0f / m_refresh_rate;
    }

    void Application::set_refresh_interval(int a_refresh_rate)
    {
        if(a_refresh_rate > 24)
            m_refresh_rate = a_refresh_rate;

        recalculate_refresh_interval();
    }

    Application *Application::create_instance()
    {
        if(m_instance != nullptr)
        {
            LOG_WARNING("Trying to create instance of application more than once!");
            return m_instance;
        }

        Application::m_instance = new Application();
        Logger::initialize();

        return m_instance;
    }

    void Application::start_opengl_thread()
    {
        DWORD ogl_thread_id = 0;
        Context* context = m_window->get_context();
        HANDLE ogl_thread = CreateThread(
                nullptr,
                0,
                opengl_thread,
                context,
                0,
                &ogl_thread_id
                );

        ASSERT(ogl_thread_id, "Failed to create OpenGL thread!");

        WaitForSingleObject(ogl_thread, 0);
    }

    DWORD Application::opengl_thread(LPVOID a_param)
    {
        auto context = (Context*) a_param;
        wglMakeCurrent(context->m_hdc, context->m_hglrc);

        GLint profile_mask = 0;
        glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile_mask);

        LOG_INFO("\nGL_RENDERER: {0}\nGL_VENDOR: {1}\nGL_VERSION: {2}\nGL_SHADING_LANGUAGE_VERSION: {3}\nProfile mask: {4}\n\n",
                 glGetString(GL_RENDERER),
                 glGetString(GL_VENDOR),
                 glGetString(GL_VERSION),
                 glGetString(GL_SHADING_LANGUAGE_VERSION),
                 profile_mask);

        glEnable(GL_DEBUG_OUTPUT);

        wglSwapIntervalEXT(1);

        glEnable(GL_LINE_SMOOTH);
        glLineWidth(0.2f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_BLEND);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        RECT contextRect;
        GetClientRect(m_window->get_context()->m_hwnd, &contextRect);

        glViewport(0, 0, contextRect.right, contextRect.bottom);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        SwapBuffers(context->m_hdc);
        ShowWindow(context->m_hwnd, 1);

        Application::get_instance()->m_layer_stack.on_attach_layers();
        Application::m_opengl_initialized = true;
        Application::m_layers_attached = true;
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

        Application::get_instance()->m_scene_framebuffer = std::make_unique<Framebuffer>(contextRect.right, contextRect.bottom);
        CheckGLError();

        while(Application::is_running())
        {
            if(m_gl_context_should_resize)
            {
                on_resize_event(*m_resize_event);
            }

            if(!Application::get_instance()->is_minimized())
            {
                Application::get_instance()->m_scene_framebuffer->bind();

                glEnable(GL_DEPTH_TEST);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

                //Render
                Application::get_instance()->on_render();

                Application::get_instance()->m_scene_framebuffer->unbind();

                glDisable(GL_DEPTH_TEST);

                Application::get_instance()->on_imgui_render();

                glEnable(GL_DEPTH_TEST);

                //Flush and swap buffers
                glFlush();
                SwapBuffers(context->m_hdc);
            }
        }

        return 0;
    }

    void Application::on_resize_event(WindowResizeEvent& a_event)
    {
        if(a_event.get_width() < 0 || a_event.get_height() < 0)
        {
            LOG_ERROR("Invalid OpenGL context size!");
        }

        glViewport(0, 0, a_event.get_width(), a_event.get_height());

        delete m_resize_event;

        m_gl_context_should_resize = false;
        m_resize_event = nullptr;
    }

    void Application::set_resize_event(WindowResizeEvent *a_event)
    {
        m_resize_event = a_event;
        m_gl_context_should_resize = true;
    }

    void Application::on_imgui_render()
    {
        ImGuiIO& io = ImGui::GetIO();

        float dt = get_delta_time();
        if(dt > 0.0f)
        {
            io.DeltaTime = dt;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        const auto& layers = m_layer_stack.get_layers();
        std::for_each(layers.begin(), layers.end(), [](Layer* a_layer) { a_layer->on_imgui_render(); });

        ImGui::PopFont();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Application::on_key_press_event(KeyPressEvent &a_event)
    {
        if(a_event.get_key_code() == 'F')
        {
            m_window->set_show_cursor(!m_window->get_show_cursor());
        }
    }

    void Application::paint_custom_caption(HWND m_hwnd, HDC m_hdc)
    {
        RECT rcClient;
        GetClientRect(m_hwnd, &rcClient);
        //HTHEME hTheme = OpenThemeData(nullptr, L"CompositedWindow::Window");
    }
}