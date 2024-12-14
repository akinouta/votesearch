# 指定CMake的最小版本要求
cmake_minimum_required(VERSION 3.0)

# 定义项目名称和语言
project(HCNNG CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 查找OpenMP
find_package(OpenMP REQUIRED)

# 如果找到了OpenMP，设置编译器标志
if(OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# 添加子目录
add_subdirectory(src)
add_subdirectory(tests)