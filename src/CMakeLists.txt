
#INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})


#如果需要包含头文件，应该加上INCLUDE_DIRECTORIES(PATH)
#INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

#设置生成的二进制库（.so .a不是可执行文件）的存放位置位于build/lib
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
message(STATUS "PROJECT_BINARY_DIR:${PROJECT_BINARY_DIR}") 

#将源文件添加进一个变量中
SET(DIR_LIB_SRCS ./)

#static参数指明是静态库，会在编译的时候将二进制代码嵌入最后唯一的可执行文件，
#shared参数指明是动态库，编译的时候不会将二进制代码嵌入执行文件，而是生成一个二进制文件，在执行时再动态加载这个二进制文件供别的模块调用
#此处生成了一个二进制库叫做Mylib
message(STATUS "DIR_LIB_SRCS:${DIR_LIB_SRCS}") 
add_library(tcp_server ${DIR_LIB_SRCS}/tcp-server/tcp_server.cc)

#设置产生的二进制文件放在bin文件夹中
#PROJECT_BINARY_DIR的含义是在那个文件夹中执行cmake命令
#哪个文件夹就是PROJECT_BINARY_DIR
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# 查找当前目录下的所有源文件,因为函数名为directory，肯定是文件夹
# 并将名称保存到 DIR_SRCS 变量
#aux_source_directory(./binary-search-407.cc DIR_SRCS)


#目录下面有很多题目，要为每一个.cc文件生成相应的.out可执行文件
    #set(SRC_407 ./Array/binary-search-407.cc)


# 添加源文件，指定生成目标
    #add_executable(Demo_407 ${SRC_407})


# 添加静态链接库
#指明demo二进制文件需要链接的二进制库，此处MathFunctions正是我们在lib目录下的
#CMake文件中定义的二进制库
#target_link_libraries(Demo MathFunctions)