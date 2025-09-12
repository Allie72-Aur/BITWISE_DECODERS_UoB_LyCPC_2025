/**
 * @file less_efficient.cpp
 * @date 2025-09-12
 * @authors Emad S. Alshkre (polyex9@gmail.com)
 *      and Allie Phenish (alliephenish@gmail.com)
 * @brief Solution to Problem F "Triple Riot" of [Contest Name]
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
 */
#include <iostream>
#include <vector>

using namespace std;

void solve()
{
    int n;
    cin >> n;
    if (n < 1)
        return;

    vector<int> input(n);
    for (auto &x : input)
        cin >> x;

    vector<int> divisors;

    for (int i = 1; i <= input[n - 1]; i++)
    {
        bool flag = true;
        for (int j = 0; j < n; j++)
        {
            if (!(input[j] % i == 0))
                flag = false;
        }

        if (flag)
        {
            divisors.push_back(i);
        }
    }

    cout << divisors.size() << '\n';

    for (auto x : divisors)
        cout << x << " ";
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int times = 1;
    cin >> times;

    while  (times--)
    {
        solve();
        cout << '\n';
    }
}