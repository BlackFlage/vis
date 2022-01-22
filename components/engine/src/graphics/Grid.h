//
// Created by BlackFlage on 02.01.2022.
//

#ifndef MAIN_GRID_H
#define MAIN_GRID_H

#include "resource_loaders/resource_types/Mesh.h"
#include "Shader.h"

namespace vis
{
    class Grid
    {
    public:
        Grid() = default;

        bool create(std::uint16_t width, std::uint16_t height);

        const std::vector<Vertex>&       get_vertices()  const;
        const std::vector<unsigned int>& get_indices()   const;
        std::uint16_t                    get_width()     const;
        std::uint16_t                    get_height()    const;
        glm::mat4                        get_model_mat() const;
        glm::vec3 m_pos;
    private:
        std::uint16_t             m_width;
        std::uint16_t             m_height;
        std::vector<Vertex>       m_vertices;
        std::vector<unsigned int> m_indices;
    };
}

#endif //MAIN_GRID_H
