/**
 * @file solution_e.cpp
 * @date 2025-09-13
 * @author Allie Phenish (alliephenish@gmail.com)
 * @brief Solution to a problem on the expected cost of a random string chain.
 * @details 
 * # Problem Description
 * We are given $n$ strings and a chain is formed by arranging them in a random permutation.
 * The cost of the chain is the sum of overlap lengths between adjacent strings. Specifically,
 * for a chain $s_{p_1}, s_{p_2}, \dots, s_{p_n}$, the cost is given by $\sum_{i=1}^{n-1} F(s_{p_i}, s_{p_{i+1}})$,
 * where $F(s_i, s_j)$ is the length of the longest suffix of $s_i$ that is also a prefix of $s_j$.
 * We need to find the expected cost of this chain modulo $10^9+7$.
 * # Algorithm
 * The problem can be solved by using the linearity of expectation. The expected cost of the chain
 * is the sum of the expected costs of each adjacent pair. For any two distinct strings $s_i$ and $s_j$,
 * the probability that they are adjacent in a random permutation is $1/(n-1)$.
 * The expected cost is therefore given by:
 * $E[\text{Cost}] = E[\sum_{i=1}^{n-1} F(s_{p_i}, s_{p_{i+1}})]$
 * $E[\text{Cost}] = \sum_{i=1}^{n-1} E[F(s_{p_i}, s_{p_{i+1}})]$
 * $E[\text{Cost}] = \sum_{i=1}^{n-1} \sum_{k \ne l} F(s_k, s_l) \times P(\text{s}_k\text{ at pos } i, \text{s}_l\text{ at pos } i+1)$
 * $E[\text{Cost}] = (n-1) \times \frac{1}{n(n-1)} \sum_{k \ne l} F(s_k, s_l) = \frac{1}{n} \sum_{k \ne l} F(s_k, s_l)$
 * The core task is to efficiently compute the sum of $F(s_k, s_l)$ for all ordered pairs of distinct strings.
 * A brute-force $O(N^2 \cdot \text{max\_len})$ approach is too slow given the constraints.
 * An efficient solution requires a specialized data structure that can handle all strings simultaneously. A
 * **Generalized Suffix Automaton (GSA)** is a suitable choice.
 * The GSA can be built on all $n$ strings. Each state in the GSA represents a set of substrings
 * that are common to the input strings. By traversing the GSA's trie-like structure and its
 * suffix links, we can efficiently count for each substring `p` the number of times it appears as
 * a prefix and the number of times it appears as a suffix in the original strings.
 * The total sum can then be computed by iterating through all states of the GSA and accumulating
 * the contributions based on these counts, carefully handling the "longest" overlap condition.
 * All calculations are performed modulo $10^9+7$.
 * # Input
 * - The first line contains a single integer $n$ ($2 \le n \le 2 \times 10^5$), the number of strings.
 * - The next $n$ lines each contain a single string $s_i$ ($1 \le |s_i| \le 10^6$).
 * - The sum of all string lengths $\sum|s_i|$ does not exceed $10^6$.
 * # Output
 * - A single integer representing the expected cost modulo $10^9+7$.
 */