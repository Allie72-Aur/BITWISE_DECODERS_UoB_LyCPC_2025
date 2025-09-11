/**
 * @file solution_I.cpp
 * @date 2025-09-11
 * @author Allie Phenish (alliephenish@gmail.com)
 * @brief Solution to problem I: "Neutralizer" from the 2024 LyCPC.
 * @details The gest of the problem is to keep a list ordered and iterate
 * through it summing its element up to an index i.
 */

#include <iostream>
#include <vector>
#include <algorithm> // Required for std::upper_bound
#include <iterator>  // Required for std::distance

/**
 * @brief Function to add an item to a sorted vector, maintaining the sorted order.
 * @details The elements in the vector are sorted in non-increasing order.
*/
void addItemSorted(std::vector<int>& list, int newItem) {
    // std::upper_bound finds the position where the new item should be inserted
    // to maintain the sorted order. It returns an iterator to the first element
    // that is greater than newItem.
    auto it = std::lower_bound(list.begin(), list.end(), newItem);

    // list.insert() inserts the newItem at the position found by the iterator.
    list.insert(it, newItem);
}

int main() {
    int num_queries;
    std::cin >> num_queries;
    std::vector<int> sortedListOfTargets;
    int i = 0; // Index up to which we sum the elements
    for (int q = 0; q < num_queries; ++q) {
        char query_type;
        std::cin >> query_type;
        if (query_type == '1') {
            int new_target;
            std::cin >> new_target;
            addItemSorted(sortedListOfTargets, new_target);
        } else if (query_type == '2') {
            i++;
            long long sum = 0;
            for (int j = 0; j < i && j < static_cast<int>(sortedListOfTargets.size()); ++j) {
                sum += sortedListOfTargets[j];
            }
            std::cout << sum << std::endl;
        }
}