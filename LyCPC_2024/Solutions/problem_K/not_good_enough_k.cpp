/** Time limit exceeded on test 8 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    long long total_evaluation = 0;

    for (int i = 0; i < n; ++i) {
        // Use a set to maintain the sorted unique elements of the current subarray
        std::set<int> subarray_set;

        for (int j = i; j < n; ++j) {
            subarray_set.insert(arr[j]);

            // Only consider subarrays of length > 1
            if (j - i + 1 > 1) {
                int difficulty = 0;
                auto it = subarray_set.begin();
                int prev_val = *it;
                it++;

                for (; it != subarray_set.end(); ++it) {
                    if (*it - prev_val > 1) {
                        difficulty++;
                    }
                    prev_val = *it;
                }
                total_evaluation += difficulty;
            }
        }
    }
    std::cout << total_evaluation << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}