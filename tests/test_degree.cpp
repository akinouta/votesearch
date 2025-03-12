#include "search.h"
using namespace std;

int find_first_node_with_5_neighbors(const AdjList &graph) {
    // 遍历所有节点
    for (size_t i = 0; i < graph.size(); ++i) {
        if (graph[i].size() == 5) {  // 检查邻居数量是否为 5
            return i;  // 返回第一个符合条件的节点
        }
    }
    return -1;  // 如果没有找到，返回 -1
}

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


    auto start = std::chrono::high_resolution_clock::now();
    auto trees = get_all_Guided_tree(points, graph);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "trees Time taken: " << duration.count() << " milliseconds" << std::endl;


    start = std::chrono::high_resolution_clock::now();
    auto forest = get_all_Guided_forest(points, graph);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "forest Time taken: " << duration.count() << " milliseconds" << std::endl;


    int show = find_first_node_with_5_neighbors(graph);
    cout<<"cur:"<<show<<endl;
    for(auto neighbor:graph.at(show)){
        cout<<neighbor<<" ";
    }
    cout<<endl;

    for(auto tree:forest[show]){
        cout<<"tree:"<<endl;
        print_tree_levels(tree);
    }
}