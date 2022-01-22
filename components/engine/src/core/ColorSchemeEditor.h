//
// Created by BlackFlage on 04.01.2022.
//

#ifndef MAIN_COLORSCHEMEEDITOR_H
#define MAIN_COLORSCHEMEEDITOR_H

#include "ImGui/imgui.h"

namespace vis
{
    struct Theme
    {
        unsigned int background;
        unsigned int text;
        unsigned int main_theme;
        unsigned int accent;
        unsigned int plot_lines;
    };

    namespace themes
    {
        static inline Theme DEFAULT = { 0x21212100, 0xFFFFFF00, 0x42424200, 0x61616100, 0xFFFFFF00 };
        static inline Theme LIGHT_BROWN = { 0x3E272300, 0xBCAAA400, 0x4E342E00, 0x79554800, 0xFFFFFF00 };
        static inline Theme BLUE_GRAY = { 0x26323800, 0xB0BEC500, 0x37474F00, 0x546E7A00, 0xFFFFFF00 };
    }

    class ColorSchemeEditor
    {
    public:
        static float get_R(unsigned int color = m_black);
        static float get_G(unsigned int color = m_black);
        static float get_B(unsigned int color = m_black);
        static float get_alpha(unsigned int alpha = 0xFF);
        static ImVec4 lighten(ImVec4 color, float p);
        static ImVec4 mix(ImVec4 c1, ImVec4 c2);
        static ImVec4 get_color(unsigned int color = m_black, unsigned int alpha = m_alpha_100);
        static inline Theme get_current_theme() { return m_current_theme; }

        static void set_theme(Theme theme = themes::DEFAULT);
        static void set_theme(unsigned int background = 0x21212100, unsigned int text = 0xFFFFFF00, unsigned int main_theme = 0x42424200, unsigned int accent = 0x61616100, unsigned int plot_lines = 0xFFFFFF00);

        inline static unsigned int m_alpha_0   = 0x00;
        inline static unsigned int m_alpha_20  = 0x33;
        inline static unsigned int m_alpha_40  = 0x66;
        inline static unsigned int m_alpha_60  = 0x9A;
        inline static unsigned int m_alpha_70  = 0xB3;
        inline static unsigned int m_alpha_80  = 0xCD;
        inline static unsigned int m_alpha_90  = 0xE6;
        inline static unsigned int m_alpha_100 = 0xFF;

        inline static unsigned int m_white     = 0xFFFFFF00;
        inline static unsigned int m_black     = 0x00000000;

        inline static Theme m_current_theme = themes::DEFAULT;
    };
}

#endif //MAIN_COLORSCHEMEEDITOR_H
