//
// Created by BlackFlage on 01.10.2021.
//

#include "Window.h"
#include <windowsx.h>
#include <string>
#include <gl/GL.h>
#include "wglext.h"
#include "Macro.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"

typedef HGLRC WINAPI wglCreateContextAttribsARB_type(HDC a_hdc, HGLRC a_hShareContext, const int* a_attribList);
wglCreateContextAttribsARB_type* wglCreateContextAttribsARB;

typedef BOOL WINAPI wglChoosePixelFormatARB_type(HDC a_hdc, const int* a_attribList, const FLOAT* a_attribFList, UINT a_nMaxFormats, int* a_piFormats, UINT* a_nNumFormats);
wglChoosePixelFormatARB_type* wglChoosePixelFormatARB;

#define WGL_DRAW_TO_WINDOW_ARB                    0x2001
#define WGL_ACCELERATION_ARB                      0x2003
#define WGL_SUPPORT_OPENGL_ARB                    0x2010
#define WGL_DOUBLE_BUFFER_ARB                     0x2011
#define WGL_PIXEL_TYPE_ARB                        0x2013
#define WGL_COLOR_BITS_ARB                        0x2014
#define WGL_DEPTH_BITS_ARB                        0x2022
#define WGL_STENCIL_BITS_ARB                      0x2023

#define WGL_FULL_ACCELERATION_ARB                 0x2027
#define WGL_TYPE_RGBA_ARB                         0x202B

namespace vis
{
    Window_Data Window::m_window_data;

