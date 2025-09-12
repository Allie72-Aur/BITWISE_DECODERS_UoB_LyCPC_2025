/**
 * @file solution_m.cpp
 * @date 2025-09-12
 * @author Allie Phenish (alliephenish@gmail.com)
 * @brief Solution to Problem M "Coach Academy PST" of the LyCPC 2024 contest.
 * @details 
 * # Problem Description
 * We need to determine the most suitable training level for a student based on the
 * number of problems they have solved in a qualification contest. There are four
 * training levels, each with a minimum number of problems required for eligibility.
 * If the student does not meet even the minimum requirements, they are not qualified.
 * # Input
 * - The first line contains a single integer n (0 <= n <= 14), the number of problems
 *      the student has solved.
 * - The second line contains four distinct integers L1, L2, L3, L4 
 *      (0 <= L1 < L2 < L3 < L4 <= 14),
 *   the minimum number of problems required for each of the four levels.
 * # Output
 * - A single integer representing the most suitable level the student can join.
 * - If the student is not qualified for any level, output -1.
 */
#include <iostream>

int main() {
    // Use fast I/O to improve performance for competitive programming
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // n: number of problems solved
    int n;
    std::cin >> n;

    // l1, l2, l3, l4: minimum problems required for each of the four levels
    int l1, l2, l3, l4;
    std::cin >> l1 >> l2 >> l3 >> l4;

    // The problem states that L1 < L2 < L3 < L4.
    // To find the "most suitable" level, we should check from the highest level downwards.
    // The first level for which Student has solved enough problems is the most suitable.
    if (n >= l4) {
        // Student has solved enough problems for Level 4
        std::cout << 4 << std::endl;
    } else if (n >= l3) {
        // Student doesn't qualify for Level 4, but qualifies for Level 3
        std::cout << 3 << std::endl;
    } else if (n >= l2) {
        // Student doesn't qualify for Level 3, but qualifies for Level 2
        std::cout << 2 << std::endl;
    } else if (n >= l1) {
        // Student doesn't qualify for Level 2, but qualifies for Level 1
        std::cout << 1 << std::endl;
    } else {
        // Student does not meet the minimum requirements for any level
        std::cout << -1 << std::endl;
    }

    return 0;
}