#include <iostream>
#include <fstream>

using namespace std;

void solve(long long N) {
    int ans = 0;
    for (int i = 0; 50 * i <= N; ++i)  {
        for (int j = 0; 100 * j + 50 * i <= N; ++j) {
            long long remaining_money = N - 100 * j - 50 * i;
            if (remaining_money % 200 == 0)  {
                ++ans;
            }
        }
    }
    long long pre_n = N / 100;
    long long f = pre_n / 2;
    long long s = pre_n - f;

    cout << "N/50 = " << N / 50 << ": formula = " << (f + 1) * (s + 1) << " ans = " << ans << endl;
} 

int main() {
    // optimal n^2
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    freopen("faster_solve_research/answers.txt", "w", stdout);

    for (long long N = 0; N < (long long)100 * 50; N += 50) {
        solve(N);
    }


    return 0;
}
