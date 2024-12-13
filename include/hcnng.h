#ifndef HCNNG_H
#define HCNNG_H

#if defined (_MSC_VER)  // Visual studio
    #define thread_local __declspec( thread )
#elif defined (__GCC__) // GCC
    #define thread_local __thread
#endif

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <tuple>
#include <ctime>
#include <cmath>
#include <sys/time.h>
#include "common.h"
#include <omp.h>
#include <random>
#include <time.h>
#include <thread>

extern int xxx;
std::tuple<Graph, float> kruskal(std::vector<Edge> &edges, int N, Matrix<float> &points, int max_mst_degree);
Graph create_exact_mst(Matrix<float> &points, int *idx_points, int left, int right, int max_mst_degree);
bool check_in_neighbors(int u, std::vector<Edge> &neigh);
void create_clusters(Matrix<float> &points, int *idx_points, int left, int right, Graph &graph, int minsize_cl, std::vector<omp_lock_t> &locks, int max_mst_degree);
Graph HCNNG_create_graph(Matrix<float> &points, int Dim, int num_cl, int minsize_cl, int max_mst_degree);


#endif