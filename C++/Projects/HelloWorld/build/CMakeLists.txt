cmake_minimum_required (VERSION 3.0)    # cmake 最低版本

project (helloworld)    # 工程名称

add_executable(helloworld ../helloworld.cpp ../printtest.cpp)   # 源文件
# target_sources(helloworld PUBLIC ../printtest.cpp)
# if(WIN32)   # 静态关联配置
#     set(CMAKE_CXX_FLAGS "-static-libgcc")
# endif(WIN32)