cmake_minimum_required(VERSION 3.10.0)
project(gpge VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES 
    "src/*.cpp"
    "src/**/*.cpp"
    "src/**/**/*.cpp"
    "src/**/**/**/*.cpp"
    "src/include/*.h"
    "src/include/**/*.h"
    "src/include/**/**/*.h"
    "src/include/**/**/**/*.h"
)

add_executable(gpge ${SOURCES})

find_package(OpenGL REQUIRED)

# --- ImGui Library ---
set(IMGUI_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/")
file(GLOB IMGUI_SOURCES
    "${IMGUI_PATH}/*.cpp"
    "${IMGUI_PATH}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp"
)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC "${IMGUI_PATH}" "${IMGUI_PATH}/backends" lib/glfw/include)
# ---------------------
# --- GLEW Library ---
set (GLEW_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/glew/")
file(GLOB GLEW_SOURCES
    "${GLEW_PATH}/src/glew.c"
)
add_library(glew STATIC ${GLEW_SOURCES})
target_include_directories(glew PUBLIC "${GLEW_PATH}" "${GLEW_PATH}/include")
# ---------------------


add_definitions(-DGLEW_STATIC)

add_subdirectory(lib/glfw)

target_link_libraries(gpge PRIVATE imgui glfw OpenGL::GL glew)

target_compile_definitions(imgui PUBLIC IMGUI_ENABLE_DOCKING)
target_compile_definitions(gpge PRIVATE IMGUI_ENABLE_DOCKING)

target_include_directories(gpge PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
