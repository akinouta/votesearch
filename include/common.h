#ifndef COMMON_H
#define COMMON_H
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
#include <algorithm>
#include <tuple>
#include <ctime>
#include <cmath>
#include <sys/time.h>
#include <omp.h>
#include <random>
#include <time.h>
#include <thread>

struct MyRandomNumberGenerator
{
	int operator()(int limit) const;
};

struct DisjointSet{
	int * parent;
	int * rank;
	DisjointSet(int N);
	void _union(int x, int y);
	int find(int x);
	~DisjointSet();
};

struct Edge{
	int v1, v2;
	float weight;
	Edge();
	Edge(int _v1, int _v2, float _weight);
	bool operator<(const Edge& e) const;
	~Edge();
};

template <class T>
struct Matrix{
	T *M;
	int rows, cols;
	Matrix();
	Matrix(int _rows, int _cols);
	T* operator[](int i);
	~Matrix();
};
template <class T>
Matrix<T>::Matrix(){
    rows = -1;
    cols = -1;
    M = NULL;
}
template <class T>
Matrix<T>::Matrix(int _rows, int _cols){
    rows = _rows;
    cols = _cols;
    M = new T[((long int)rows)*cols];
}
template <class T>
T* Matrix<T>::operator[](int i){
    return M+(((long int)i)*cols);
}
template <class T>
Matrix<T>::~Matrix(){
    if(M != NULL)
        delete[] M;
    M = NULL;
}

template<typename SomeType>
float mean_v(std::vector<SomeType> a){
	float s = 0;
	for(float x: a) s += x;
	return s/a.size();
}

template<typename SomeType>
float sum_v(std::vector<SomeType> a){
	float s = 0;
	for(float x: a) s += x;
	return s;
}

template<typename SomeType>
float max_v(std::vector<SomeType> a){
	float mx = a[0];
	for(float x: a) mx = std::max(mx,x);
	return mx;
}

template<typename SomeType>
float min_v(std::vector<SomeType> a){
	float mn = a[0];
	for(float x: a) mn = std::min(mn,x);
	return mn;
}

template<typename SomeType>
float std_v(std::vector<SomeType> a){
	float m = mean_v(a), s = 0, n = a.size();
	for(float x: a) s += (x-m)*(x-m);
	return sqrt(s/(n-1));
}

template<typename SomeType>
float variance_v(std::vector<SomeType> a, float mean){
	float o = 0;
	for(float x: a) o += (x-mean)*(x-mean);
	return o/a.size();
}


#define Graph std::vector< std::vector< Edge > >
#define AdjList std::vector< std::vector< int > >
#define not_in_set(_elto,_set) (_set.find(_elto)==_set.end())
#define in_set(_elto,_set) (_set.find(_elto)!=_set.end())
#define not_in_edges(a, b, t, noedges) (noedges.find(make_pair(min(a, b),max(a, b)))==noedges.end() || noedges[make_pair(min(a, b),max(a, b))]&(1LL<<t))


int rand_int(const int & min, const int & max);
int rand_int_nosafe(int min, int max);
float rand_float(const float & min, const float & max);
float dist_L2(float* x, float* y, int n);
float sim_COS(float* x, float* y, int n);
void sort_edges(Graph &G);
Graph complete_edges(Graph &adjlist);
float get_recall(std::vector<int> r1, std::vector<int> r2, int K);
float get_recall_dist(std::vector<float> r1, std::vector<float> r2);
long int fsize(FILE *fp);
Matrix<float> read_fvecs(std::string path_file, int &N, int &Dim);
void write_fvecs(std::string path_file, Matrix<float> &M);
std::vector<std::vector<int> > read_ivecs(std::string path_file, int &N, int &Dim);
void write_ivecs(std::string path_file, std::vector<std::vector<int> > &GT);
std::vector<int> get_sizeadj(Graph &G);
std::vector<int> get_sizeadj(AdjList &G);
void print_stats_graph(Graph &G);
void print_stats_graph(AdjList &G);
void write_graph(std::string path_file, Graph &G);
Graph read_graph(std::string path_file, Matrix<float> &points, bool verbose);
AdjList read_adjlist(std::string path_file, Matrix<float> &points, bool verbose);




#endif