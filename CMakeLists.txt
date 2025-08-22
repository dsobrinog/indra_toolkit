cmake_minimum_required(VERSION 3.5)
project(indra_toolkit)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#IMGUI KIT SOURCES
file(GLOB_RECURSE KIT_SOURCES src/*.cpp)
file(GLOB_RECURSE KIT_HEADERS 
    includes/*.h
    src/*.h)
    

# ImGui sources (minimal set, without backends yet)
set(IMGUI_SRC
    thirdparty/imgui/imgui.cpp
    thirdparty/imgui/imgui_draw.cpp
    thirdparty/imgui/imgui_tables.cpp
    thirdparty/imgui/imgui_widgets.cpp
    thirdparty/imgui/imgui_demo.cpp   
)

set(IMGUI_BACKEND_SRC
    thirdparty/imgui/backends/imgui_impl_glfw.cpp
    thirdparty/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(indra_toolkit STATIC
    ${KIT_SOURCES}
    ${KIT_HEADERS}
    ${IMGUI_SRC}
)

target_include_directories(indra_toolkit PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui/backends
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/stb
)

target_sources(indra_toolkit PRIVATE ${IMGUI_BACKEND_SRC})

# Link system dependencies (Debian libs installed in Docker)
target_link_libraries(indra_toolkit
    PUBLIC
    glfw
    GL
    X11
    Xi
    Xrandr
    Xxf86vm
    Xcursor
)
