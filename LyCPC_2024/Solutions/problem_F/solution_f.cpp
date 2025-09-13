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

/**
 * @brief Finds all divisors of a given number.
 * * This function efficiently computes all divisors of a `long long` number
 * by iterating only up to its square root.
 *
 * @param num The number to find divisors for.
 * @return A vector of `long long` integers containing all divisors, sorted in
 * increasing order.
 */
std::vector<long long> get_divisors(long long num)
{
    std::vector<long long> divisors;
    // Iterate from 1 up to the square root of num
    for (long long j = 1; j * j <= num; ++j)
    {
        if (num % j == 0)
        {
            // j is a divisor
            divisors.push_back(j);
            // If j is not the square root of num, then num/j is also a divisor
            if (j * j != num)
            {
                divisors.push_back(num / j);
            }
        }
    }
    // Sort the divisors in increasing order for the final output
    std::sort(divisors.begin(), divisors.end());
    return divisors;
}

/**
 * @brief Solves a single test case for the problem.
 * * This function handles the logical flow for one problem instance. It reads the
 * input array, calculates the greatest common divisor of all elements, finds
 * the divisors of the GCD, and prints the result.
 */
void solve()
{
    int n;
    std::cin >> n;

    // Use long long to handle large input numbers up to 10^12
    long long final_gcd = 0;
    bool first_non_zero_found = false;

    for (int j = 0; j < n; ++j)
    {
        long long current_val;
        std::cin >> current_val;

        // The GCD of a number with 0 is the number itself. We only need to
        // consider the non-zero numbers to find the GCD of the entire set.
        if (current_val != 0)
        {
            if (!first_non_zero_found)
            {
                // Initialize the GCD with the first non-zero number
                final_gcd = current_val;
                first_non_zero_found = true;
            }
            else
            {
                // Iteratively compute the GCD with subsequent non-zero numbers
                final_gcd = std::gcd(final_gcd, current_val);
            }
        }
    }

    // Get all divisors of the final GCD
    std::vector<long long> divisors = get_divisors(final_gcd);

    // Print the number of common divisors
    std::cout << divisors.size() << '\n';

    // Print the divisors separated by spaces
    for (size_t j = 0; j < divisors.size(); ++j)
    {
        std::cout << divisors[j] << (j == divisors.size() - 1 ? "" : " ");
    }
}

/**
 * @brief The main function and entry point of the program.
 *
 * This function sets up fast I/O, reads the number of test cases, and calls
 * the `solve()` function for each test case.
 */
int main(void)
{
    // Set up fast input/output
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int num_test_cases = 0;
    std::cin >> num_test_cases;

    while (num_test_cases--)
    {
        solve();
        std::cout << '\n';
    }

    return 0;
}