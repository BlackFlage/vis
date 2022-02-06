cmake_minimum_required(VERSION 3.19)
project(VISUAL)

set(CORE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/core)
set(GRAPHICS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics)
set(VENDOR_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../vendor)

set(HEADER_FILES_CORE
        ${CORE_PATH}/Window.h
        ${CORE_PATH}/Application.h
        ${CORE_PATH}/Input.h
        ${CORE_PATH}/event/Event.h
        ${CORE_PATH}/event/KeyboardEvent.h
        ${CORE_PATH}/event/MouseEvent.h
        ${CORE_PATH}/event/WindowEvent.h
        ${CORE_PATH}/Macro.h
        ${CORE_PATH}/Logger.h
        ${CORE_PATH}/Types.h
        ${CORE_PATH}/layers/Layer.h
        ${CORE_PATH}/layers/LayerStack.h
        ${CORE_PATH}/layers/ImGuiLayer.h
        ${CORE_PATH}/layers/SceneEditorLayer.h
        ${CORE_PATH}/ecs/EntityManager.h
        ${CORE_PATH}/ecs/ComponentManager.h
        ${CORE_PATH}/ecs/ComponentArray.h
        ${CORE_PATH}/ecs/System.h
        ${CORE_PATH}/ecs/Entity.h
        ${CORE_PATH}/ecs/SystemManager.h
        ${CORE_PATH}/ecs/MainManager.h
        ${CORE_PATH}/ecs/systems/BasicSystems.h
        ${CORE_PATH}/ecs/components/BasicComponents.h
        ${CORE_PATH}/scene/SceneManager.h
        ${CORE_PATH}/scene/Scene.h
        ${CORE_PATH}/resource_loaders/ResourcesManager.h
        ${CORE_PATH}/resource_loaders/ResourceArray.h
        ${CORE_PATH}/resource_loaders/MeshLoader.h
        ${CORE_PATH}/resource_loaders/resource_types/Mesh.h
        ${CORE_PATH}/ColorSchemeEditor.h
        ${CORE_PATH}/TPool.h
        )

set(SOURCE_FILES_CORE
        ${CORE_PATH}/EntryPoint.cpp
        ${CORE_PATH}/Window.cpp
        ${CORE_PATH}/Application.cpp
        ${CORE_PATH}/Logger.cpp
        ${CORE_PATH}/Macro.cpp
        ${CORE_PATH}/Input.cpp
        ${CORE_PATH}/ecs/Entity.cpp
        ${CORE_PATH}/ecs/EntityManager.cpp
        ${CORE_PATH}/layers/ImGuiLayer.cpp
        ${CORE_PATH}/layers/SceneEditorLayer.cpp
        ${CORE_PATH}/scene/SceneManager.cpp
        ${CORE_PATH}/scene/Scene.cpp
        ${CORE_PATH}/resource_loaders/MeshLoader.cpp
        ${CORE_PATH}/resource_loaders/ResourcesManager.cpp
        ${CORE_PATH}/resource_loaders/resource_types/Mesh.cpp
        ${CORE_PATH}/ColorSchemeEditor.cpp
        ${CORE_PATH}/TPool.cpp
        )

set(HEADER_FILES_UTIL
        src/utilities/Timer.h
        src/utilities/BMPLoader.h
        ${VENDOR_PATH}/nativefiledialog/src/common.h
        ${VENDOR_PATH}/nativefiledialog/src/nfd_common.h
        ${VENDOR_PATH}/stbimage/stb_image.h
        )

set(SOURCE_FILES_UTIL
        src/utilities/BMPLoader.cpp
        ${VENDOR_PATH}/nativefiledialog/src/nfd_win.cpp
        ${VENDOR_PATH}/nativefiledialog/src/nfd_common.c)

set(HEADER_FILES_GRAPHICS
        ${GRAPHICS_PATH}/Model.h
        ${GRAPHICS_PATH}/Renderer.h
        ${GRAPHICS_PATH}/Shader.h
        ${GRAPHICS_PATH}/Camera.h
        ${GRAPHICS_PATH}/Texture.h
        ${GRAPHICS_PATH}/Framebuffer.h
        ${GRAPHICS_PATH}/Grid.h
        ${GRAPHICS_PATH}/Skybox.h
        )

set(SOURCE_FILES_GRAPHICS
        ${GRAPHICS_PATH}/Model.cpp
        ${GRAPHICS_PATH}/Renderer.cpp
        ${GRAPHICS_PATH}/Shader.cpp
        ${GRAPHICS_PATH}/Camera.cpp
        ${GRAPHICS_PATH}/Texture.cpp
        ${GRAPHICS_PATH}/Framebuffer.cpp
        ${GRAPHICS_PATH}/Grid.cpp
        ${GRAPHICS_PATH}/Skybox.cpp
        )


add_executable(${PROJECT_NAME} ${HEADER_FILES_CORE} ${SOURCE_FILES_CORE} ${HEADER_FILES_UTIL} ${SOURCE_FILES_UTIL} ${HEADER_FILES_GRAPHICS} ${SOURCE_FILES_GRAPHICS})
add_subdirectory(${VENDOR_PATH}/glew/build/cmake ${VENDOR_PATH}/glew/build/cmake)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/core)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/utilities)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics)

# VENDOR

#SPDLOG
target_include_directories(${PROJECT_NAME} PRIVATE ${VENDOR_PATH}/spdlog/include)

#GLEW
target_include_directories(${PROJECT_NAME} PRIVATE ${VENDOR_PATH}/glew/include)
target_link_libraries(${PROJECT_NAME} opengl32 glew_s)

#GLM
add_subdirectory(${VENDOR_PATH}/glm ${VENDOR_PATH}/glm)
target_link_libraries(${PROJECT_NAME} glm::glm)
target_include_directories(${PROJECT_NAME} PRIVATE ${VENDOR_PATH}/glm)

#ImGui
add_subdirectory(${VENDOR_PATH}/ImGui ${VENDOR_PATH}/ImGui)
target_link_libraries(${PROJECT_NAME} ImGui)
target_include_directories(${PROJECT_NAME} PRIVATE ${VENDOR_PATH}/ImGui)

#stb_image
target_include_directories(${PROJECT_NAME} PRIVATE ${VENDOR_PATH}/stbimage)

#nativefiledialog
target_include_directories(${PROJECT_NAME} PRIVATE ${VENDOR_PATH}/nativefiledialog/src/include)

IF(WIN32)
    target_link_libraries(${PROJECT_NAME} "Dwmapi.lib")
ENDIF()