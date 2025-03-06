/*
 * Author: Nino Bašić <nino.basic@upr.si>
 *
 * Read digraph6 strings from the standard input and print those that are dextro-nut digraphs.
 */

#include <cstdio>
#include "nut_tools.h"
using namespace std;

#define MAX_LEN 1024  // Max length for input lines
#define N_MAX 62  // Max order of a graph

int main() {
	char line[MAX_LEN];
	int n;
	arma::mat A = arma::mat(10, 10);  // Adjacency matrix of digraph
	arma::mat A_rev = arma::mat(10, 10);  // Adjacency matrix of reverse digraph
	arma::vec ker, co_ker;
	int in_deg[N_MAX];
	int out_deg[N_MAX];
	bool is_dextro_nut;
	long long digraph_count = 0;
	long long dextronut_digraph_count = 0;

	while (fgets(line, sizeof(line), stdin)) {
		rstrip(line);
		if (strlen(line) == 0) continue;  // Skip blank lines
		parse_digraph6(line, A, A_rev, n, in_deg, out_deg);
		digraph_count++;
		is_dextro_nut = is_dextro_nut_digraph(n, A, ker);
		if (is_dextro_nut) {
			printf("%s\n", line);
			dextronut_digraph_count++;
		}
	}
	fprintf(stderr, "> Total number of digraphs parsed: %lld\n", digraph_count);
	fprintf(stderr, "> Total number of dextro-nut digraphs: %lld\n", dextronut_digraph_count);
	return 0;
}
