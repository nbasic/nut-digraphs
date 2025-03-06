# Nut digraphs

Supplementary material for the Nut digraphs paper.

To enumerate nut digraphs we use the [nauty and Traces](https://pallini.di.uniroma1.it/) software and the **Nut tools** package (provided in the present repository).

## Examples and enumeration

Nut digraphs among oriented graphs of order $n \leq 8$.

Files containing dextro-nut digraphs are located in the `data` folder and are named `dextronut_digraphsN.d6`, where `N` is the
order of the digraph. Similar conventions apply to files containing bi-nut and ambi-nut digraphs. Each line of a file contains one
digraph in the **digraph6** format. For description of the format see Chapter 20 in the
[nauty and Traces User's Guide](https://pallini.di.uniroma1.it/Guide.htmlhttps://pallini.di.uniroma1.it/Guide.html).

| n  | Undirected | Oriented        | Dextro-nut                           | Bi-nut                          | Ambi-nut                          |
| -: | ---------: | --------------: | -----------------------------------: | ------------------------------: | --------------------------------: |
| 3  | 2          | 5               | 0                                    | 0                               | 0                                 |
| 4  | 6          | 34              | [1](data/dextronut_digraphs4.d6)     | 0                               | 0                                 |
| 5  | 21         | 535             | [4](data/dextronut_digraphs5.d6)     | 0                               | 0                                 |
| 6  | 112        | 20848           | [153](data/dextronut_digraphs6.d6)   | [2](data/binut_digraphs6.d6)    | [2](data/ambinut_digraphs6.d6)    |
| 7  | 853        | 2120098         | [17170](data/dextronut_digraphs7.d6) | [21](data/binut_digraphs7.d6)   | [1](data/ambinut_digraphs7.d6)    |
| 8  | 11117      | 572849763       | 5579793                              | [9592](data/binut_digraphs8.d6) | [104](data/ambinut_digraphs8.d6)  |
| 9  | 261080     | 415361983540    | ?                                    | ?                               | [3371](data/ambinut_digraphs9.d6) |
| 10 | 11716571   | 815590925440865 | ?                                    | ?                               | 1404682                           |

To obtain, e.g., dextro-nut digraphs among oriented graphs on 6 vertices, execute:

```bash
geng -c 6 | directg -o | ./filter_dextronut_digraphs
```

For bi-nut digraphs (or ambi-nut digraphs) use `filter_binut_digraphs` (or `filter_ambinut_digraphs`) instead of `filter_dextronut_digraphs`.

Nut digraphs among 4-regular oriented graphs of order $n \leq 11$.

| n   | Undirected | Oriented  | Dextro-nut                                    | Bi-nut                                   | Ambi-nut                                  |
| --: | ---------: | --------: | --------------------------------------------: | ---------------------------------------: | ----------------------------------------: |
| 5   | 1          | 12        | 0                                             | 0                                        | 0                                         |
| 6   | 1          | 112       | [4](data/quartic_dextronut_digraphs6.d6)      | [2](data/quartic_binut_digraphs6.d6)     | [2](data/quartic_ambinut_digraphs6.d6)    |
| 7   | 2          | 1602      | [9](data/quartic_dextronut_digraphs7.d6)      | 0                                        | 0                                         |
| 8   | 6          | 32263     | [202](data/quartic_dextronut_digraphs8.d6)    | [27](data/quartic_binut_digraphs8.d6)    | [5](data/quartic_ambinut_digraphs8.d6)    |
| 9   | 16         | 748576    | [2255](data/quartic_dextronut_digraphs9.d6)   | 0                                        | 0                                         |
| 10  | 59         | 19349594  | [33034](data/quartic_dextronut_digraphs10.d6) | [2072](data/quartic_binut_digraphs10.d6) | [32](data/quartic_ambinut_digraphs10.d6)  |
| 11  | 265        | 548123668 | 436947                                        | 0                                        | 0                                         |
| 12  | 1544       | ?         | ?                                             | ?                                        | [860](data/quartic_ambinut_digraphs12.d6) |
| 13  | 10778      | ?         | ?                                             | 0                                        | 0                                         |
| 14  | 88168      | ?         | ?                                             | ?                                        | [?](data/quartic_ambinut_digraphs14.d6)   |
| 15  | 805491     | ?         | ?                                             | 0                                        | 0                                         |

To obtain, e.g., quartic dextro-nut digraphs among oriented graphs on 8 vertices, execute:

```bash
geng -c -d4D4 8 | directg -o | ./filter_dextronut_digraphs
```

Nut digraphs among tournaments of order $n \leq 11$.

| n  | Tournaments  | Dextro-nut                             | Bi-nut                               | Ambi-nut |
| -: | -----------: | -------------------------------------: | -----------------------------------: | -------: |
| 4  | 4            | [1](data/dextronut_tournaments4.d6)    | 0                                    | 0        |
| 5  | 12           | 0                                      | 0                                    | 0        |
| 6  | 56           | [3](data/dextronut_tournaments6.d6)    | 0                                    | 0        |
| 7  | 456          | [9](data/dextronut_tournaments7.d6)    | 0                                    | 0        |
| 8  | 6880         | [119](data/dextronut_tournaments8.d6)  | 0                                    | 0        |
| 9  | 191536       | [2373](data/dextronut_tournaments9.d6) | [10](data/binut_tournaments9.d6)     | 0        |
| 10 | 9733056      | 90782                                  | [567](data/binut_tournaments10.d6)   | 0        |
| 11 | 903753248    | 5918592                                | [26629](data/binut_tournaments11.d6) | 0        |

It is shown in the paper that ambi-nut tournaments do not exist (see Proposition 10).

To obtain, e.g., dextro-nut digraph among tournaments on 8 vertices, execute:

```bash
gentourng -z 8 | ./filter_dextronut_digraphs
```

## Multiplier constructions

We provide examples of **base digraphs** and **gadgets** for the multiplier construction (see Theorem 37).

