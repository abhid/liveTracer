cmake_minimum_required (VERSION 2.6)
project (GRAPHICSRENDERER)

# Set the folder where the binaries are being stored
set (BIN_DIR "bin")
set (TEST_DIR "bin/test")

# Create the binary directories if not already created
MAKE_DIRECTORY (${BIN_DIR})
MAKE_DIRECTORY (${TEST_DIR})

set (CMAKE_CXX_FLAGS "-g3 -Wall")
include_directories(.)
include_directories(libLinear)
include_directories(libObjects)
include_directories(libObjects/libMaterial)
include_directories(libOGL)
include_directories(libOutput)
include_directories(libParser)

 add_library (Graphics
		libLinear/Vector.cpp libLinear/Vector.h
		libLinear/Matrix.cpp libLinear/Matrix.h
		libLinear/Ray.h	libLinear/GMatrix.h
		libLinear/utilMatrix.h
		
		libObjects/Camera.h libObjects/HitStruct.h
		libObjects/Light.h libObjects/Object.h
		libObjects/Quad.h libObjects/Sphere.h
		libObjects/Triangle.h libObjects/Vertex.h
			libObjects/libMaterial/Shading.h
			libObjects/libMaterial/Texture.h
				
		libOGL/OGLImage.h	libOGL/liveTrace.h
		
		libOutput/Image.h libOutput/PNGImage.cpp
		libOutput/PNGImage.h libOutput/writepng.cpp
		libOutput/writepng.h
		
		libParser/Parser.cpp libParser/Parser.h
		libParser/Scene.cpp libParser/Scene.h
		)
		
add_executable (${BIN_DIR}/Renderer Renderer.cpp)

target_link_libraries (${BIN_DIR}/Renderer Graphics)
target_link_libraries (${BIN_DIR}/Renderer png)
target_link_libraries (${BIN_DIR}/Renderer sfml-window)
target_link_libraries (${BIN_DIR}/Renderer GL)
target_link_libraries (${BIN_DIR}/Renderer GLEW)
target_link_libraries (${BIN_DIR}/Renderer GLU)
target_link_libraries (${BIN_DIR}/Renderer pthread)

add_executable (${TEST_DIR}/libLinear
		libLinear/libLinearTest.cpp
		libLinear/Vector.cpp
		libLinear/Matrix.cpp
		libLinear/Ray.h	libLinear/GMatrix.h
		libLinear/utilMatrix.h
		)