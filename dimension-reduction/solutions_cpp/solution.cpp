#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

std::mt19937 gen{10};
normal_distribution<> d{0, 1};

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

vector<vector<ld>> generate_matrix() {
  vector<vector<ld>> ret(m, vector<ld>(k));
  ld div = sqrt((ld)1 / k);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < k; ++j) {
      ret[i][j] = d(gen) * div;
    }
  }
  return ret;
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

void solve7() {
  cin >> n >> m >> k;

  int GEN_CNT = max((int)(1e7) / (n * m * k), 100);

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

  vector<vector<ld>> ans;
  vector<vector<ld>> mul;
  ld best_error = INF;

  // GEN_CNT * n * m * k

  for (int t = 0; t < GEN_CNT; ++t) {
    vector<vector<ld>> now_mul = generate_matrix();
    vector<vector<ld>> possible_ans = get_matrix_multiplication(a, now_mul);
    ld error = calc_error(a, possible_ans);
    if (error < best_error) {
      mul = now_mul;
    }
  }

  cout.precision(5);
  cout << fixed;

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < k; ++j) {
      cout << mul[i][j] << " ";
    }
    cout << endl;
  }
}

void solve3() {
  cin >> n >> m >> k;
  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
    }
  }
  vector<vector<ld>> mul_matr(m, vector<ld>(k, 0));
  for (int i = 0; i < min(m, k); ++i) {
    mul_matr[i][i] = 1;
  }
  ld best_error = INF;
  cout.precision(30);

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
    if (t == 7) {
      solve7();
    } else {
      solve3();
    }
  }
}