cmake_minimum_required(VERSION 3.19)
project(VISUAL)

set(CMAKE_CXX_STANDARD 17)

set(CORE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/core)

set(HEADER_FILES
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
        )

set(SOURCE_FILES
        ${CORE_PATH}/EntryPoint.cpp
        ${CORE_PATH}/Window.cpp
        ${CORE_PATH}/Application.cpp
        )

set(HEADER_FILES_UTIL
        src/utilities/Timer.h)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${HEADER_FILES_UTIL})

target_link_libraries(${PROJECT_NAME} opengl32)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/core)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/utilities)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics)