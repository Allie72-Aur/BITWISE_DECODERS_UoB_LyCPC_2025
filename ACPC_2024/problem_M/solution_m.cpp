#include <iostream>

/**
 * @file solution_m.cpp
 * @date 2025-09-16
 * @author Allie Phenish (alliephenish@gmail.com)
 * @brief Solution to Problem M "Festival of Opet Logistics" of the ACPC 2024
 * @details
 * # Problem Description
 * The problem asks whether a group of M teams can be perfectly arranged on a contest floor 
 * with N tables. A "perfect fit" means no tables are empty and every team has a place. The 
 * verbose story about the Festival of Opet is a distraction. The core of the problem lies in 
 * the perfect distribution of teams among tables.
 * * # Input
 * The input consists of two integers:
 * - **N** (1 <= N <= 1000): The number of tables.
 * - **M** (1 <= M <= 10000): The number of teams.
 * * # Output
 * The output is a single string, either "Yes" or "No".
 * - "Yes" if the teams can be perfectly fit.
 * - "No" otherwise.
 * * # Solution
 * A perfect fit is achieved only when the total number of teams can be divided evenly among 
 * the tables. This implies that each table will have the same number of teams, with no teams 
 * left over. This condition can be checked using the modulo operator. If the number of teams 
 * (M) is perfectly divisible by the number of tables (N), then M % N will equal 0.
 * * The solution is as follows:
 * 1. Read the number of tables (N) and the number of teams (M) from standard input.
 * 2. Check if M is perfectly divisible by N using the modulo operator: `M % N == 0`.
 * 3. If the condition is true, print "Yes".
 * 4. If the condition is false, print "No".
 */

int main()
{
    // Fast I/O for competitive programming
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Get number of tables and teams for stdin
    int num_tables, num_teams;
    std::cin >> num_tables >> num_teams;

    // Check if the number of teams is perfectly divisible by the number of tables.
    // Use a ternary operator for a concise one-line check.
    std::cout << ((num_teams % num_tables == 0) ? "Yes\n" : "No\n");

    return 0;
}