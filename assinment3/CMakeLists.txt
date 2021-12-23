# 规定该CMakeLists.txt适用的cmake最小版本，这里是 3.10
cmake_minimum_required(VERSION 3.10)

# 相当于visual studio项目名称，这里是 MYwork 但似乎没有什么地方需要用到
project(MYwork)
set(CMAKE_CXX_COMPILER "g++")#设置c++编译器

include_directories(${PROJECT_SOURCE_DIR}/include)#添加头文件的搜索路径

aux_source_directory(./src SrcFiles)#将源文件列表写在变量SrcFiles中

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)#设置可执行文件输出路径

add_executable(test main.cpp ${SrcFiles})#设置可执行文件的名称，make之后bin目录下出现test.exe