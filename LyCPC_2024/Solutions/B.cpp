#include <iostream>

using namespace std;

void solve()
{
    int N, M, X1, X2;

    cin >> N >> M >> X1 >> X2;

    int unsave = 0;

    for (int i = N; i < M + 1; i++)
        if ((X1 % i) == 0 && (X2 % i) == 0)
            unsave++;

    cout << (M - N + 1) - unsave;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int times = 1;
    cin >> times;

    while  (times--)
    {
        solve();
        cout << '\n';
    }
}