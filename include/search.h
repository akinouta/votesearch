#ifndef SEARCH_H
#define SEARCH_H
#if defined(_MSC_VER) // Visual studio
#define thread_local __declspec(thread)
#elif defined(__GCC__) // GCC
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
#include <omp.h>
#include <random>
#include <time.h>
#include <thread>
#include <chrono>

#include "common.h"
#include "guided_structure.h"

std::tuple<std::vector<int>, std::vector<float>> search_KNN(float *query, int K, AdjList &graph, Matrix<float> &points, int start, int max_calc);
std::tuple<std::vector<int>, std::vector<float>> search_KNN_by_Guided_tree(float *query, int K, AdjList &graph, Matrix<float> &points, std::vector<Guided_tree *> &trees, int start, int max_calc);
std::tuple<std::vector<int>, std::vector<float>> search_KNN_two_phase(float *query, int K, AdjList &graph, Matrix<float> &points, std::vector<Guided_tree *> &trees, int start, int max_calc);
void test_without_guide(Matrix<float> &queries, int K, Matrix<float> &points, std::vector<std::vector<int>> &GT, AdjList &graph, int max_calc);
void test_Guided_tree(Matrix<float> &queries, int K, Matrix<float> &points, std::vector<std::vector<int>> &GT, AdjList &graph, std::vector<Guided_tree *> &trees, int max_calc);
void test_two_phase(Matrix<float> &queries, int K, Matrix<float> &points, std::vector<std::vector<int>> &GT, AdjList &graph, std::vector<Guided_tree *> &trees, int max_calc);

#endif