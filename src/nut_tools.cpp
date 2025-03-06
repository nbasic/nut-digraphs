/*
 * Author: Nino Bašić <nino.basic@upr.si>
 */

#include "nut_tools.h"
#include <cctype>

bool same_vector(arma::vec v1, arma::vec v2) {
	/*
	 * Return true iff v1 and v2 are the same vectors up to scalar multiplication.
	 */
	unsigned long long n = v1.n_elem;
	if (v2.n_elem != n) return false;
	double q = v1(0) / v2(0);
	double q_here;
	for (unsigned long long i=1; i<n; i++) {
		q_here = v1(i) / v2(i);
		if (!(fabs(q - q_here) < TOLERANCE)) return false;
	}
	return true;
}

bool is_dextro_core_digraph(int n, arma::mat &A) {
	/*
	 * Return true iff A is the adjacency matrix of a dextro-core digraph.
	 */
	arma::mat B = arma::null(A);
	int nullity = B.n_cols;
	if (nullity < 1) return false;
	for (int i=0; i<n; i++) {
		bool is_good_vertex = false;
		for (int j=0; j<nullity; j++) {
			if (fabs(B(i, j)) > TOLERANCE) {  // Is there a non-zero entry?
				is_good_vertex = true;
				break;
			}
		}
		if (!is_good_vertex) return false;  // Has a core-forbidden vertex
	}
	return true;
}

bool is_core_graph(int n, arma::mat &A) {
	/*
	 * Return true iff A is the adjacency matrix of a core graph.
	 */
	return is_dextro_core_digraph(n, A);
}

bool is_dextro_nut_digraph(int n, arma::mat &A, arma::vec &ker) {
	/*
	 * Return true iff A is the adjacency matrix of a dextro-nut digraph.
	 * In case it is a dextro-nut digraph, set ker to the kernel eigenvector.
	 */
	arma::mat B = arma::null(A);
	int nullity = B.n_cols;
	if (nullity != 1) return false;
	for (int i=0; i<n; i++) {
		if (fabs(B(i, 0)) < TOLERANCE) return false;  // Is it a zero entry?
	}
	ker = arma::vectorise(B);
	return true;
}

bool is_nut_graph(int n, arma::mat &A, arma::vec &ker) {
	/*
	 * Return true iff A is the adjacency matrix of a nut graph.
	 * In case it is a nut graph, set ker to the kernel eigenvector.
	 */
	return is_dextro_nut_digraph(n, A, ker);
}

const int mold[] = {0b100000, 0b010000, 0b001000, 0b000100, 0b000010, 0b000001};

void parse_graph6(char *s, arma::mat &A, int &n, int deg[]) {
	/*
	 * Given a string s that contains a graph in the graph6 format, parse it and
	 * set A to its adjacency matrix. Also find the order of the graph and degrees of
	 * all vertices.
	 * Note: In the current implementation, digraphs may contain at most 62 vertices.
	 */
	int p = 0, v = 0, u = 1;
	if (s[p] == '&') p++;
	if (s[p] == 126) {
		printf("Not implemented: Graphs may contain at most 62 vertices.\n");
		exit(1);
	}
	n = s[p] - 63;
	p++;
	int char_follow = (n * (n - 1) / 2 + 5) / 6;  // How many characters should follow N(n)?
	A.set_size(n, n);
	for (int i=0; i<n; i++) deg[i] = 0;
	int fragment;
	while (char_follow--) {
		fragment = s[p] - 63;
		for (int i=0; i<6; i++) {
			if (fragment & mold[i]) {  // Is edge u -> v present?
				A(u, v) = 1.0;
				A(v, u) = 1.0;
				deg[u]++;
				deg[v]++;
			} else {
				A(u, v) = 0.0;
				A(v, u) = 0.0;
			}
			v++;
			if (v == u) { u++; v = 0; }
			if (u == n) break;
		}
		p++;
	}
}

void parse_digraph6(char *s, arma::mat &A, arma::mat &R, int &n, int in_deg[], int out_deg[]) {
	/*
	 * Given a string s that contains a digraph in the digraph6 format, parse it and
	 * set A to its adjacency matrix and R to the adjacency matrix of the reverse digraph.
	 * Also find the order of the digraph and in-degrees and out-degrees of all vertices.
	 * Note: In the current implementation, digraphs may contain at most 62 vertices.
	 */
	int p = 0, u = 0, v = 0;
	if (s[p] == '&') p++;
	if (s[p] == 126) {
		printf("Not implemented: Digraphs may contain at most 62 vertices.\n");
		exit(1);
	}
	n = s[p] - 63;
	p++;
	int char_follow = (n * n + 5) / 6;  // How many characters should follow N(n)?
	A.set_size(n, n);
	R.set_size(n, n);
	for (int i=0; i<n; i++) in_deg[i] = out_deg[i] = 0;
	int fragment;
	while (char_follow--) {
		fragment = s[p] - 63;
		for (int i=0; i<6; i++) {
			if (fragment & mold[i]) {  // Is edge u -> v present?
				A(u, v) = 1.0;
				R(v, u) = 1.0;
				out_deg[u]++;
				in_deg[v]++;
			} else {
				A(u, v) = 0.0;
				R(v, u) = 0.0;
			}
			v++;
			if (v == n) { u++; v = 0; }
			if (u == n) break;
		}
		p++;
	}
}

void rstrip(char *c) {
	/*
	 * Removes trailing whitespace characters from the string c.
	 */
	int len = strlen(c);
	while (len > 0 && isspace(c[len - 1])) {
		c[len - 1] = '\0';
		len--;
	}
}