    LRESULT CALLBACK window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch(uMsg)
        {
            case WM_KEYDOWN:
            {
                KeyPressEvent event((int)wParam);
                Window::get_window_data().m_window_callback(event);
                break;
            }
            case WM_KEYUP:
            {
                KeyReleaseEvent event((int)wParam);
                Window::get_window_data().m_window_callback(event);
                break;
            }
            case WM_LBUTTONUP:
            {
                MouseButtonReleaseEvent event(MK_LBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Window::get_window_data().m_window_callback(event);
                break;
            }
            case WM_RBUTTONUP:
            {
                MouseButtonReleaseEvent event(MK_RBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Window::get_window_data().m_window_callback(event);
                break;
            }
            case WM_LBUTTONDOWN:
            {
                MouseButtonPressEvent event(MK_LBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Window::get_window_data().m_window_callback(event);
                break;
            }
            case WM_RBUTTONDOWN:
            {
                MouseButtonPressEvent event(MK_RBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Window::get_window_data().m_window_callback(event);
                break;
            }
            case WM_MOUSEMOVE:
            {
                MouseMoveEvent event(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Window::get_window_data().m_window_callback(event);
                break;
            }
            case WM_MBUTTONUP:
            {
                MouseButtonReleaseEvent event(MK_MBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Window::get_window_data().m_window_callback(event);
                break;
            }
            case WM_MBUTTONDOWN:
            {
                MouseButtonPressEvent event(MK_MBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Window::get_window_data().m_window_callback(event);
                break;
            }
            case WM_XBUTTONDOWN:
            {
                MouseButtonPressEvent event(GET_XBUTTON_WPARAM(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Window::get_window_data().m_window_callback(event);
                break;
            }
            case WM_XBUTTONUP:
            {
                MouseButtonReleaseEvent event(GET_XBUTTON_WPARAM(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Window::get_window_data().m_window_callback(event);
                break;
            }
            case WM_MOUSEWHEEL:
            {
                MouseScrollEvent event(GET_WHEEL_DELTA_WPARAM(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Window::get_window_data().m_window_callback(event);
                break;
            }
            case WM_CLOSE:
            {
                PostQuitMessage(APPLICATION_CLOSED);
                break;
            }
        }

        return DefWindowProcA(hwnd, uMsg, wParam, lParam);
    }

    Window::Window(const Window_Data& a_window_data)
    {
        m_window_data = a_window_data;
    }

    Window::~Window()
    {
        wglDeleteContext(m_window_data.m_hglrc);
        ReleaseDC(m_window_data.m_hwnd, m_window_data.m_hdc);
        DestroyWindow(m_window_data.m_hwnd);
    }

    Window *Window::create_window(int a_width, int a_height, const char* a_name)
    {
        HWND hwnd = create_window_handler(a_width, a_height, a_name);
        HDC hdc = GetDC(hwnd);
        HGLRC hglrc = initialize_opengl(hdc);

        UpdateWindow(hwnd);

        return new Window({a_width, a_height, hwnd, hdc, hglrc, nullptr});
    }

    std::optional<int> Window::pull_events()
    {
        MSG msg;

        while(PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
        {
            if(msg.message == WM_QUIT)
            {
                return msg.wParam;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return {};
    }

    void Window::change_title(const char* a_title)
    {
        SetWindowTextA(m_window_data.m_hwnd, a_title);
    }

    void Window::initialize_opengl_extensions()
    {
        WNDCLASS tempClass = {
                .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
                .lpfnWndProc = DefWindowProcA,
                .hInstance = GetModuleHandleA(NULL),
                .lpszClassName = "Temp_wnd_class"
        };

        ASSERT(RegisterClassA(&tempClass), "Failed to register temp window class");

        HWND tempWindow = CreateWindowExA(
                0,
                tempClass.lpszClassName,
                "Temp window",
                0,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                0,
                0,
                tempClass.hInstance,
                0);

        ASSERT(tempWindow, "Failed to create temp window!");

        HDC temp_hdc = GetDC(tempWindow);

        PIXELFORMATDESCRIPTOR pfd = {
                .nSize = sizeof(pfd),
                .nVersion = 1,
                .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                .iPixelType = PFD_TYPE_RGBA,
                .cColorBits = 32,
                .cAlphaBits = 8,
                .cDepthBits = 24,
                .cStencilBits = 8,
                .iLayerType = PFD_MAIN_PLANE,
        };

        int pixel_format = ChoosePixelFormat(temp_hdc, &pfd);

        ASSERT(pixel_format, "Failed to find suitable pixel format.")
        ASSERT(SetPixelFormat(temp_hdc, pixel_format, &pfd), "Failed to set pixel format.")

        HGLRC temp_context = wglCreateContext(temp_hdc);
        ASSERT(temp_context, "Failed to create temp OpenGL context.")
        ASSERT(wglMakeCurrent(temp_hdc, temp_context), "Failed to set temp context as current.")

        wglCreateContextAttribsARB = (wglCreateContextAttribsARB_type*)wglGetProcAddress("wglCreateContextAttribsARB");
        wglChoosePixelFormatARB = (wglChoosePixelFormatARB_type*) wglGetProcAddress("wglChoosePixelFormatARB");

        wglMakeCurrent(temp_hdc, 0);
        wglDeleteContext(temp_context);
        ReleaseDC(tempWindow, temp_hdc);
        DestroyWindow(tempWindow);
    }

    HGLRC Window::initialize_opengl(HDC a_hdc)
    {
        initialize_opengl_extensions();

        int pixel_format_attribs[] = {
                WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
                WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
                WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
                WGL_COLOR_BITS_ARB, 32,
                WGL_DEPTH_BITS_ARB, 24,
                WGL_STENCIL_BITS_ARB, 8,
                0
        };

        int pixel_format;
        UINT num_formats;
        wglChoosePixelFormatARB(a_hdc, pixel_format_attribs, 0, 1, &pixel_format, &num_formats);
        ASSERT(num_formats, "Failed to set OpenGL 3.3 pixel format.");

        PIXELFORMATDESCRIPTOR pfd;
        DescribePixelFormat(a_hdc, pixel_format, sizeof(pfd), &pfd);
        ASSERT(SetPixelFormat(a_hdc, pixel_format, &pfd), "Failed to set pixel format.");

        int gl33_attribs[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                WGL_CONTEXT_MINOR_VERSION_ARB, 3,
                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                0,
        };

        HGLRC gl33_context = wglCreateContextAttribsARB(a_hdc, 0, gl33_attribs);
        ASSERT(gl33_context, "Failed to create OpenGL 3.3 context.");
        ASSERT(wglMakeCurrent(a_hdc, gl33_context), "Failed to make OpenGL 3.3 context current.");

        return gl33_context;
    }

    HWND Window::create_window_handler(int a_width, int a_height, const char *a_name)
    {
        const char className[] = "Sample Window";

        HINSTANCE hInstance = GetModuleHandleA(nullptr);

        WNDCLASS wndClass = {
                .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
                .lpfnWndProc = window_proc,
                .hInstance = hInstance,
                .hCursor = LoadCursorA(0, IDC_ARROW),
                .hbrBackground = 0,
                .lpszClassName = className
        };

        ASSERT(RegisterClassA(&wndClass), "Failed to register window class.");

        HWND hwnd = CreateWindowExA(
                0,
                className,
                a_name,
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, a_width, a_height,
                nullptr,
                nullptr,
                hInstance,
                nullptr
        );


        return hwnd;
    }
}