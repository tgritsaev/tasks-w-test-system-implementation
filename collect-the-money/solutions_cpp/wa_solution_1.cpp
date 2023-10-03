#include <iostream>

using namespace std;

int main() {
    long long N;
    cin >> N;
    int ans = 0;
    long long pre_n = N / 100;
    long long f = pre_n / 2;
    long long s = pre_n - f;
    cout << (f + 1) * (s) << endl;
    return 0;
}
