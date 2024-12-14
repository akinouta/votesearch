#if defined(_MSC_VER) // Visual studio
#define thread_local __declspec(thread)
#elif defined(__GCC__) // GCC
#define thread_local __thread
#endif

#include "search.h"

using namespace std;

tuple<vector<int>, vector<float>> search_KNN(float *query, int K, AdjList &graph, Matrix<float> &points, int start, int max_calc)
{
	int N = points.rows;
	int calc_left = max_calc - 1;
	unordered_set<int> visited;
	visited.insert(start);
	priority_queue<tuple<float, int>> q, knn;
	float furthest_dist = dist_L2(points[start], query, points.cols);
	q.push(make_tuple(-furthest_dist, start));
	knn.push(make_tuple(furthest_dist, start));
	while (!q.empty() && calc_left > 0)
	{
		float d;
		int v;
		tie(d, v) = q.top();
		q.pop();
		for (int u : graph[v])
		{
			if (calc_left <= 0)
				break;
			if (in_set(u, visited))
				continue;
			visited.insert(u);
			d = dist_L2(points[u], query, points.cols);
			calc_left--;
			q.push(make_tuple(-d, u));
			knn.push(make_tuple(d, u));
			if (knn.size() > K)
				knn.pop();
		}
	}

	vector<int> nearests;
	vector<float> dists;
	while (!knn.empty())
	{
		float x;
		int y;
		tie(x, y) = knn.top();
		nearests.push_back(y);
		dists.push_back(x);
		knn.pop();
	}
	reverse(nearests.begin(), nearests.end());
	reverse(dists.begin(), dists.end());
	return make_tuple(nearests, dists);
}

void run_on_testset(Matrix<float> &queries, int K, Matrix<float> &points, vector<vector<int>> &GT, AdjList &graph, int max_calc)
{
	float recall = 0;
	int N = points.rows;
	int num_queries = queries.rows;

	#pragma omp parallel for
	for (int i = 0; i < num_queries; i++)
	{
		int start = rand_int(0, N - 1);
		auto knn = search_KNN(queries[i], K, graph, points, start, max_calc);
		#pragma omp critical
		{
			// vector<float> aux(K);
			// for(int j=0; j<K; j++)
			// 	aux[j] = dist_L2(points[GT[i][j]], queries[i], points.cols);
			// recall += get_recall_dist(aux, get<1>(knn));
			recall += get_recall(GT[i], get<0>(knn), K);
		}
	}
	printf("Recall@%d(%d):\t%.2lf\n", K, max_calc, recall * 100 / num_queries);
}
