/**
 * @file solution_g.cpp
 * @date 2025-09-12
 * @author Allie Phenish (alliephenish@gmail.com)
 * @brief Solution to Problem G "Deal With Meal" of LyCPC 2024 contest.
 * @details
 * # Problem Description
 * We need to find the K most affordable unique meals from a given set of N dishes and M sauces.
 * The cost of a meal is the sum of the cost of one dish and one sauce. The dish and sauce
 * costs are provided in sorted, non-decreasing order. The output should be the K meals
 * sorted by cost in ascending order. In case of a tie in cost, the meal with the smaller
 * dish index comes first. If there is still a tie, the meal with the smaller sauce index
 * should be prioritized.
 * # Input
 * - The first line contains an integer T (1 <= T <= 10), the number of test cases.
 * - For each test case:
 * - The first line contains three integers N, M, and K
 *      (1 <= N, M <= 10^5, 1 <= K <= min(N*M, 10^5)).
 * - The second line contains N non-decreasing integers, the costs of the dishes.
 * - The third line contains M non-decreasing integers, the costs of the sauces.
 * # Output
 * - For each test case, a single line containing the K most economical meals in the
 * format {(d1,s1),(d2,s2),...,(dk,sk)}, where di and si are the 0-based indices of
 * the dish and sauce, respectively.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>

// A struct to represent a meal with its cost and indices
struct Meal
{
    long long cost;
    int dish_idx;
    int sauce_idx;

    // Custom comparator for the priority queue.
    // By default, std::priority_queue is a max-heap. We want a min-heap,
    // so we overload the '>' operator. This allows us to use std::greater<Meal>
    // to create a min-heap. The tie-breaking rules are also implemented here:
    // 1. Ascending by cost
    // 2. Ascending by dish_idx
    // 3. Ascending by sauce_idx
    bool operator>(const Meal &other) const
    {
        if (cost != other.cost)
        {
            return cost > other.cost;
        }
        if (dish_idx != other.dish_idx)
        {
            return dish_idx > other.dish_idx;
        }
        return sauce_idx > other.sauce_idx;
    }
};

// Function to solve a single test case
void solve()
{
    int N, M, K;
    std::cin >> N >> M >> K;

    std::vector<long long> dishes(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> dishes[i];
    }

    std::vector<long long> sauces(M);
    for (int i = 0; i < M; ++i)
    {
        std::cin >> sauces[i];
    }

    // Min-priority queue to store the meals to be considered,
    // ordered by cost and then by indices for tie-breaking.
    std::priority_queue<Meal, std::vector<Meal>, std::greater<Meal>> pq;

    // A set to keep track of pairs (dish_idx, sauce_idx) that have already been
    // processed or are in the priority queue to prevent duplicates.
    std::set<std::pair<int, int>> visited;

    // The most affordable meal is always the first dish and first sauce.
    if (N > 0 && M > 0)
    {
        pq.push({dishes[0] + sauces[0], 0, 0});
        visited.insert({0, 0});
    }

    std::vector<std::pair<int, int>> result_meals;

    // Extract the K cheapest meals from the priority queue
    while (!pq.empty() && result_meals.size() < K)
    {
        Meal current_meal = pq.top();
        pq.pop();

        result_meals.push_back({current_meal.dish_idx, current_meal.sauce_idx});

        // The next cheapest meals can be found by either incrementing the dish index
        // or the sauce index of the current meal.

        // Candidate 1: The same dish with the next sauce
        int next_dish_idx_1 = current_meal.dish_idx;
        int next_sauce_idx_1 = current_meal.sauce_idx + 1;
        if (next_sauce_idx_1 < M && visited.find({next_dish_idx_1, next_sauce_idx_1}) == visited.end())
        {
            pq.push({dishes[next_dish_idx_1] + sauces[next_sauce_idx_1], next_dish_idx_1, next_sauce_idx_1});
            visited.insert({next_dish_idx_1, next_sauce_idx_1});
        }

        // Candidate 2: The next dish with the same sauce
        int next_dish_idx_2 = current_meal.dish_idx + 1;
        int next_sauce_idx_2 = current_meal.sauce_idx;
        if (next_dish_idx_2 < N && visited.find({next_dish_idx_2, next_sauce_idx_2}) == visited.end())
        {
            pq.push({dishes[next_dish_idx_2] + sauces[next_sauce_idx_2], next_dish_idx_2, next_sauce_idx_2});
            visited.insert({next_dish_idx_2, next_sauce_idx_2});
        }
    }

    // Output the result in the specified format
    for (size_t i = 0; i < result_meals.size(); ++i)
    {
        std::cout << result_meals[i].first + 1 << " " << result_meals[i].second + 1;
        std::cout << std::endl;
    }
}

int main()
{
    // Fast I/O for competitive programming
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T;
    while (T--)
    {
        solve();
    }

    return 0;
}