#include <iostream>

using namespace std;

void solve()
{
    string input;    
    cin >> input;
    
    long long output;
    int index;
    output = index = 0;

    for (auto c : input)
    {
        if (c == '1')
            output += ++index;
        else
            index = 0;
    }

    cout << output;
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