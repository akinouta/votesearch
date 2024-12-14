#if defined(_MSC_VER) // Visual studio
#define thread_local __declspec(thread)
#elif defined(__GCC__) // GCC
#define thread_local __thread
#endif

#include "guided_structure.h"

Guided_tree::Guided_tree()
{
}

Guided_tree::~Guided_tree()
{
}

Guided_tree *get_Guided_tree(int p, Matrix<float> &points, std::vector<int> &neighbors, int start_dim, int end_dim)
{
    Guided_tree *tree=new Guided_tree();
    std::vector<int> neg_neighbors;
    std::vector<int> pos_neighbors;
    for (auto neighbor : neighbors)
    {
        if (start_dim < end_dim && points[neighbor][start_dim] < points[p][start_dim])
        {
            neg_neighbors.push_back(neighbor);
        }
        else
        {
            pos_neighbors.push_back(neighbor);
        }
    }

    if (neg_neighbors.empty() || pos_neighbors.empty())
    {
        tree->neighbors = neighbors;
    }
    else
    {
        tree->neg = get_Guided_tree(p, points, neg_neighbors, start_dim + 1, end_dim);
    }
    return tree;
}

std::vector<Guided_tree *> get_all_Guided_tree(Matrix<float> &points, AdjList &graph)
{
    std::vector<Guided_tree *> trees;
    for (int i = 0; i < points.rows; i++)
    {
        auto tree = get_Guided_tree(i, points, graph[i], 0, points.cols);
        trees.push_back(tree);
    }
    tre
}