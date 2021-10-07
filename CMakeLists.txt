cmake_minimum_required(VERSION 3.19)
project(VISUAL)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        src/Window.h
        src/Application.h
        src/Input.h
        src/Event.h
        src/KeyboardEvent.h
        src/MouseEvent.h
        src/Layer.h
        src/LayerStack.h
        src/Sandbox.h
        )

set(SOURCE_FILES
        src/main.cpp
        src/Window.cpp
        src/Application.cpp
        src/Input.cpp
        )

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)