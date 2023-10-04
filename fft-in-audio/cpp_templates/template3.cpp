#include <cassert>
#include <cmath>
#include <set>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

constexpr int N = 57600;
constexpr int m = 4000;
constexpr int b = 1000;
const double pi = atan2(0, -1);

double x(int i, int j) {
    assert(0 <= i && i < N);
    assert(1 <= j && j <= 2 * m);
    if (j <= m) {
        return cos(2 * pi * i * j / N);
    } else {
        j -= m;
        return -sin(2 * pi * i * j / N);
    }
}

int main() {
    cout << fixed << setprecision(6);

    // Input:
    freopen("train.csv", "r", stdin);
    vector<pair<int, double>> v(N / 4);
    for (int i = 0; i < N / 4; i++) {
        double t, y;
        scanf("%lf,%lf", &t, &y);
        v[i] = {int(t), y};
    }

    vector<double> w(2 * m);
    for (int it = 1; it <= 1; it++) {
        // Gradient descent iteration:
        cerr << "Iteration #" << it << '\r' << flush;

        // Calculating current y:
        vector<double> y(N / 4);
        for (int i = 0; i < N / 4; i++) {
            for (int j = 1; j <= 2 * m; j++) {
                y[i] += w[j - 1] * x(v[i].first, j);
            }
        }

        // Generate batch:
        set<int> batch;
        while (int(batch.size()) < b) {
            batch.insert(rand() % (N / 4) + 1);
        }

        // Find gradient:
        // TODO...

        // Change w:
        // TODO... (w -= ??? * gradient)
    }

    // Output:
    for (int i = 0; i < 2 * m; i++) {
        if (i) cout << ",";
        cout << w[i];
    }
    cout << '\n';
}
