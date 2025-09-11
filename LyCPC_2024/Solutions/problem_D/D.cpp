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

    for (int i = 0; i < n; i++)
        cin >> input[i];

    int output ,index;
    output = index = 0;

    int before = input[0];

    for (auto num : input)
    {
        if (num > before)
        {
            output += ++index;
        }
        else
        {
            index = 1;
            output += index;
        }

        before = num;
    }

    cout << output;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int times = 1;
    // cin >> times;

    while  (times--)
    {
        solve();
        cout << '\n';
    }
}