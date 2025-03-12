cmake_minimum_required(VERSION 3.6)

project(HCNNG CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


find_package(OpenMP REQUIRED)

# 查找 Boost（必须包含 serialization 和 system 组件）
find_package(Boost 1.71.0 REQUIRED COMPONENTS serialization system)

# 检查 Boost 是否找到
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost 库未找到，请安装 libboost-dev, libboost-serialization-dev, libboost-system-dev")
endif()

# 包含头文件目录
include_directories(
    include
    ${Boost_INCLUDE_DIRS}  # 添加 Boost 头文件路径
)

if(OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# 添加子目录
add_subdirectory(src)
add_subdirectory(tests)

