/**
 * @file solution_j.cpp
 * @date 2025-09-11
 * @author Allie Phenish (alliephenish@gmail.com)
 * @brief Solution to Problem J "Problem Setters" of LyCPC 2024
 * @details 
 * # Problem Description
 *   We need to perform a logical AND operation on n arrays of boolean values.
 *   Each array has a length of m. The result should be an array of length m 
 *   where each element is the result of the AND operation on the corresponding
 *   elements of the input arrays.
 * # Input
 *   - The first line contains two integers n and m (1 ≤ n, m ≤ 1000), the number of arrays
 *     and the length of each array.
 *   - The next n lines each contain m integers (0 or 1), representing the boolean values
 *     in each array.
 * # Output
 *  - A single line containing the number of 1s in the resulting array after performing
 *    the AND operation.
 */
#include <iostream>
#include <vector>
#include <string>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<bool> result_array(m, true); // Initialize all to true
    int one_count = 0;

    for (int i = 0; i < n; ++i) {
        std::string line;
        std::cin >> line;
        for (int j = 0; j < m; ++j) {
            char c = line[j];
            if (c == '0') {
                result_array[j] = false;
            }
        }
    }

    for (int j = 0; j < m; ++j) {
        if (result_array[j]) {
            one_count++;
        }
    }

    std::cout << one_count << std::endl;

    return 0;
}