cmake_minimum_required(VERSION 3.19)
project(ImGui)

set(CMAKE_CXX_STANDARD 20)

set(HEADER_FILES
        ImGui/imconfig.h
        ImGui/imgui.h
        ImGui/imgui_internal.h
        ImGui/imstb_rectpack.h
        ImGui/imstb_textedit.h
        ImGui/imstb_truetype.h
        ImGui/imgui_impl_opengl3.h
        ImGui/imgui_impl_opengl3_loader.h
        )

set(SOURCE_FILES
        ImGui/imgui.cpp
        ImGui/imgui_demo.cpp
        ImGui/imgui_draw.cpp
        ImGui/imgui_tables.cpp
        ImGui/imgui_widgets.cpp
        ImGui/imgui_impl_opengl3.cpp
        )

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "ImGui")