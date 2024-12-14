# 指定CMake的最小版本要求
cmake_minimum_required(VERSION 3.1)

# 定义测试项目名称和语言
project(HCNNG_TEST CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/../include)

# 添加src目录的库，以便测试可以链接到它
add_library(HCNNG_LIB STATIC IMPORTED)
set_target_properties(mylib PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/../src/libmylib.a)

# 添加测试目录下的源文件，并为每个文件生成单独的可执行文件
file(GLOB TEST_SOURCES "*.cpp")
foreach(TEST_SOURCE ${TEST_SOURCES})
    # 获取文件名作为测试的可执行文件名（没有扩展名）
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    
    # 添加可执行文件
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    
    # 链接到mylib库FFF
    target_link_libraries(${TEST_NAME} mylib)
    
    # 如果需要开启OpenMP支持
    find_package(OpenMP REQUIRED)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(${TEST_NAME} ${OpenMP_CXX_FLAGS})
    endif()
endforeach()