cmake_minimum_required(VERSION 3.28.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(app VERSION 1.0.0)

add_executable(app)

find_package(glfw3 REQUIRED CONFIG)
target_link_libraries(app glfw)

target_sources(app PRIVATE 
	${CMAKE_SOURCE_DIR}/src/main.cpp 
)
target_include_directories(app PUBLIC "${CMAKE_SOURCE_DIR}/include")