cmake_minimum_required(VERSION 3.0)

project (TestGladGlfw)      # 工程名称

link_directories(${PROJECT_SOURCE_DIR}/lib)         # 库目录, -L

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17")

set(SOURCE_FILES src/test.cpp src/glad.c)
add_executable(main ${SOURCE_FILES})    # 源文件

include_directories(${PROJECT_SOURCE_DIR}/include)   # 头文件目录, -I

target_link_libraries(main glfw3)