#ifndef GUIDED_STRUCTURE_H
#define GUIDED_STRUCTURE_H

#if defined (_MSC_VER)  // Visual studio
    #define thread_local __declspec( thread )
#elif defined (__GCC__) // GCC
    #define thread_local __thread
#endif

#include<vector>
#include "common.h"

struct guided_tree
{
    guided_tree *neg;
    guided_tree *pos;
    std::vector<int> points;
    bool is_leaf;
    int level;
    guided_tree();
    ~guided_tree(); 
};

guided_tree get_guided_tree(int p,std::vector<int> neighbors,int start_dim,int end_dim);
#endif