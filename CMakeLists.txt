cmake_minimum_required(VERSION 3.10)

project(Cube)

find_package( OpenGL REQUIRED )
find_package( GLEW REQUIRED)

get_filename_component(PROJECTNAME ${CMAKE_CURRENT_LIST_DIR} NAME)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE "GLVND")

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

set(glm_DIR include/glm/cmake/glm) 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_subdirectory(include/glfw)
include_directories(include/glfw/include)
include_directories(include/glm/glm)
add_subdirectory(include/glm)

set(CMAKE_PREFIX_PATH include/glfw ${CMAKE_PREFIX_PATH})

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()



set(SOURCES 
    src/main.hpp src/main.cpp src/library.hpp src/library.cpp
)

configure_file(${CMAKE_SOURCE_DIR}/Surface.dat ${CMAKE_BINARY_DIR}/Surface.dat)
configure_file(${CMAKE_SOURCE_DIR}/CubeConnectivity.dat ${CMAKE_BINARY_DIR}/CubeConnectivity.dat)


add_executable(${PROJECT_NAME} ${SOURCES})

if(OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS}  )
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw m  glm::glm GLEW::GLEW)
else()
    message(FATAL_ERROR "OpenGL not found")
endif()