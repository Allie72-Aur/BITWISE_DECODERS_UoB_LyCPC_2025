#include <iostream>

using namespace std;

void solve()
{
    int p1, p2;
    cin >> p1;
    cin >> p2;

    if (p1 > p2)
        cout << "p2";
    else if (p2 > p1)
        cout << "p1";
    else
        cout << "d";
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int times = 1;


    while  (times--)
    {
        solve();
        cout << '\n';
    }
}