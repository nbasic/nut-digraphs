# Nut digraphs

Supplementary material for the Nut digraphs paper.

To enumerate nut digraphs we use the [nauty and Traces](https://pallini.di.uniroma1.it/) software and the **Nut tools** package (provided in the present repository).

## Examples and enumeration

Nut digraphs among orianted graphs of order $n \leq 8$.

| n  | Undirected | Oriented  | Dextro-nut                           | Bi-nut | Ambi-nut |
| -: | ---------: | --------: | -----------------------------------: | -----: | -------: |
| 3  | 2          | 5         | 0                                    | 0      | 0        |
| 4  | 6          | 34        | [1](data/dextronut_digraphs4.d6)     | 0      | 0        |
| 5  | 21         | 535       | [4](data/dextronut_digraphs5.d6)     | 0      | 0        |
| 6  | 112        | 20848     | [153](data/dextronut_digraphs6.d6)   | 2      | 2        |
| 7  | 853        | 2120098   | [17170](data/dextronut_digraphs7.d6) | 21     | 1        |
| 8  | 11117      | 572849763 | ?                                    | ?      | ?        |

To obtain, e.g., dextro-nut digraphs among oriented graphs on 6 vertices, execute:

```bash
geng -c 6 | directg -o | ./filter_dextronut_digraphs
```

For bi-nut digraphs (or ambi-nut digraphs) use `filter_binut_digraphs` (or `filter_ambinut_digraphs`) instead of `filter_dextronut_digraphs`.
