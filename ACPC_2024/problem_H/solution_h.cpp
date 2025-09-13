#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <map>

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
 * The GSA is built by concatenating all strings with unique separator characters. Each state in the GSA
 * represents a set of substrings that are common to the input strings. By traversing the GSA's trie-like
 * structure and its suffix links, we can efficiently count for each substring `p` the number of times it
 * appears as a prefix (`cnt_pref[u]`) and the number of times it appears as a suffix (`cnt_suf[u]`) in the
 * original strings.
 * The total sum for all pairs (including $k=l$) can be computed by iterating through all states `u` of the GSA:
 * $\sum_{k,l} F(s_k, s_l) = \sum_{u} (\text{len}(u) - \text{len}(\text{link}(u))) \times \text{cnt\_suf}[u] \times \text{cnt\_pref}[u]$
 * We then must subtract the cost for pairs where the strings are the same, i.e., $\sum_{k=1}^n F(s_k, s_k)$.
 * $F(s_k, s_k)$ is the length of the longest proper suffix of $s_k$ that is a prefix of $s_k$. This is
 * equivalent to the length of the longest suffix link from the terminal state of $s_k$.
 * All calculations are performed modulo $10^9+7$.
 * # Input
 * - The first line contains a single integer $n$ ($2 \le n \le 2 \times 10^5$), the number of strings.
 * - The next $n$ lines each contain a single string $s_i$ ($1 \le |s_i| \le 10^6$).
 * - The sum of all string lengths $\sum|s_i|$ does not exceed $10^6$.
 * # Output
 * - A single integer representing the expected cost modulo $10^9+7$.
 */

const int MOD = 1e9 + 7;
const int MAX_LEN = 2e6 + 5; // Sum of lengths + N separators
const int MAX_STATES = 2 * MAX_LEN;

struct Node {
    int len, link;
    std::map<char, int> next;
};

Node state[MAX_STATES];
int sz, last;

void gsa_init() {
    state[0].len = 0;
    state[0].link = -1;
    sz = 1;
    last = 0;
}

void gsa_extend(char c) {
    int cur = sz++;
    state[cur].len = state[last].len + 1;
    int p = last;
    while (p != -1 && state[p].next.find(c) == state[p].next.end()) {
        state[p].next[c] = cur;
        p = state[p].link;
    }
    if (p == -1) {
        state[cur].link = 0;
    } else {
        int q = state[p].next[c];
        if (state[q].len == state[p].len + 1) {
            state[cur].link = q;
        } else {
            int clone = sz++;
            state[clone].len = state[p].len + 1;
            state[clone].next = state[q].next;
            state[clone].link = state[q].link;
            while (p != -1 && state[p].next[c] == q) {
                state[p].next[c] = clone;
                p = state[p].link;
            }
            state[q].link = clone;
            state[cur].link = clone;
        }
    }
    last = cur;
}

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;
    std::vector<std::string> strings(n);
    long long sum_lengths = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> strings[i];
        sum_lengths += strings[i].length();
    }

    gsa_init();
    std::vector<int> end_states(n);
    std::vector<int> cnt_pref(MAX_STATES, 0);

    for (int i = 0; i < n; ++i) {
        last = 0;
        for (char c : strings[i]) {
            gsa_extend(c);
        }
        end_states[i] = last;
        // Use a separator to make sure strings don't form a continuous chain
        // in the automaton's forward path, for correct suffix counting.
        if (i < n - 1) {
             gsa_extend('Z' + 1 + i);
        }
    }
    
    // Count prefix occurrences
    for (int i = 0; i < n; ++i) {
        int curr = 0;
        for (char c : strings[i]) {
            curr = state[curr].next[c];
            cnt_pref[curr]++;
        }
    }
    
    // Count suffix occurrences by propagating up suffix links
    std::vector<int> cnt_suf(sz, 0);
    for (int i = 0; i < n; ++i) {
        cnt_suf[end_states[i]]++;
    }
    
    std::vector<std::pair<int, int>> sorted_states(sz);
    for (int i = 0; i < sz; ++i) {
        sorted_states[i] = {state[i].len, i};
    }
    std::sort(sorted_states.rbegin(), sorted_states.rend());

    for (const auto& p : sorted_states) {
        int u = p.second;
        if (state[u].link != -1) {
            cnt_suf[state[u].link] += cnt_suf[u];
        }
    }

    long long total_sum = 0;
    for (int u = 1; u < sz; ++u) {
        long long len_diff = state[u].len - state[state[u].link].len;
        long long pref_count = cnt_pref[u];
        long long suf_count = cnt_suf[u];
        long long term = (len_diff * pref_count) % MOD;
        term = (term * suf_count) % MOD;
        total_sum = (total_sum + term) % MOD;
    }
    
    // Subtract the F(s_k, s_k) part for distinct strings
    long long diag_sum = 0;
    for (int i = 0; i < n; ++i) {
        int end_state_idx = end_states[i];
        if (state[end_state_idx].link != -1) {
            diag_sum = (diag_sum + state[state[end_state_idx].link].len) % MOD;
        }
    }
    
    long long final_sum = (total_sum - diag_sum + MOD) % MOD;
    long long expected_cost = (final_sum * modInverse(n)) % MOD;

    std::cout << expected_cost << std::endl;

    return 0;
}