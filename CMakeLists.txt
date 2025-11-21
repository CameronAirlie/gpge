cmake_minimum_required(VERSION 3.10.0)
project(gpge VERSION 0.1.0 LANGUAGES C CXX)

include_directories(glfw/include)

find_package(OpenGL REQUIRED)


set(IMGUI_PATH "${CMAKE_CURRENT_SOURCE_DIR}/imgui/")

file(GLOB IMGUI_SOURCES
    "${IMGUI_PATH}/*.cpp"
    "${IMGUI_PATH}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp"
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC "${IMGUI_PATH}" "${IMGUI_PATH}/backends")


add_subdirectory(glfw)

add_executable(gpge main.cpp)
target_link_libraries(gpge PRIVATE imgui glfw OpenGL::GL)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
