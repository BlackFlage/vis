//
// Created by BlackFlage on 01.10.2021.
//

#include "Window.h"
#include <windowsx.h>
#include <string>
#include <iostream>
#include "KeyboardEvent.h"
#include "MouseEvent.h"

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
        DestroyWindow(m_window_data.m_hwnd);
    }

    Window *Window::create_window(int a_width, int a_height, const char* a_name)
    {
        const char className[] = "Sample Window";

        WNDCLASS wndClass = {};

        HINSTANCE hInstance = GetModuleHandleA(nullptr);

        wndClass.lpfnWndProc = window_proc;
        wndClass.hInstance = hInstance;
        wndClass.lpszClassName = className;

        RegisterClassA(&wndClass);

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


        return new Window({a_width, a_height, hwnd, nullptr});
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
}