#!/usr/bin/env sage
import sys
from sage.all import *

'''
Author: Nino Bašić <nino.basic@upr.si>

Read digraphs in the digraph6 format from the standard input.
Output all gadgets that are not ambi-nut digraphs, one per line.
The following information is printed (separated by spaces):

 * digraph (in the digraph6 format);
 * the root vertex;
 * the demand (as a fraction).

To find all gadgets of a given order, e.g. 6, execute the following:

$ geng -c 6 | directg -o | ./find_gadgets.py
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

def get_dextro(g):
    '''
    Return the kernel eigenvector of the digraph g if g is a dextro-nut
    digraph; otherwise return None.
    '''
    d = g.adjacency_matrix()
    ker = d.right_kernel()
    if ker.dimension() != 1:
        return None  # Nullity is not 1
    kev = ker.basis()[0]
    if any(x == 0 for x in kev):
        return None  # 0 in the kernel eigenvector
    return kev

def get_laevo(g):
    '''
    Return the co-kernel eigenvector of the digraph g if g is a laevo-nut
    digraph; otherwise return None.
    '''
    d = g.adjacency_matrix()
    ker = d.left_kernel()
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

def is_gadget(g, u):
    '''
    Return the demand (as a fraction) if digraph g is a gadget with root r;
    otherwise return None.
    '''
    n = g.order()
    g = g.copy(immutable=True)
    A = g.adjacency_matrix()[list(range(u)) + list(range(u + 1, n)), range(n)]
    B = g.adjacency_matrix().transpose()[list(range(u)) + list(range(u + 1, n)), range(n)]
    dex = get_kernel(A)
    if dex is None:
        return None
    lae = get_kernel(B)
    if lae is None:
        return None
    if not same_vector(dex, lae):
        return None
    out_sum = sum(dex[x] for x in g.neighbors_out(u))
    return -out_sum/dex[u]

if __name__ == '__main__':
    gadget_count = 0
    frequencies_by_demand = {}
    for line in sys.stdin:
        di6s = line.strip()
        if di6s[0] == '&':
            di6s = di6s[1:]
        g = DiGraph(di6s)
        kernel_vector = get_dextro(g)
        cokernel_vector = get_laevo(g)
        if (kernel_vector is not None and 
                cokernel_vector is not None and 
                same_vector(kernel_vector, cokernel_vector)):
            continue  # Graph g is an ambi-nut digraph and we skip it
        for u in g:
            demand = is_gadget(g, u)
            if demand is None:
                continue
            print(di6s, u, demand)
            gadget_count += 1
            frequencies_by_demand[demand] = frequencies_by_demand.get(demand, 0) + 1
    print(f'> Number of gadgets found: {gadget_count}', file=sys.stderr)
    print('> Stratification by demand:', file=sys.stderr)
    for dem in sorted(frequencies_by_demand):
        print(f'> \tDemand: {dem} \tCount: {frequencies_by_demand[dem]}', file=sys.stderr)
