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
        src/EntryPoint.cpp
        src/Window.cpp
        src/Application.cpp
        src/Input.cpp
        )

set(HEADER_FILES_UTIL
        src/utilities/Timer.h)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${HEADER_FILES_UTIL})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/utilities)