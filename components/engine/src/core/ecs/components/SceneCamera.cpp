//
// Created by BlackFlage on 06.02.2022.
//

#include "SceneCamera.h"

#define DEFAULT_CLEAR_COLOR { 0.25f, 0.5f, 0.25f }
#define DEFAULT_FOV 60.0f
#define DEFAULT_NEAR 1.0f
#define DEFAULT_FAR 1000.0f

namespace vis
{

    vis::SceneCamera::SceneCamera()
    {
        m_use_skybox       = false;
        m_perspective_view = true;
        m_clear_color      = DEFAULT_CLEAR_COLOR;
        m_FOV              = DEFAULT_FOV;
        m_near             = DEFAULT_NEAR;
        m_far              = DEFAULT_FAR;
    }

    bool& SceneCamera::get_use_skybox()
    {
        return m_use_skybox;
    }

    std::array<float, 3>& SceneCamera::get_clear_color()
    {
        return m_clear_color;
    }

    void SceneCamera::set_use_skybox(bool use_skybox)
    {
        m_use_skybox = use_skybox;
    }

    void SceneCamera::set_clear_color(float v1, float v2, float v3)
    {
        m_clear_color = {v1, v2, v3};
    }

    float& SceneCamera::get_z_near()
    {
        return m_near;
    }

    float& SceneCamera::get_z_far()
    {
        return m_far;
    }

    float& SceneCamera::get_fov()
    {
        return m_FOV;
    }
}