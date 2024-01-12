cmake_minimum_required (VERSION 3.9.0)
project(gltemplate)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(glad)

add_subdirectory(Libraries/include/GLFW)


add_executable(gltemplate 
	main.cpp 
	glad.c 
)

target_link_libraries(gltemplate glfw)