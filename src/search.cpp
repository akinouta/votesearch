#if defined(_MSC_VER) // Visual studio
#define thread_local __declspec(thread)
#elif defined(__GCC__) // GCC
#define thread_local __thread
#endif

#include "search.h"
#include "guided_structure.h"
#include <unordered_map>

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

tuple<vector<int>, vector<float>> search_KNN_by_Guided_tree(float *query, int K, AdjList &graph, Matrix<float> &points, vector<Guided_tree *> &trees, int start, int max_calc)
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
		int max_dim(0);
		tie(d, v) = q.top();
		q.pop();
		vector<int> neighbors = find_neighbors(query, v, trees[v], points, 0, points.cols, max_dim);
		for (int u : neighbors)
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

tuple<vector<int>, vector<float>> search_KNN_two_phase(float *query, int K, AdjList &graph, Matrix<float> &points, vector<Guided_tree *> &trees, int start, int max_calc, int L)
{
	int N = points.rows;
	int calc_left = max_calc - 1;
	unordered_set<int> visited;
	visited.insert(start);
	priority_queue<tuple<float, int>> q, knn;
	float furthest_dist = dist_L2(points[start], query, points.cols);
	q.push(make_tuple(-furthest_dist, start));
	knn.push(make_tuple(furthest_dist, start));
	while (q.size() < L && !q.empty() && calc_left > 0)
	{
		float d;
		int v;
		int max_dim(0);

		tie(d, v) = q.top();
		q.pop();
		vector<int> neighbors = find_neighbors(query, v, trees[v], points, 0, points.cols, max_dim);
		for (int u : neighbors)
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

tuple<vector<int>, vector<float>> search_KNN_two_phase_nn(float *query, int K, AdjList &graph, Matrix<float> &points, vector<Guided_tree *> &trees, int start, int max_calc, int L)
{
	int N = points.rows;
	int calc_left = max_calc - 1;
	unordered_set<int> visited;
	visited.insert(start);
	priority_queue<tuple<float, int>> q, knn;
	float furthest_dist = dist_L2(points[start], query, points.cols);
	q.push(make_tuple(-furthest_dist, start));
	knn.push(make_tuple(furthest_dist, start));
	while (q.size() < L && !q.empty() && calc_left > 0)
	{
		float d;
		int v;
		int max_dim(0);
		tie(d, v) = q.top();
		q.pop();
		vector<int> neighbors = find_neighbors(query, v, trees[v], points, 0, points.cols, max_dim);
		for (int u : neighbors)
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

	while (!q.empty() && calc_left > 0)
	{
		float d;
		int v;
		tie(d, v) = q.top();
		q.pop();
		// get neighbors' neighbors

		unordered_set<int> nns(graph[v].begin(), graph[v].end());

		for (auto n : graph[v])
		{
			for (auto nn : graph[n])
			{
				nns.insert(nn);
			}
		}

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

tuple<vector<int>, vector<float>> search_KNN_vote(float *query, int K, AdjList &graph, Matrix<float> &points, vector<vector<Guided_tree *>> &forest, int start, int max_calc, int L)
{
	int new_start = start;
	int N = points.rows;
	int calc_left = max_calc - 1;
	unordered_set<int> visited;
	visited.insert(start);
	priority_queue<tuple<float, int>> q, knn;


	// find new start
	for (int i = 0; i < L; ++i)
	{
		auto trees = forest[new_start];
		unordered_map<int, int> counters;
		int max_dim(0);
		for (auto tree : trees)
		{
			vector<int> neighbors = find_neighbors(query, new_start, tree, points, 0, points.cols, max_dim);
			for (auto neighbor : neighbors)
			{
				counters[neighbor] += 1;
			}
		}

		int max_n = numeric_limits<int>::min();
		for (const auto &pair : counters)
		{
			if (pair.second > max_n)
			{
				max_n = pair.second;
			}
		}
		new_start = max_n;
	}
	start = new_start;

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

// no calc
tuple<vector<int>, vector<float>> search_KNN_vote(float *query, int K, AdjList &graph, Matrix<float> &points, vector<vector<Guided_tree *>> &forest, int start, int L)
{
	int new_start = start;
	int N = points.rows;
	unordered_set<int> visited;
	visited.insert(start);
	priority_queue<tuple<float, int>> q, knn;


	// find new start
	for (int i = 0; i < L; ++i)
	{
		auto trees = forest[new_start];
		unordered_map<int, int> counters;
		int max_dim(0);
		for (auto tree : trees)
		{
			vector<int> neighbors = find_neighbors(query, new_start, tree, points, 0, points.cols, max_dim);
			for (auto neighbor : neighbors)
			{
				counters[neighbor] += 1;
			}
		}

		int max_n = numeric_limits<int>::min();
		for (const auto &pair : counters)
		{
			if (pair.second > max_n)
			{
				max_n = pair.second;
			}
		}
		new_start = max_n;
	}
	start = new_start;

	float furthest_dist = dist_L2(points[start], query, points.cols);
	q.push(make_tuple(-furthest_dist, start));
	knn.push(make_tuple(furthest_dist, start));

	while (!q.empty())
	{
		float d;
		int v;
		tie(d, v) = q.top();
		q.pop();
		for (int u : graph[v])
		{
			if (in_set(u, visited))
				continue;
			visited.insert(u);
			d = dist_L2(points[u], query, points.cols);
			q.push(make_tuple(-d, u));
			knn.push(make_tuple(d, u));
			if (knn.size() > K)
				knn.pop();
		}

		float b;
		int vb;
		tie(b,vb) = knn.top();
	
		if (knn.size() >= K && b>d)
		{
			break;
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


void test_without_guide(Matrix<float> &queries, int K, Matrix<float> &points, vector<vector<int>> &GT, AdjList &graph, int max_calc, int start)
{
	float recall = 0;
	int N = points.rows;
	int num_queries = queries.rows;

#pragma omp parallel for
	for (int i = 0; i < num_queries; i++)
	{
		if (start < 0)
		{
			start = rand_int(0, N - 1);
		}
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
	print_recall(K, max_calc, num_queries, recall);
}

void test_Guided_tree(Matrix<float> &queries, int K, Matrix<float> &points, vector<vector<int>> &GT, AdjList &graph, vector<Guided_tree *> &trees, int max_calc, int start)
{
	float recall = 0;
	int N = points.rows;
	int num_queries = queries.rows;

#pragma omp parallel for
	for (int i = 0; i < num_queries; i++)
	{
		if (start < 0)
		{
			start = rand_int(0, N - 1);
		}
		auto knn = search_KNN_by_Guided_tree(queries[i], K, graph, points, trees, start, max_calc);
#pragma omp critical
		{
			// vector<float> aux(K);
			// for(int j=0; j<K; j++)
			// 	aux[j] = dist_L2(points[GT[i][j]], queries[i], points.cols);
			// recall += get_recall_dist(aux, get<1>(knn));
			recall += get_recall(GT[i], get<0>(knn), K);
		}
	}
	print_recall(K, max_calc, num_queries, recall);
}

void test_two_phase(Matrix<float> &queries, int K, Matrix<float> &points, vector<vector<int>> &GT, AdjList &graph, vector<Guided_tree *> &trees, int max_calc, int start, int L)
{
	float recall = 0;
	int N = points.rows;
	int num_queries = queries.rows;

#pragma omp parallel for
	for (int i = 0; i < num_queries; i++)
	{
		if (start < 0)
		{
			start = rand_int(0, N - 1);
		}
		auto knn = search_KNN_two_phase(queries[i], K, graph, points, trees, start, max_calc, L);
#pragma omp critical
		{
			// vector<float> aux(K);
			// for(int j=0; j<K; j++)
			// 	aux[j] = dist_L2(points[GT[i][j]], queries[i], points.cols);
			// recall += get_recall_dist(aux, get<1>(knn));
			recall += get_recall(GT[i], get<0>(knn), K);
		}
	}
	print_recall(K, max_calc, num_queries, recall);
}

void test_two_phase_nn(Matrix<float> &queries, int K, Matrix<float> &points, vector<vector<int>> &GT, AdjList &graph, vector<Guided_tree *> &trees, int max_calc, int start, int L)
{
	float recall = 0;
	int N = points.rows;
	int num_queries = queries.rows;

#pragma omp parallel for
	for (int i = 0; i < num_queries; i++)
	{
		if (start < 0)
		{
			start = rand_int(0, N - 1);
		}
		auto knn = search_KNN_two_phase_nn(queries[i], K, graph, points, trees, start, max_calc, L);
#pragma omp critical
		{
			// vector<float> aux(K);
			// for(int j=0; j<K; j++)
			// 	aux[j] = dist_L2(points[GT[i][j]], queries[i], points.cols);
			// recall += get_recall_dist(aux, get<1>(knn));
			recall += get_recall(GT[i], get<0>(knn), K);
		}
	}
	print_recall(K, max_calc, num_queries, recall);
}

void test_vote(Matrix<float> &queries, int K, Matrix<float> &points, vector<vector<int>> &GT, AdjList &graph, vector<vector<Guided_tree *>> &forest, int max_calc, int start, int L)
{
	float recall = 0;
	int N = points.rows;
	int num_queries = queries.rows;

#pragma omp parallel for
	for (int i = 0; i < num_queries; i++)
	{
		if (start < 0)
		{
			start = rand_int(0, N - 1);
		}
		auto knn = search_KNN_vote(queries[i], K, graph, points, forest, start, max_calc, L);
#pragma omp critical
		{
			// vector<float> aux(K);
			// for(int j=0; j<K; j++)
			// 	aux[j] = dist_L2(points[GT[i][j]], queries[i], points.cols);
			// recall += get_recall_dist(aux, get<1>(knn));
			recall += get_recall(GT[i], get<0>(knn), K);
		}
	}
	print_recall(K, max_calc, num_queries, recall);
}