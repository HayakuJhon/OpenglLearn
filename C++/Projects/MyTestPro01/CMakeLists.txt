cmake_minimum_required(VERSION 3.0)

project (TestGladGlfw)      # 工程名称

link_directories(${PROJECT_SOURCE_DIR}/lib)         # 库目录, -L

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17")

set(SOURCE_FILES src/test.cpp src/glad.c)
add_executable(game ${SOURCE_FILES})    # 源文件
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/run)

include_directories(${PROJECT_SOURCE_DIR}/include)   # 头文件目录, -I

target_link_libraries(game glfw3)