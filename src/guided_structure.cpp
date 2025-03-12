#if defined(_MSC_VER) // Visual studio
#define thread_local __declspec(thread)
#elif defined(__GCC__) // GCC
#define thread_local __thread
#endif

#include "guided_structure.h"
using namespace std;

Guided_tree::Guided_tree() : neg(nullptr), pos(nullptr), is_leaf(false)
{
}

Guided_tree::~Guided_tree()
{
}

Guided_tree *get_Guided_tree(int p, Matrix<float> &points, vector<int> &neighbors, int start_dim, int end_dim, int &max_dim)
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
    ++start_dim;

    if (neg_neighbors.empty() || pos_neighbors.empty())
    {
        tree->neighbors = neighbors;
        tree->is_leaf = true;
    }
    else
    {
        tree->neg = get_Guided_tree(p, points, neg_neighbors, start_dim, end_dim, max_dim);
        tree->pos = get_Guided_tree(p, points, pos_neighbors, start_dim, end_dim, max_dim);
    }
    max_dim = max(start_dim, max_dim);
    return tree;
}

vector<int> find_neighbors(float *query, int curr, Guided_tree *tree, Matrix<float> &points, int start_dim, int end_dim, int &max_dim)
{
    int dim;
    for (dim = start_dim; dim < end_dim; ++dim)
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
    max_dim = dim;
    return tree->neighbors;
}

vector<Guided_tree *> get_all_Guided_tree(Matrix<float> &points, AdjList &graph)
{
    vector<Guided_tree *> trees(points.rows);
    // #pragma omp parallel for
    for (int i = 0; i < points.rows; ++i)
    {
        int max_dim(0);
        trees[i] = get_Guided_tree(i, points, graph[i], 0, points.cols, max_dim);
    }
    cout << "get all Guided tree" << endl;
    return trees;
}

vector<vector<Guided_tree *>> get_all_Guided_forest(Matrix<float> &points, AdjList &graph)
{
    vector<vector<Guided_tree *>> forest(points.rows);
    for (int i = 0; i < points.rows; ++i)
    {
        int start_dim(0);
        int max_dim(0);
        vector<Guided_tree *> trees;
        while (start_dim < points.cols)
        {
            auto tree = get_Guided_tree(i, points, graph[i], start_dim, points.cols, max_dim);
            trees.push_back(tree);
            start_dim = max_dim;
        }
        forest[i] = trees;
    }
    cout << "get forest" << endl;
    return forest;
}



void print_tree_levels(Guided_tree *root, string pre)
{
    if (root == nullptr)
    {
        cout << "Empty tree" << endl;
        return;
    }
    if (root->pos != nullptr)
    {
        cout << pre << "pos:" << endl;
        print_tree_levels(root->pos, pre + "\t");
    }
    if (root->neg != nullptr)
    {
        cout << pre << "neg:" << endl;
        print_tree_levels(root->neg, pre + "\t");
    }
    if (root->is_leaf)
    {
        cout << pre << "[";
        for (auto e : root->neighbors)
        {
            cout << e << " ";
        }
        cout << "]" << endl;
    }
}