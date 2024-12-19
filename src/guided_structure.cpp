#if defined(_MSC_VER) // Visual studio
#define thread_local __declspec(thread)
#elif defined(__GCC__) // GCC
#define thread_local __thread
#endif

#include "guided_structure.h"
using namespace std;

Guided_tree::Guided_tree() : is_leaf(false)
{
}

Guided_tree::~Guided_tree()
{
}

Guided_tree *get_Guided_tree(int p, Matrix<float> &points, vector<int> &neighbors, int start_dim, int end_dim)
{
    Guided_tree *tree = new Guided_tree();
    vector<int> neg_neighbors;
    vector<int> pos_neighbors;
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
        tree->is_leaf = true;
    }
    else
    {
        tree->neg = get_Guided_tree(p, points, neg_neighbors, start_dim + 1, end_dim);
        tree->pos = get_Guided_tree(p, points, pos_neighbors, start_dim + 1, end_dim);
    }
    return tree;
}

vector<Guided_tree *> get_all_Guided_tree(Matrix<float> &points, AdjList &graph)
{
    vector<Guided_tree *> trees;
    for (int i = 0; i < points.rows; ++i)
    {
        auto tree = get_Guided_tree(i, points, graph[i], 0, points.cols);
        trees.push_back(tree);
    }
    return trees;
}

vector<int> find_neighbors(float *query, int curr, Guided_tree *tree, Matrix<float> &points, int start_dim, int end_dim)
{
    for (int dim = start_dim; dim < end_dim; ++dim)
    {
        if (tree->is_leaf)
        {
            break;
        }
        else
        {
            if (query[dim] < points[curr][dim])
            {
                tree = tree->neg;
            }
            else
            {
                tree = tree->pos;
            }
        }
    }
    return tree->neighbors;
}