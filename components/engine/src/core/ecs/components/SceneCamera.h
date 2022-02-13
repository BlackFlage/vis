//
// Created by BlackFlage on 06.02.2022.
//

#ifndef MAIN_SCENECAMERA_H
#define MAIN_SCENECAMERA_H

#include <array>

namespace vis
{
    class SceneCamera
    {
    public:
        SceneCamera();

        void set_use_skybox(bool use_skybox);
        void set_clear_color(float v1, float v2, float v3);

        bool& get_use_skybox();
        std::array<float, 3>& get_clear_color();
        float& get_z_near();
        float& get_z_far();
        float& get_fov();
    private:
        bool m_use_skybox;
        bool m_perspective_view;
        float m_FOV;
        float m_near;
        float m_far;
        std::array<float, 3> m_clear_color;
    };
}

#endif //MAIN_SCENECAMERA_H
