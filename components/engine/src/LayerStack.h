//
// Created by BlackFlage on 07.10.2021.
//

#ifndef VISUAL_LAYERSTACK_H
#define VISUAL_LAYERSTACK_H

#include <vector>
#include <algorithm>
#include "Layer.h"

namespace vis
{
    class LayerStack
    {
    public:
        inline void push_layer(Layer* a_layer) { m_stack.push_back(a_layer); a_layer->on_attach(); }
        inline void detach_layer(Layer* a_layer) { a_layer->on_detach(); std::remove(m_stack.begin(), m_stack.end(), a_layer); }

        inline void clear_stack()
        {
            std::for_each(m_stack.begin(), m_stack.end(), [](Layer* a_layer) { a_layer->on_detach(); });
            std::for_each(m_stack.begin(), m_stack.end(), std::default_delete<Layer>());
            m_stack.clear();
        }

        inline void update_all_layers()
        {
            std::for_each(m_stack.begin(), m_stack.end(), [](Layer* a_layer) { a_layer->on_update(); });
        }

        inline std::vector<Layer*> get_layers() { return m_stack; }
    private:
        std::vector<Layer*> m_stack;
    };
}

#endif //VISUAL_LAYERSTACK_H
