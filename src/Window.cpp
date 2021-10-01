//
// Created by BlackFlage on 01.10.2021.
//

#include "Window.h"
#include "string"

namespace vis
{
    LRESULT CALLBACK window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch(uMsg)
        {
            case WM_QUIT:
                DestroyWindow(hwnd);
                PostQuitMessage(0);
                return 0;
            default:
                return DefWindowProcA(hwnd, uMsg, wParam, lParam);
        }
        return 0;
    }

    Window::Window(int a_width, int a_height, HWND a_hwnd)
    : m_width(a_width), m_height(a_height), m_hwnd(a_hwnd)
    {

    }

    Window::~Window()
    {

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


        return new Window(a_width, a_height, hwnd);
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
}