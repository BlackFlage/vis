cmake_minimum_required(VERSION 3.19)
project(VISUAL)

set(CMAKE_CXX_STANDARD 20)

set(CORE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/core)
set(GRAPHICS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics)
set(VENDOR_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../vendor)

set(HEADER_FILES_CORE
        ${CORE_PATH}/Window.h
        ${CORE_PATH}/Application.h
        ${CORE_PATH}/Input.h
        ${CORE_PATH}/Event.h
        ${CORE_PATH}/KeyboardEvent.h
        ${CORE_PATH}/MouseEvent.h
        ${CORE_PATH}/Layer.h
        ${CORE_PATH}/LayerStack.h
        ${CORE_PATH}/Sandbox.h
        ${CORE_PATH}/Macro.h
        ${CORE_PATH}/Logger.h
        )

set(SOURCE_FILES_CORE
        ${CORE_PATH}/EntryPoint.cpp
        ${CORE_PATH}/Window.cpp
        ${CORE_PATH}/Application.cpp
        ${CORE_PATH}/Logger.cpp
        ${CORE_PATH}/Macro.cpp
        )

set(HEADER_FILES_UTIL
        src/utilities/Timer.h
        src/utilities/OBJLoader.h)

set(SOURCE_FILES_UTIL
        src/utilities/OBJLoader.cpp)

set(HEADER_FILES_GRAPHICS
        src/utilities/Mesh.h
        src/utilities/Model.h
        ${GRAPHICS_PATH}/Renderer.h
        ${GRAPHICS_PATH}/VBO.h
        ${GRAPHICS_PATH}/Shader.h
        ${GRAPHICS_PATH}/VAO.h
        ${GRAPHICS_PATH}/EBO.h
        ${GRAPHICS_PATH}/Camera.h
        ${GRAPHICS_PATH}/Vertex.h
        )

set(SOURCE_FILES_GRAPHICS
        src/utilities/Mesh.cpp
        src/utilities/Model.cpp
        ${GRAPHICS_PATH}/Renderer.cpp
        ${GRAPHICS_PATH}/VBO.cpp
        ${GRAPHICS_PATH}/Shader.cpp
        ${GRAPHICS_PATH}/VAO.cpp
        ${GRAPHICS_PATH}/EBO.cpp
        ${GRAPHICS_PATH}/Camera.cpp
        )


add_subdirectory(${VENDOR_PATH}/glew/build/cmake ${VENDOR_PATH}/glew/build/cmake)
add_executable(${PROJECT_NAME} ${HEADER_FILES_CORE} ${SOURCE_FILES_CORE} ${HEADER_FILES_UTIL} ${SOURCE_FILES_UTIL} ${HEADER_FILES_GRAPHICS} ${SOURCE_FILES_GRAPHICS})

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
