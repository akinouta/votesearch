#ifndef SEARCH_H
#define SEARCH_H
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
#include <stack>
#include <map>
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

#include <chrono>
std::tuple<std::vector<int>, std::vector<float>> search_KNN(float *query, int K, AdjList &graph, Matrix<float> &points, int start, int max_calc);
void run_on_testset(Matrix<float> &queries, int K, Matrix<float> &points, std::vector<std::vector<int> > &GT, AdjList &graph, int max_calc);
#endif