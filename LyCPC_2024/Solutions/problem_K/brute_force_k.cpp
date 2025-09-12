#include <iostream>
#include <vector>
#include <algorithm>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    long long total_evaluation = 0;

    // Iterate through all possible subarrays with length > 1
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // Create the current subarray
            std::vector<int> sub;
            for (int k = i; k <= j; ++k) {
                sub.push_back(arr[k]);
            }

            // Sort the subarray
            std::sort(sub.begin(), sub.end());

            // Calculate the difficulty
            int difficulty = 0;
            for (size_t k = 0; k < sub.size() - 1; ++k) {
                if (sub[k+1] - sub[k] > 1) {
                    difficulty++;
                }
            }

            // Add to the total evaluation
            total_evaluation += difficulty;
        }
    }
    std::cout << total_evaluation << std::endl;
}

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}