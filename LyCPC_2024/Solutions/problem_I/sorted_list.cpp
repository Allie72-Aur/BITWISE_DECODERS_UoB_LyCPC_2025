#include <iostream>
#include <vector>
#include <algorithm> // Required for std::upper_bound
#include <iterator>  // Required for std::distance

// Function to add an item to a sorted vector, maintaining the sorted order.
void addItemSorted(std::vector<int>& list, int newItem) {
    // std::upper_bound finds the position where the new item should be inserted
    // to maintain the sorted order. It returns an iterator to the first element
    // that is greater than newItem.
    auto it = std::upper_bound(list.begin(), list.end(), newItem);

    // list.insert() inserts the newItem at the position found by the iterator.
    list.insert(it, newItem);
}

// Function to print the contents of the vector.
void printList(const std::vector<int>& list) {
    std::cout << "Current List: ";
    for (int item : list) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> sortedList;

    // Add some numbers to the list.
    // Notice they are not added in sorted order, but the list will remain sorted.
    std::cout << "Adding numbers to the list..." << std::endl;

    addItemSorted(sortedList, 50);
    printList(sortedList); // List: 50

    addItemSorted(sortedList, 10);
    printList(sortedList); // List: 10 50

    addItemSorted(sortedList, 70);
    printList(sortedList); // List: 10 50 70

    addItemSorted(sortedList, 30);
    printList(sortedList); // List: 10 30 50 70

    addItemSorted(sortedList, 10);
    printList(sortedList); // List: 10 10 30 50 70

    addItemSorted(sortedList, 90);
    printList(sortedList); // List: 10 10 30 50 70 90

    return 0;
}