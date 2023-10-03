#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

typedef long long ll;
typedef long double ld;

const ll INF = 1e18;
ld dp[1000][1000];

int n, m, k;

template <typename T> ld calc_norm(vector<T> &a, vector<T> &b) {
  ld norm = 0;
  for (int i = 0; i < a.size(); ++i) {
    norm += (a[i] - b[i]) * (a[i] - b[i]);
  }
  return sqrt(norm);
}

ld calc_error(vector<vector<int>> &a, vector<vector<ld>> &b) {
  ld error = 0;
  for (int i = 0; i < a.size(); ++i) {
    for (int j = i + 1; j < a.size(); ++j) {
      ld norm1 = dp[i][j];
      ld norm2 = calc_norm(b[i], b[j]);
      error += abs(norm1 - norm2);
    }
  }
  return error;
}

vector<vector<ld>> get_matrix_multiplication(const vector<vector<int>> &a,
                                             const vector<vector<ld>> &b) {
  vector<vector<ld>> ret(a.size(), vector<ld>(b[0].size(), 0));
  for (int i = 0; i < a.size(); ++i) {
    for (int k = 0; k < b[0].size(); ++k) {
      for (int j = 0; j < b.size(); ++j) {
        ret[i][k] += a[i][j] * b[j][k];
      }
    }
  }
  return ret;
}

void solve() {
  cin >> n >> m >> k;

  int GEN_CNT = max((int)(1e8) / (n * m * k), 100);
  GEN_CNT = 5;

  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      dp[i][j] = calc_norm(a[i], a[j]);
    }
  }

  vector<vector<ld>> mul_matr(m, vector<ld>(k, 0));
  for (int i = 0; i < min(m, k); ++i) {
    mul_matr[i][i] = 1;
  }
  //   vector<vector<ld>> ans = get_matrix_multiplication(a, mul_matr);
  ld best_error = INF;

  cout.precision(5);
  cout << fixed;

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < k; ++j) {
      if (mul_matr[i][j] == -0) {
        cout << "0 ";
      } else {
        cout << mul_matr[i][j] << " ";
      }
    }
    cout << endl;
  }
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}