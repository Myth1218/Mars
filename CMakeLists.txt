#顶层CMake

cmake_minimum_required(VERSION 2.8)


##指定工程名字，工程语言,定义了PROJECT( DIR ),则此CMake文件就是顶层Cmake，其所在的目录会被视为全局变量PROJECT_SOURCE_DIR的值，即项目的根目录
project(demo_gdb_ CXX)

#打印输出变量信息
message(STATUS "项目源路径:${PROJECT_SOURCE_DIR}") 

#设置变量。此处用于设置GDB调试
set(CMAKE_BUILD_TYPE "Debug")   #构建级别，DEBUG级别能够用来调试。
#当这个变量值为Debug的时候，Cmake会使用变量CMAKE_FLAGS_DEBUG 和 CMAKE_C_FLAGS_DEBUG中的字符串作为编译选项生成Makefile.
#-Wall选项意思是编译后显示所有警告（W 表示warning）；-g 可执行程序包含调试信息
#-g 该选项可以利用操作系统的“原生格式（native format）”生成调试信息。GDB 可以直接利用这个信息，其它调试器也可以使用这个调试信息
#-ggdb 使 GCC 为 GDB 生成专用的更为丰富的调试信息，但是，此时就不能用其他的调试器来进行调试了 (如 ddx)
#-O0表示没有优化,-O1为缺省值，-O3优化级别最高
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


#添加一个子目录并构建该子目录，告诉CMAKE我还有其它子目录的CMakeList.txt需要编译。目录下必须要有CMakeLists.txt
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/Math) 
add_subdirectory(${PROJECT_SOURCE_DIR}/src)