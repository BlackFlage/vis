//
// Created by BlackFlage on 01.10.2021.
//

#include "Application.h"
#include <windowsx.h>
#include <GL/wglew.h>
#include <exception>
#include "event/MouseEvent.h"
#include "event/WindowEvent.h"

namespace vis
{
    Application* Application::m_instance = nullptr;
    Window* Application::m_window = nullptr;
    WindowResizeEvent* Application::m_resize_event = nullptr;
    bool Application::m_running = false;
    bool Application::m_gl_context_should_resize = false;

    LRESULT CALLBACK win_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch(uMsg)
        {
            case WM_KEYDOWN:
            {
                KeyPressEvent event((int)wParam);
                Application::get_instance()->on_event(event);
                break;
            }
            case WM_KEYUP:
            {
                KeyReleaseEvent event((int)wParam);
                Application::get_instance()->on_event(event);
                break;
            }
            case WM_LBUTTONUP:
            {
                MouseButtonReleaseEvent event(MK_LBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Application::get_instance()->on_event(event);
                break;
            }
            case WM_RBUTTONUP:
            {
                MouseButtonReleaseEvent event(MK_RBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Application::get_instance()->on_event(event);
                break;
            }
            case WM_LBUTTONDOWN:
            {
                MouseButtonPressEvent event(MK_LBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Application::get_instance()->on_event(event);
                break;
            }
            case WM_RBUTTONDOWN:
            {
                MouseButtonPressEvent event(MK_RBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Application::get_instance()->on_event(event);
                break;
            }
            case WM_MOUSEMOVE:
            {
                MouseMoveEvent event(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Application::get_instance()->on_event(event);
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

                WindowResizeEvent event(new_client_rect);
                Application::set_resize_event(new WindowResizeEvent(new_client_rect));

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

        if(!m_resize_event)
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
            on_update();
        }
    }

    void Application::initialize()
    {
        Logger::initialize();
        char* name = new char[1];
        name[0] = 'A';
        Settings set(720, 750, name);
        m_window = Window::create_window(win_proc, set);

        glDebugMessageControl(GL_DEBUG_SOURCE_WINDOW_SYSTEM, GL_DEBUG_TYPE_OTHER_ARB, 0x826b, 0, nullptr, GL_FALSE);

        m_running = true;
    }

    void Application::on_event(Event &a_event)
    {
        for(const auto& l : m_layer_stack.get_layers())
        {
            l->on_event(a_event);
        }
    }

    void Application::on_update()
    {
        double time_delta = m_timer.get_delta_time();
        while(time_delta > m_refresh_interval) {
            m_window->set_title(std::to_string(time_delta).c_str());

            m_layer_stack.update_all_layers();

            time_delta -= m_refresh_interval;
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
        m_layer_stack.push_layer(a_layer);
    }

    void Application::detach_layer(Layer *a_layer)
    {
        m_layer_stack.detach_layer(a_layer);
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
        Application* app = new Application();

        Application::m_instance = app;

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

        printf(
                "\n*permanent*\nGL_RENDERER: %s\nGL_VENDOR: %s\nGL_VERSION: %s\nGL_SHADING_LANGUAGE_VERSION: %s\nProfile mask: %d\n\n",
                glGetString(GL_RENDERER),
                glGetString(GL_VENDOR),
                glGetString(GL_VERSION),
                glGetString(GL_SHADING_LANGUAGE_VERSION),
                profile_mask
        );

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(opengl_error_callback, 0);

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
        glClearColor(0.5f, 0.0f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        SwapBuffers(context->m_hdc);
        ShowWindow(context->m_hwnd, 1);

        Application::get_instance()->m_layer_stack.on_attach_layers();

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
}


