#include "hcnng.h"

using namespace std;

int main(int argc, char **argv)
{

	// argv[1]: dataset file
	// argv[2]: min size cluster
	// argv[3]: number of clusters
	// argv[4]: graph file

	int N, Dim;
	string file_dataset(argv[1]);
	int minsize_cl = atoi(argv[2]);
	int num_cl = atoi(argv[3]);
	int max_mst_degree = 3;
	string file_graph(argv[4]);

	printf("\n***************************\n");
	printf("MIN SZ CL:\t%d\n", minsize_cl);
	printf("NUMBER CL:\t%d\n", num_cl);
	printf("***************************\n\n");

	Matrix<float> points = read_fvecs(file_dataset, N, Dim);
	printf("base read (%d,%d) ...\n", N, Dim);
	Graph nngraph = HCNNG_create_graph(points, Dim, num_cl, minsize_cl, max_mst_degree);
	
	write_graph(file_graph, nngraph);
	return 0;
}
