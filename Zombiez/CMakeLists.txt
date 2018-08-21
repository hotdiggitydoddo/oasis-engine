cmake_minimum_required(VERSION 3.1)
project(zombiez)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(../Oasis/include
        ../Dependencies/glad/include/
        ../Dependencies/glfw/include/
        ../Dependencies/glm/
        ../Dependencies/stb/)

file(GLOB VENDORS_SOURCES ../Dependencies/glad/src/glad.c)
file(GLOB PROJECT_HEADERS include/Oasis/*.h)
file(GLOB PROJECT_SOURCES src/*.cpp)
file(GLOB PROJECT_SHADERS Shaders/*.comp
        Shaders/*.frag
        Shaders/*.geom
        Shaders/*.vert)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
        Readme.md
        ../.gitattributes
        ../.gitignore
        ../.gitmodules)

source_group("include" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("src" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
        -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")













add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
        ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
        ${VENDORS_SOURCES})

target_link_libraries(${PROJECT_NAME} oasis glfw
        ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
        LinearMath)