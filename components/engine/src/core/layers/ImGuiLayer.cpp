//
// Created by BlackFlage on 03.12.2021.
//

#include <Windows.h>

#include "ImGuiLayer.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Application.h"
#include "ColorSchemeEditor.h"

namespace vis
{

    void ImGuiLayer::on_attach()
    {
        const char* glsl_version = "#version 330 core";

        IMGUI_CHECKVERSION();
        ImGuiContext* im_gui_context = ImGui::CreateContext();
        ImGui::SetCurrentContext(im_gui_context);

        ImGui_ImplOpenGL3_Init(glsl_version);

        RECT client_area = Application::get_window_instance()->get_client_rect();

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)client_area.right, (float)client_area.bottom);
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.ConfigWindowsResizeFromEdges = true;

        io.KeyMap[ImGuiKey_Tab] = VK_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = VK_UP;
        io.KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = VK_PRIOR;
        io.KeyMap[ImGuiKey_PageDown] = VK_NEXT;
        io.KeyMap[ImGuiKey_Home] = VK_HOME;
        io.KeyMap[ImGuiKey_End] = VK_END;
        io.KeyMap[ImGuiKey_Insert] = VK_INSERT;
        io.KeyMap[ImGuiKey_Delete] = VK_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = VK_BACK;
        io.KeyMap[ImGuiKey_Space] = VK_SPACE;
        io.KeyMap[ImGuiKey_Enter] = VK_RETURN;
        io.KeyMap[ImGuiKey_Escape] = VK_ESCAPE;
        io.KeyMap[ImGuiKey_A] = 0x41;
        io.KeyMap[ImGuiKey_C] = 0x43;
        io.KeyMap[ImGuiKey_V] = 0x56;
        io.KeyMap[ImGuiKey_X] = 0x58;
        io.KeyMap[ImGuiKey_Y] = 0x59;
        io.KeyMap[ImGuiKey_Z] = 0x5A;

        ImGui::StyleColorsDark();
        auto& style = ImGui::GetStyle();

        ColorSchemeEditor::set_theme(themes::DEFAULT);

        style.Alpha = 1.0f;

        style.FrameBorderSize = 1.0f;
        style.ChildBorderSize = 4.0f;
        style.ScrollbarSize = 13.0f;
        style.TabBorderSize = 1.0f;
        style.GrabMinSize = 7.0f;

        style.ScrollbarRounding = 12.0f;
        style.FrameRounding = 0.0f;
        style.PopupRounding = 0.5f;
        style.TabRounding = 0.0f;
        style.WindowRounding = 0.0f;

        style.ItemSpacing = ImVec2(6.0f, 2.0f);
        style.FramePadding = ImVec2(6.0f, 4.0f);
        style.WindowPadding = ImVec2(4.0f, 4.0f);

        m_current_font = io.Fonts->AddFontFromFileTTF("..\\engine_assets\\fonts\\TwCenMTStd-Light.ttf", 12.0f);
        io.Fonts->Build();
    }

    void ImGuiLayer::on_detach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        delete m_current_font;
    }

    void ImGuiLayer::on_event(Event &a_event)
    {
        EventDispatcher dispatcher(a_event);
        dispatcher.dispatch<CharInputEvent>([this](auto&& event) { on_char_input(std::forward<decltype(event)>(event)); });
        dispatcher.dispatch<KeyPressEvent>([this](auto&& event) { on_key_press_event(std::forward<decltype(event)>(event)); });
        dispatcher.dispatch<KeyReleaseEvent>([this](auto&& event) { on_key_release_event(std::forward<decltype(event)>(event)); });
        dispatcher.dispatch<WindowResizeEvent>([this](auto&& event) { on_window_resize_event(std::forward<decltype(event)>(event)); });
        dispatcher.dispatch<WindowFocusEvent>([this](auto&& event) { on_window_focus_event(std::forward<decltype(event)>(event)); });
        dispatcher.dispatch<MouseScrollEvent>([this](auto&& event) { on_scroll_event(std::forward<decltype(event)>(event)); });
        dispatcher.dispatch<MouseButtonPressEvent>([this](auto&& event) { on_mouse_button_press_event(std::forward<decltype(event)>(event)); });
        dispatcher.dispatch<MouseButtonReleaseEvent>([this](auto&& event) { on_mouse_button_release_event(std::forward<decltype(event)>(event)); });
    }

    void ImGuiLayer::on_update(float a_delta_time)
    {
        update_mouse_pos();
    }

    void ImGuiLayer::on_render()
    {

    }

    void ImGuiLayer::on_imgui_render()
    {
        ImGui::PushFont(m_current_font);
    }

    void ImGuiLayer::on_char_input(CharInputEvent &a_event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharacter(a_event.get_char());
    }

    void ImGuiLayer::on_key_press_event(KeyPressEvent &a_event)
    {
        ImGuiIO& io = ImGui::GetIO();

        const int& key = a_event.get_key_code();
        if(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown))
        {
            io.KeysDown[key] = true;
        }
    }

    void ImGuiLayer::on_key_release_event(KeyReleaseEvent& a_event)
    {
        ImGuiIO& io = ImGui::GetIO();

        const int& key = a_event.get_key_code();
        if(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown))
        {
            io.KeysDown[key] = false;
        }
    }

    void ImGuiLayer::update_mouse_pos()
    {
        ImGuiIO& io = ImGui::GetIO();

        POINT to_convert = {INPUT->get_mouse_pos_x(), INPUT->get_mouse_pos_y()};
        ScreenToClient(Application::get_window_instance()->get_context()->m_hwnd, &to_convert);
        io.MousePos = ImVec2(to_convert.x, to_convert.y);
    }

    void ImGuiLayer::on_window_resize_event(WindowResizeEvent &a_event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)a_event.get_width(), (float)a_event.get_height());
    }

    void ImGuiLayer::on_window_focus_event(WindowFocusEvent& a_event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddFocusEvent(a_event.is_focused());
    }

    void ImGuiLayer::on_scroll_event(MouseScrollEvent& a_event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheel += a_event.get_offset() / 120.0f;
    }

    void ImGuiLayer::on_mouse_button_press_event(MouseButtonPressEvent& a_event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[a_event.get_button() - 1] = true;
    }

    void ImGuiLayer::on_mouse_button_release_event(MouseButtonReleaseEvent& a_event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[a_event.get_button() - 1] = false;
    }
}