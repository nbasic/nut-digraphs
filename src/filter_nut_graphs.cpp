/*
 * Author: Nino Bašić <nino.basic@upr.si>
 *
 * Read graph6 strings from the standard input and print those that are nut graphs.
 */

#include <cstdio>
#include "nut_tools.h"
using namespace std; 

#define MAX_LEN 1024  // Max length for input lines
#define N_MAX 62  // Max order of a graph

int main() {
	char line[MAX_LEN];
	int n;
	arma::mat A = arma::mat(10, 10);
	arma::vec ker;
	int deg[N_MAX];
	bool is_nut;
	long long graph_count = 0;
	long long nut_graph_count = 0;

	while (fgets(line, sizeof(line), stdin)) {
		rstrip(line);
		if (strlen(line) == 0) continue;  // Skip blank lines
		parse_graph6(line, A, n, deg);
		graph_count++;
		is_nut = is_nut_graph(n, A, ker);
		if (is_nut) {
			printf("%s\n", line);
			nut_graph_count++;
		}
	}
	fprintf(stderr, "> Total number of graphs parsed: %lld\n", graph_count);
	fprintf(stderr, "> Total number of nut graphs: %lld\n", nut_graph_count);
	return 0;
}
