cmake_minimum_required(VERSION 3.24)
project(math)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
link_directories(${OPENGL_gl_LIBRARY})

include_directories(../libs/glfw/include)
include_directories(../libs/glew/include)

link_directories(../libs/glfw/lib-mingw-w64)
link_directories(../libs/glew/lib/Release/x64)



add_executable(
        math
        main.cpp

        math/Matrix.cpp
        math/Matrix.hpp
        math/Quaternion.cpp
        math/Quaternion.hpp
        math/Vector2.cpp
        math/Vector2.hpp
        math/Vector3.cpp
        math/Vector3.hpp

        ThreeD/Mesh.hpp
        ThreeD/Material.hpp
        ThreeD/Texture.hpp
        ThreeD/Mesh.cpp

        window/Application.hpp

        shaders/GLShader.cpp
        shaders/GLShader.hpp

        loader/loadMesh.h
        loader/stb_image.h

        ThreeD/Camera.cpp ThreeD/Camera.h ThreeD/ThreeDObject.cpp ThreeD/ThreeDObject.h ThreeD/Light.cpp ThreeD/Light.h window/Controls.hpp)


target_link_libraries(math glfw3 ${OPENGL_gl_LIBRARY} glew32)
#target_include_directories(math loader math shaders TestObjects ThreeD window glfw3 ${OPENGL_gl_LIBRARY} glew32)