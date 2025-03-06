#ifndef NUT_TOOLS_H
#define NUT_TOOLS_H

#define ARMA_DONT_USE_WRAPPER
#include <armadillo>

#define TOLERANCE 1e-10

// Helper functions
bool same_vector(arma::vec v1, arma::vec v2);

// Nuts and dinuts
bool is_nut_graph(int n, arma::mat &A, arma::vec &ker);
bool is_dextro_nut_digraph(int n, arma::mat &A, arma::vec &ker);

// Cores
bool is_dextro_core_digraph(int n, arma::mat &A);
bool is_core_graph(int n, arma::mat &A);

// Graph6 and related formats
void parse_graph6(char *s, arma::mat &A, int &n, int deg[]);
void parse_digraph6(char *s, arma::mat &A, arma::mat &R, int &n, int in_deg[], int out_deg[]);

// Miscellanea
void rstrip(char *c);

#endif
