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