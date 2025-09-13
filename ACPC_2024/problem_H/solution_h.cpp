#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <map>

/**
 * @file solution_h.cpp
 * @date 2025-09-13
 * @author Allie Phenish (alliephenish@gmail.com)
 * @brief Solution to Problem H "Nile's Flowing Currents" of the ACPC 2024
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

/**
 * @brief Suffix Automaton Node Structure
 * 
 * The Node struct represents a single state in the Generalized Suffix Automaton (GSA).
 * Each state encodes information about a set of substrings that appear in the input strings.
 * 
 * - `len`: The length of the longest substring represented by this state.
 * - `link`: The suffix link, pointing to the state representing the largest proper suffix of the current substring.
 * - `next`: A map from characters to the next state, representing transitions for each possible character.
 * 
 * The automaton is built incrementally as we process each character of the input strings.
 * The Node struct is essential for efficiently storing and traversing the automaton, allowing us to
 * quickly answer substring queries and compute overlap lengths between strings.
 */
struct Node {
    int len, link;
    std::map<char, int> next;
};

Node state[MAX_STATES];
int sz, last;

/**
 * @brief Initializes the Generalized Suffix Automaton.
 * * Sets up the initial state of the automaton with a single root state
 * representing an empty string. All other states are effectively uninitialized.
 */
void gsa_init() {
    state[0].len = 0;
    state[0].link = -1;
    sz = 1;
    last = 0;
}

/**
 * @brief Extends the GSA with a new character.
 * * This function adds a new character `c` to the automaton, effectively appending it
 * to the string currently represented by the `last` state. It handles the creation
 * of new states and the update of suffix links, including the "cloning" process
 * to maintain the automaton's properties.
 * * @param c The character to be added to the automaton.
 */
void gsa_extend(char c) {
    int cur = sz++;
    state[cur].len = state[last].len + 1;
    int p = last;
    // Traverse suffix links from the last state to find a path for 'c'
    while (p != -1 && state[p].next.find(c) == state[p].next.end()) {
        state[p].next[c] = cur;
        p = state[p].link;
    }
    if (p == -1) {
        // No path for 'c' found, link to root
        state[cur].link = 0;
    } else {
        int q = state[p].next[c];
        if (state[q].len == state[p].len + 1) {
            // Path found and is of the correct length, simple link
            state[cur].link = q;
        } else {
            // Path found but needs a "cloned" state to maintain properties
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

/**
 * @brief Calculates modular exponentiation.
 * * Computes `(base^exp) % MOD` efficiently using binary exponentiation.
 * * @param base The base number.
 * @param exp The exponent.
 * @return The result of the modular exponentiation.
 */
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

/**
 * @brief Calculates the modular multiplicative inverse.
 * * Computes the modular inverse of `n` modulo `MOD` using Fermat's Little Theorem.
 * This is used for modular division.
 * * @param n The number to find the inverse of.
 * @return The modular multiplicative inverse of `n`.
 */
long long modInverse(long long n) {
    return power(n, MOD - 2);
}

int main() {
    // Set up fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;
    std::vector<std::string> strings(n);
    long long sum_lengths = 0;
    // Read all strings and calculate their total length
    for (int i = 0; i < n; ++i) {
        std::cin >> strings[i];
        sum_lengths += strings[i].length();
    }

    gsa_init();
    std::vector<int> end_states(n);
    std::vector<int> cnt_pref(MAX_STATES, 0);

    // Build the GSA for all strings.
    // We add a unique separator between each string to ensure suffixes do not
    // cross string boundaries in the automaton's structure.
    for (int i = 0; i < n; ++i) {
        last = 0;
        for (char c : strings[i]) {
            gsa_extend(c);
        }
        end_states[i] = last;
        if (i < n - 1) {
             gsa_extend('Z' + 1 + i);
        }
    }
    
    // Count prefix occurrences for each state. A state is a prefix of a string
    // if that string's path from the root goes through the state. We can count
    // this by simply traversing each string on the automaton and incrementing a counter.
    for (int i = 0; i < n; ++i) {
        int curr = 0;
        for (char c : strings[i]) {
            curr = state[curr].next.at(c);
            cnt_pref[curr]++;
        }
    }
    
    // Count suffix occurrences for each state. A state represents a suffix of a string
    // if the string ends at a state which has a suffix link path to the current state.
    // We initialize counts for end-of-string states and propagate them up the suffix links.
    std::vector<int> cnt_suf(sz, 0);
    for (int i = 0; i < n; ++i) {
        cnt_suf[end_states[i]]++;
    }
    
    // Sort states by length in descending order to correctly propagate counts
    // up the suffix link tree.
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

    // Calculate the total sum of overlap lengths for all ordered pairs (including k=l).
    // The total sum is the sum of contributions from each state in the GSA.
    // The number of substrings represented by state 'u' is len(u) - len(link(u)).
    // Each of these substrings appears as a prefix `cnt_pref[u]` times and as a suffix
    // `cnt_suf[u]` times.
    long long total_sum = 0;
    for (int u = 1; u < sz; ++u) {
        long long len_diff = state[u].len - state[state[u].link].len;
        long long pref_count = cnt_pref[u];
        long long suf_count = cnt_suf[u];
        long long term = (len_diff * pref_count) % MOD;
        term = (term * suf_count) % MOD;
        total_sum = (total_sum + term) % MOD;
    }
    
    // Subtract the F(s_k, s_k) part to get the sum for distinct pairs.
    // F(s_k, s_k) is the length of the longest proper suffix of s_k that is also a prefix.
    // This length is given by the length of the longest suffix link from s_k's end state.
    long long diag_sum = 0;
    for (int i = 0; i < n; ++i) {
        int end_state_idx = end_states[i];
        if (state[end_state_idx].link != -1) {
            diag_sum = (diag_sum + state[state[end_state_idx].link].len) % MOD;
        }
    }
    
    // Compute the final sum for distinct pairs
    long long final_sum = (total_sum - diag_sum + MOD) % MOD;
    
    // Calculate the expected cost by dividing the final sum by n
    long long expected_cost = (final_sum * modInverse(n)) % MOD;

    std::cout << expected_cost << std::endl;

    return 0;
}