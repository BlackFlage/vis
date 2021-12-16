//
// Created by BlackFlage on 01.10.2021.
//

#include "Application.h"
#include <windowsx.h>
#include <GL/wglew.h>
#include <exception>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"

namespace vis
{
    Application* Application::m_instance = nullptr;
    Window* Application::m_window = nullptr;
    WindowResizeEvent* Application::m_resize_event = nullptr;
    Input* Application::m_input = nullptr;
    bool Application::m_running = false;
    bool Application::m_gl_context_should_resize = false;
    bool Application::m_opengl_initialized = false;
    bool Application::m_layers_attached = false;

    LRESULT CALLBACK win_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch(uMsg)
        {
            case WM_KEYDOWN:
            {
                KeyPressEvent event((int)wParam);
                Application::get_instance()->on_event(event);
                LOG_INFO(event.get_name());
                break;
            }
            case WM_KEYUP:
            {
                KeyReleaseEvent event((int)wParam);
                Application::get_instance()->on_event(event);
                break;
            }
            case WM_CHAR:
            {
                CharInputEvent event((char)wParam);
                Application::get_instance()->on_event(event);
                break;
            }
            case WM_LBUTTONUP:
            {
                MouseButtonReleaseEvent event(MK_LBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Application::get_instance()->on_event(event);
                INPUT->set_button_state(0, false);
                break;
            }
            case WM_RBUTTONUP:
            {
                MouseButtonReleaseEvent event(MK_RBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Application::get_instance()->on_event(event);
                INPUT->set_button_state(1, false);
                break;
            }
            case WM_LBUTTONDOWN:
            {
                MouseButtonPressEvent event(MK_LBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Application::get_instance()->on_event(event);
                INPUT->set_button_state(0, true);

                break;
            }
            case WM_RBUTTONDOWN:
            {
                MouseButtonPressEvent event(MK_RBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Application::get_instance()->on_event(event);
                INPUT->set_button_state(1, true);

                break;
            }
            case WM_MOUSEMOVE:
            {
                POINT mouse_point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

                MouseMoveEvent event(mouse_point.x, mouse_point.y);
                Application::get_instance()->on_event(event);

                if(!Application::get_window_instance()->get_show_cursor())
                {
                    POINT client_center = Application::get_window_instance()->get_client_center();
                    if(!SetCursorPos(client_center.x, client_center.y))
                    {
                        LOG_ERROR("Failed to set cursor position!");
                        break;
                    }
                }

                break;
            }
            case WM_MBUTTONUP:
            {
                MouseButtonReleaseEvent event(MK_MBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Application::get_instance()->on_event(event);
                break;
            }
            case WM_MBUTTONDOWN:
            {
                MouseButtonPressEvent event(MK_MBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Application::get_instance()->on_event(event);
                break;
            }
            case WM_XBUTTONDOWN:
            {
                MouseButtonPressEvent event(GET_XBUTTON_WPARAM(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Application::get_instance()->on_event(event);
                break;
            }
            case WM_XBUTTONUP:
            {
                MouseButtonReleaseEvent event(GET_XBUTTON_WPARAM(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Application::get_instance()->on_event(event);
                break;
            }
            case WM_MOUSEWHEEL:
            {
                MouseScrollEvent event(GET_WHEEL_DELTA_WPARAM(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Application::get_instance()->on_event(event);
                break;
            }
            case WM_CLOSE:
            {
                Application::set_running(false);
                PostQuitMessage(APPLICATION_CLOSED);
                break;
            }
            case WM_SIZE:
            {
                RECT new_client_rect;

                GetClientRect(Application::get_window_instance()->get_context()->m_hwnd, &new_client_rect);

                WindowResizeEvent* event = new WindowResizeEvent(new_client_rect);
                Application::get_instance()->on_event(*event);
                Application::set_resize_event(event);

                break;
            }
            case WM_SETFOCUS:
            {
                WindowFocusEvent event(false);
                Application::get_instance()->on_event(event);

                break;
            }
            case WM_KILLFOCUS:
            {
                WindowFocusEvent event(true);
                Application::get_instance()->on_event(event);

                break;
            }
        }

        return DefWindowProcA(hwnd, uMsg, wParam, lParam);
    }

    void GLAPIENTRY opengl_error_callback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam )
    {
        fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
                (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
                type, severity, message);
    }

    Application::Application()
    {
        recalculate_refresh_interval();
    }

    Application::~Application()
    {
        m_layer_stack.clear_stack();
        delete m_window;

        if(m_resize_event)
        {
            delete m_resize_event;
        }
    }

    void Application::run()
    {
        std::optional<int> windowRetValue;

        start_opengl_thread();
        while(windowRetValue != APPLICATION_CLOSED)
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
        m_window = Window::create_window(win_proc, {720, 750, "App"});

        if(!m_window)
        {
            LOG_ERROR("Failed to initialize application!");
            return;
        }

        POINT cursor_pos;
        GetCursorPos(&cursor_pos);

        m_input = new Input((float)cursor_pos.x, (float)cursor_pos.y);
        m_running = true;

        LOG_INFO("Successfully initialized application!");
    }

    void Application::on_event(Event& a_event)
    {
        EventDispatcher dispatcher(a_event);
        dispatcher.dispatch<MouseMoveEvent>([this](auto&& event) { update_input_data(std::forward<decltype(event)>(event)); });
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
            m_window->set_title(std::to_string(delta_time).c_str());

            m_layer_stack.update_all_layers(delta_time);

            delta_time -= m_refresh_interval;
            m_timer.new_time_stamp();
        }
    }

    void Application::on_render()
    {
        for(const auto& layer : m_layer_stack.get_layers())
        {
            layer->on_render();
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
        m_refresh_interval = 1.0 / m_refresh_rate;
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
            return nullptr;
        }

        Application* app = new Application();
        Application::m_instance = app;
        Logger::initialize();

        return app;
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
        //glDebugMessageCallback(opengl_error_callback, 0);

        wglSwapIntervalEXT(1);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        while(Application::is_running())
        {
            if(m_gl_context_should_resize)
            {
                on_resize_event(*m_resize_event);
            }

            //Clear
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            //Render
            Application::get_instance()->on_render();
            Application::get_instance()->on_imgui_render();

            //Flush and swap buffers
            glFlush();
            SwapBuffers(context->m_hdc);
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

    void Application::update_input_data(MouseMoveEvent &a_event)
    {
        m_input->set_mouse_pos(a_event.get_x_pos(), a_event.get_y_pos());
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

        const auto& layers = m_layer_stack.get_layers();
        std::for_each(layers.begin(), layers.end(), [](Layer* a_layer) { a_layer->on_imgui_render(); });

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
}