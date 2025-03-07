#!/usr/bin/env sage
import sys
from sage.all import *

'''
Author: Nino Bašić <nino.basic@upr.si>

The program take one command-line argument: the eigenvalue EIG_VAL.
Read digraphs in the digraph6 format from the standard input.
Output all base digraphs for the eigenvalue EIG_VAL, one per line.
The following information is printed (separated by spaces):

 * digraph (in the digraph6 format);
 * the full vector of the corresponding eigenspace.

Note: Diregular digraphs of degree k = EIG_VAL are skipped.
Bipartite diregular digraphs of degree k = -EIG_VAL are also skipped.

To find all base digraphs of a given order, e.g. 6, for a given eigenvalue,
e.g. -1, execute the following:

$ geng -c 6 | directg -o | ./find_base_digraphs.py -1
'''

def get_kernel(M):
    '''
    If the kernel of the matrix M is spanned by a full vector, return that
    kernel eigenvector; otherwise return None.
    '''
    ker = M.right_kernel()
    if ker.dimension() != 1:
        return None  # Nullity is not 1
    kev = ker.basis()[0]
    if any(x == 0 for x in kev):
        return None  # 0 in the kernel eigenvector
    return kev

def same_vector(v1, v2):
    '''
    Return True iff vectors v1 and v2 are linearly dependent (i.e., the same
    up to scalar multiplication).
    '''
    n = len(v1)
    q = v1[0] / v2[0]
    for i in range(1, n):
        if v1[i] / v2[i] != q:
            return False
    return True

def is_base_digraph(g, eig_value):
    '''
    Return the eigenvector of the digraph g if it is a base graph for the
    eigenvalue eig_value; otherwise return None.
    '''
    n = g.order()
    A = g.adjacency_matrix() - eig_value * identity_matrix(n)
    B = g.adjacency_matrix().transpose() - eig_value * identity_matrix(n)
    dex = get_kernel(A)
    if dex is None:
        return None
    lae = get_kernel(B)
    if lae is None:
        return None
    if not same_vector(dex, lae):
        return None
    return dex

def compact_format(vec):
    '''
    Return the vector vec in a 'compact' form.
    '''
    return '(' + ','.join(str(x) for x in vec) + ')'

def is_k_diregular(g):
    '''
    If the digraph is k-diregular for some k, return the value k.
    If it is not diregular, return None.
    '''
    in_deg = g.in_degree()
    if len(set(in_deg)) > 1:
        return None
    out_deg = g.out_degree()
    if len(set(out_deg)) > 1:
        return None
    return in_deg[0]

if __name__ == '__main__':
    EIG_VAL = int(sys.argv[1])

    base_graph_count = 0
    skip_count = 0
    for line in sys.stdin:
        di6s = line.strip()
        if di6s[0] == '&':
            di6s = di6s[1:]
        g = DiGraph(di6s)
        eig_vec = is_base_digraph(g, EIG_VAL)

        if eig_vec is not None:
            k = is_k_diregular(g)
            if k is not None and k == EIG_VAL:
                skip_count += 1
                continue  # Skip diregular digraphs
            bipartite = g.is_bipartite()
            if bipartite and k is not None and k == -EIG_VAL:
                skip_count += 1
                continue  # Skip bipartite diregular digraphs
            print(di6s, compact_format(eig_vec))
            base_graph_count += 1

    print(f'> Number of base digraphs found: {base_graph_count}', file=sys.stderr)
    print(f'> Number of digraphs skipped: {skip_count}', file=sys.stderr)
