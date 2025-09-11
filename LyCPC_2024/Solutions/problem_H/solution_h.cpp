/**
 * @file solution_h.cpp
 * @date 2025-9-11
 * @author Allie Phenish (alliephenish@gmail.com)
 * @brief Solution to Problem H
 * @details
 *  Given an integer P, which is defined by the formula P = S_n - r, where S_n is the sum of
 *  the first n natural numbers and n and r are random integer, r in the range [1, n], n and r
 *  are random and we don't have knowledge of thier values, find the value of r.
 */

#include <iostream>
#include <cmath>
using namespace std;

/**
 * @param P The given integer defined by the formula P = S_n - r, can have a value upto 10^9
 * @return The value of r in the range [1, n]
 * @details
 *  We know that S_n = n(n + 1)/2, so we can rewrite the equation as P = n(n + 1)/2 - r.
 *  Rearranging gives us r = n(n + 1)/2 - P.
 *  To find n, we can use the quadratic formula to solve for n in the equation n^2 + n - 2(P + r) = 0.
 *  The quadratic formula gives us n = (-b ± √(b² - 4ac)) / 2a, where a = 1, b = 1, and c = -2(P + r)
 *  We substitute these values into the formula to get n = (-1 ± √(1 + 8(P + r))) / 2.
 *  We take r as 1, justification being that it will give us the maximum possible n for a given P.
 *  This simplifies to n = (-1 + √(1 + 8(P + 1))) / 2.
 *  We take the positive root since n must be a positive integer.
 *  Once we have n, we can easily calculate r using the rearranged equation.
 *  The time complexity of this approach is O(1) since it involves a constant number of arithmetic
 *  operations and a square root calculation.
 */
int find_r(int P)
{
    // Using the quadratic formula to solve for n in the equation n^2 + n - 2(P + r) = 0
    int n = (sqrt(1 + 8 * (P + 1)) - 1) / 2; // Start with r = 1 to find the maximum possible n
    int S_n = n * (n + 1) / 2;               // Sum of first n natural numbers
    int r = S_n - P;                         // Calculate r
    return r;
}

/**
 * @details P The given integer defined by the formula P = S_n - r
 *  can have a value upto 10^9
 */
void solve_one_case()
{
    int P;
    cin >> P;
    int r = find_r(P);
    cout << r << endl;
}

int main()
{
    int num_test_cases = 0;
    cin >> num_test_cases;
    for (int i = 0; i < num_test_cases; ++i)
    {
        solve_one_case();
    }

    return 0;
}