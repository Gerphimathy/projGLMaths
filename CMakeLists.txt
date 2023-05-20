cmake_minimum_required(VERSION 3.25)
project(math)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(math
        main.cpp
        math/Matrix.cpp
        math/Matrix.hpp
        math/Quaternion.cpp
        math/Quaternion.hpp
        math/Vector2.cpp
        math/Vector2.hpp
        math/Vector3.cpp
        math/Vector3.hpp ThreeD/Vertex.hpp ThreeD/Mesh.hpp window/Application.hpp shaders/GLShader.cpp shaders/GLShader.hpp)


target_link_libraries(math ${OPENGL_LIBRARIES} glfw3 glew32)
target_include_directories(math PUBLIC ${OPENGL_INCLUDE_DIRS} glfw3 glew32)