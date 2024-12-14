# 指定CMake的最小版本要求
cmake_minimum_required(VERSION 3.1)

# 定义项目名称和语言
project(HCNNG_LIB CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加src目录下的源文件，生成静态库
file(GLOB SOURCES "*.cpp")
add_library(mylib STATIC ${SOURCES})

# 包含头文件目录
target_include_directories(mylib PUBLIC ${PROJECT_SOURCE_DIR}/../include)


# 链接OpenMP库到目标
if(OpenMP_CXX_FOUND)
    target_link_libraries(mylib PRIVATE ${OpenMP_CXX_FLAGS})
endif()