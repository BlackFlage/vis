//
// Created by BlackFlage on 04.01.2022.
//

#include <cmath>
#include "ColorSchemeEditor.h"

namespace vis
{
    float ColorSchemeEditor::get_R(unsigned int color)
    {
        return (float)((color & 0xFF000000) >> 24) / float(0xFF);
    }

    float ColorSchemeEditor::get_G(unsigned int color)
    {
        return (float)((color & 0x00FF0000) >> 16) / float(0xFF);
    }

    float ColorSchemeEditor::get_B(unsigned int color)
    {
        return (float)((color & 0x0000FF00) >> 8) / float(0xFF);
    }

    float ColorSchemeEditor::get_alpha(unsigned int alpha)
    {
        return (float)alpha / (float)0xFF;
    }

    ImVec4 ColorSchemeEditor::get_color(unsigned int color, unsigned int alpha)
    {
        return ImVec4(get_R(color), get_G(color), get_B(color), get_alpha(alpha));
    }

    void ColorSchemeEditor::set_theme(Theme theme)
    {
        set_theme(theme.background, theme.text, theme.main_theme, theme.accent, theme.plot_lines);
        m_current_theme = theme;
    }

    void ColorSchemeEditor::set_theme(unsigned int background, unsigned int text, unsigned int main_theme, unsigned int accent, unsigned int plot_lines)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        ImVec4 white_100 = get_color(m_white, m_alpha_100);

        colors[ImGuiCol_Text]                   = get_color(text, m_alpha_100);
        colors[ImGuiCol_TextDisabled]           = get_color(text, m_alpha_40);
        colors[ImGuiCol_WindowBg]               = get_color(background, m_alpha_100);
        colors[ImGuiCol_ChildBg]                = get_color(background, m_alpha_100);
        colors[ImGuiCol_PopupBg]                = mix(get_color(background, m_alpha_100), get_color(main_theme, m_alpha_100));
        colors[ImGuiCol_Border]                 = get_color(main_theme, m_alpha_100);
        colors[ImGuiCol_BorderShadow]           = get_color(accent, m_alpha_0);
        colors[ImGuiCol_FrameBg]                = get_color(main_theme, m_alpha_100);
        colors[ImGuiCol_FrameBgHovered]         = get_color(main_theme, m_alpha_100);
        colors[ImGuiCol_FrameBgActive]          = get_color(background, m_alpha_100);
        colors[ImGuiCol_TitleBg]                = get_color(background, m_alpha_100);
        colors[ImGuiCol_TitleBgActive]          = get_color(background, m_alpha_100);
        colors[ImGuiCol_TitleBgCollapsed]       = get_color(background, m_alpha_100);
        colors[ImGuiCol_MenuBarBg]              = get_color(main_theme, m_alpha_100);
        colors[ImGuiCol_ScrollbarBg]            = get_color(background, m_alpha_100);
        colors[ImGuiCol_ScrollbarGrab]          = get_color(main_theme, m_alpha_100);
        colors[ImGuiCol_ScrollbarGrabHovered]   = get_color(main_theme, m_alpha_80);
        colors[ImGuiCol_ScrollbarGrabActive]    = get_color(main_theme, m_alpha_60);
        colors[ImGuiCol_CheckMark]              = get_color(m_white, m_alpha_40);
        colors[ImGuiCol_SliderGrab]             = get_color(accent, m_alpha_100);
        colors[ImGuiCol_SliderGrabActive]       = get_color(accent, m_alpha_60);
        colors[ImGuiCol_Button]                 = get_color(main_theme, m_alpha_100);
        colors[ImGuiCol_ButtonHovered]          = get_color(accent, m_alpha_100);
        colors[ImGuiCol_ButtonActive]           = get_color(accent, m_alpha_100);
        colors[ImGuiCol_HeaderHovered]          = get_color(accent, m_alpha_100);
        colors[ImGuiCol_HeaderActive]           = get_color(accent, m_alpha_100);
        colors[ImGuiCol_Header]                 = get_color(main_theme, m_alpha_90);
        colors[ImGuiCol_SeparatorHovered]       = get_color(main_theme, m_alpha_90);
        colors[ImGuiCol_SeparatorActive]        = get_color(main_theme, m_alpha_80);
        colors[ImGuiCol_ResizeGrip]             = white_100;
        colors[ImGuiCol_ResizeGripHovered]      = get_color(main_theme, m_alpha_100);
        colors[ImGuiCol_ResizeGripActive]       = get_color(main_theme, m_alpha_80);
        colors[ImGuiCol_Tab]                    = get_color(main_theme, m_alpha_100);
        colors[ImGuiCol_TabHovered]             = get_color(main_theme, m_alpha_60);
        colors[ImGuiCol_TabActive]              = get_color(main_theme, m_alpha_40);
        colors[ImGuiCol_TabUnfocused]           = get_color(main_theme, m_alpha_100);
        colors[ImGuiCol_TabUnfocusedActive]     = get_color(main_theme, m_alpha_100);
        colors[ImGuiCol_DockingPreview]         = mix(get_color(m_black, m_alpha_100), get_color(main_theme, m_alpha_100));
        colors[ImGuiCol_DockingEmptyBg]         = get_color(main_theme, m_alpha_90);
        colors[ImGuiCol_PlotLines]              = get_color(plot_lines, m_alpha_100);
        colors[ImGuiCol_PlotLinesHovered]       = white_100;
        colors[ImGuiCol_PlotHistogram]          = white_100;
        colors[ImGuiCol_PlotHistogramHovered]   = white_100;
        colors[ImGuiCol_TableHeaderBg]          = get_color(accent, m_alpha_100);
        colors[ImGuiCol_TableBorderStrong]      = get_color(main_theme, m_alpha_100);   // Prefer using Alpha=1.0 here
        colors[ImGuiCol_TableBorderLight]       = get_color(main_theme, m_alpha_80);   // Prefer using Alpha=1.0 here
        colors[ImGuiCol_TableRowBg]             = get_color(background, m_alpha_100);
        colors[ImGuiCol_TableRowBgAlt]          = get_color(background, m_alpha_80);
        colors[ImGuiCol_TextSelectedBg]         = get_color(m_white, m_alpha_40);
        colors[ImGuiCol_DragDropTarget]         = get_color(accent, m_alpha_90);
        colors[ImGuiCol_NavHighlight]           = white_100;
        colors[ImGuiCol_NavWindowingHighlight]  = white_100;
        colors[ImGuiCol_NavWindowingDimBg]      = white_100;
        colors[ImGuiCol_ModalWindowDimBg]       = white_100;
    }

    ImVec4 ColorSchemeEditor::lighten(ImVec4 color, float p)
    {
        return ImVec4(fmax(0.0f, color.x - 1.0f * p), fmax(0.0f, color.y - 1.0f * p), fmax(0.0f, color.z - 1.0f * p), color.w);
    }

    ImVec4 ColorSchemeEditor::mix(ImVec4 c1, ImVec4 c2)
    {
        return ImVec4((c1.x + c2.x) / 2.0f, (c1.y + c2.y) / 2.0f, (c1.z + c2.z) / 2.0f, (c1.w + c2.w) / 2.0f);
    }
}