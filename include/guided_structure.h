#ifndef GUIDED_STRUCTURE_H
#define GUIDED_STRUCTURE_H

#if defined (_MSC_VER)  // Visual studio
    #define thread_local __declspec( thread )
#elif defined (__GCC__) // GCC
    #define thread_local __thread
#endif

#include<vector>
#include "common.h"

struct Guided_tree
{
    Guided_tree *neg;
    Guided_tree *pos;
    std::vector<int> neighbors;
    bool is_leaf;
    int level;
    Guided_tree();
    ~Guided_tree(); 
};


Guided_tree* get_Guided_tree(int p,Matrix<float> &points,std::vector<int> &neighbors,int start_dim,int end_dim);
std::vector<Guided_tree*> get_all_Guided_tree(Matrix<float> &points,AdjList &graph);
#endif