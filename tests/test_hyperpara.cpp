#include "search.h"
using namespace std;

int main(int argc, char **argv)
{

    // argv[1]: dataset file
    // argv[2]: queries file
    // argv[3]: ground-truth file
    // argv[4]: graph file
    // argv[5]: K, number of neighbors
    // argv[6]: maximum number of calculations

    int N, Dim, num_queries, nn_gt;

    string file_dataset(argv[1]);
    string file_queries(argv[2]);
    string file_gt(argv[3]);
    string file_graph(argv[4]);
    int K = atoi(argv[5]);
    int max_calc = atoi(argv[6]);
    int L = atoi(argv[7]);

    Matrix<float> points = read_fvecs(file_dataset, N, Dim);
    printf("base read (%d,%d) ...\n", N, Dim);
    Matrix<float> queries = read_fvecs(file_queries, num_queries, Dim);
    printf("queries read (%d,%d)...\n", num_queries, Dim);
    vector<vector<int>> gt = read_ivecs(file_gt, num_queries, nn_gt);
    printf("groundtruth read...\n");

    AdjList graph = read_adjlist(file_graph, points, true);


    // auto trees = get_all_Guided_tree(points, graph);



    auto forest = get_all_Guided_forest(points, graph);



}