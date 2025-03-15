#!/bin/bash

# 打开输出，显示命令执行过程
set -x

# 使用 CMake 生成 Makefile 并构建项目
cmake -Bbuild -H. -DCMAKE_BUILD_TYPE=Debug
cmake --build build

# 创建 bin/graph 目录
mkdir -p bin/graph

# 设置数据集和数据路径变量
dataset=sift
data_path=dataset/${dataset}
graph_path=./bin/graph/${dataset}_hcnng.ivecs

# 检查文件是否存在，如果不存在则执行 build_index 命令
if [ ! -f ${graph_path} ]; then
    ./bin/test_build_index ${data_path}/${dataset}_base.fvecs 1000 20 ${graph_path}
fi

# 执行两阶段搜索测试
# ./bin/test_l_2phase_search ${data_path}/${dataset}_base.fvecs ${data_path}/${dataset}_query.fvecs ${data_path}/${dataset}_groundtruth.ivecs ${graph_path} 10 -1
./bin/test_hyperpara ${data_path}/${dataset}_base.fvecs ${data_path}/${dataset}_query.fvecs ${data_path}/${dataset}_groundtruth.ivecs ${graph_path} 50 -1
./bin/test_hyperpara ${data_path}/${dataset}_base.fvecs ${data_path}/${dataset}_query.fvecs ${data_path}/${dataset}_groundtruth.ivecs ${graph_path} 100 -1

