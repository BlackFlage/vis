//
// Created by BlackFlage on 03.12.2021.
//

#ifndef MAIN_IMGUILAYER_H
#define MAIN_IMGUILAYER_H

#include "Layer.h"
#include "ImGui/imgui.h"

namespace vis
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer() = default;
        ~ImGuiLayer() override = default;
        void on_attach() override;
        void on_detach() override;

        void on_event(Event& a_event) override;
        void on_update(float a_delta_time) override;
        void on_render() override;
        void on_imgui_render() override;

    private:
        void on_char_input(CharInputEvent& a_event);
        void on_key_press_event(KeyPressEvent& a_event);
        void on_key_release_event(KeyReleaseEvent& a_event);
        void on_window_resize_event(WindowResizeEvent& a_event);
        void on_window_focus_event(WindowFocusEvent& a_event);
        void on_scroll_event(MouseScrollEvent& a_event);
        void on_mouse_button_press_event(MouseButtonPressEvent& a_event);
        void on_mouse_button_release_event(MouseButtonReleaseEvent& a_event);
        void update_mouse_pos();

        ImFont* m_current_font;
    };
}

#endif //MAIN_IMGUILAYER_H
