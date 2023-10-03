#include <iostream>

using namespace std;

int main() {
    // optimal n^2
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    int ans = 0;
    for (int i = 0; 50 * i <= N; ++i)  {
        for (int j = 0; 100 * j + 50 * i <= N; ++j) {
            int remaining_money = N - 100 * j - 50 * i;
            if (remaining_money % 200 == 0)  {
                ++ans;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
