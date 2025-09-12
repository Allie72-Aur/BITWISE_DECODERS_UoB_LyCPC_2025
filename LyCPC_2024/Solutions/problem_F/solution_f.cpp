#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

/**
 * @file solution_f.cpp
 * @date 2025-09-12
 * @authors Emad S. Alshkre (polyex9@gmail.com)
 *      and Allie Phenish (alliephenish@gmail.com)
 * @brief Solution to Problem F "Triple Riot" of LyCPC 2024 contest.
 * @details 
 * # Problem Description
 * We are given an array of $n$ numbers and are required to find all their common divisors. The output
 * should be the count of these divisors, followed by the divisors themselves, sorted in increasing order.
 * # Input
 * - The first line contains an integer $T$ ($1 \le T \le 7$), the number of test cases.
 * - For each test case:
 * - The first line contains an integer $n$ ($1 \le n \le 10^5$).
 * - The second line contains $n$ space-separated integers $a_1, a_2, ..., a_n$ ($0 \le a_i \le 10^{12}$).
 * - It is guaranteed that at least one number in the array is non-zero.
 * # Output
 * - The first line of output for each test case is a single integer $m$, the number of common divisors.
 * - The second line contains $m$ space-separated integers, the common divisors in increasing order.
 * # Constraints & Algorithm
 * The most efficient way to find the common divisors of a set of numbers is to first calculate
 * their greatest common divisor (GCD). The common divisors of the set are then simply the
 * divisors of this GCD.
 * We calculate the GCD iteratively using std::gcd. Since the numbers can be up to $10^{12}$,
 * we use `long long`. The GCD calculation is efficient.
 * After finding the GCD, we find its divisors by iterating up to its square root, which is
 * significantly faster than iterating up to the GCD itself. This allows us to handle
 * large numbers within the time limit.
 */

// Function to find all divisors of a number
std::vector<long long> get_divisors(long long num) {
    std::vector<long long> divisors;
    // Iterate from 1 up to the square root of num
    for (long long i = 1; i * i <= num; ++i) {
        if (num % i == 0) {
            divisors.push_back(i);
            // If i is not the square root of num, then num/i is also a divisor
            if (i * i != num) {
                divisors.push_back(num / i);
            }
        }
    }
    // Sort the divisors in increasing order
    std::sort(divisors.begin(), divisors.end());
    return divisors;
}

// Function to solve a single test case
void solve() {
    int n;
    std::cin >> n;

    std::vector<long long> a(n);
    long long final_gcd = 0;
    bool first_non_zero_found = false;

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        if (a[i] != 0) {
            if (!first_non_zero_found) {
                final_gcd = a[i];
                first_non_zero_found = true;
            } else {
                final_gcd = std::gcd(final_gcd, a[i]);
            }
        }
    }

    std::vector<long long> divisors = get_divisors(final_gcd);

    std::cout << divisors.size() << '\n';

    for (size_t i = 0; i < divisors.size(); ++i) {
        std::cout << divisors[i] << (i == divisors.size() - 1 ? "" : " ");
    }
}

int main(void) {
    // Fast I/O for competitive programming
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int times = 1;
    std::cin >> times;

    while (times--) {
        solve();
        std::cout << '\n';
    }
    
    return 0;
}
