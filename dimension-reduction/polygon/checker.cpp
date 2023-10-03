#include "testlib.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

using namespace std;

typedef long double ld;

template <typename T> ld calc_norm(vector<T> &a, vector<T> &b) {
  ld norm = 0;
  for (size_t i = 0; i < a.size(); ++i) {
    norm += (a[i] - b[i]) * (a[i] - b[i]);
  }
  return sqrt(norm);
}

ld calc_error(vector<vector<int>> &a, vector<vector<ld>> &b) {
  ld error = 0;
  for (size_t i = 0; i < a.size(); ++i) {
    for (size_t j = i + 1; j < a.size(); ++j) {
      ld norm1 = calc_norm(a[i], a[j]);
      ld norm2 = calc_norm(b[i], b[j]);
      error += abs(norm1 - norm2);
    }
  }
  return error;
}

const int bound = 1000 * 1000;

vector<vector<ld>> readOuf(InStream &in, int m, int k) {
  vector<vector<ld>> ret(m, vector<ld>(k));
  for (size_t i = 0; i < m; ++i) {
    for (size_t j = 0; j < k; ++j) {
      ret[i][j] = in.readDouble(-bound, bound, "a");
    }
  }
  return ret;
}

vector<vector<ld>> get_matrix_multiplication(const vector<vector<int>> &a,
                                             const vector<vector<ld>> &b) {
  vector<vector<ld>> ret(a.size(), vector<ld>(b[0].size(), 0));
  for (size_t i = 0; i < a.size(); ++i) {
    for (size_t k = 0; k < b[0].size(); ++k) {
      for (size_t j = 0; j < b.size(); ++j) {
        ret[i][k] += a[i][j] * b[j][k];
      }
    }
  }
  return ret;
}

const ld mul = 2;
const ld eps = 0.001;

int main(int argc, char *argv[]) {
  vector<ld> down_bounds(10);
  down_bounds[0] = 0;
  down_bounds[1] = 0;
  down_bounds[2] = 0;
  down_bounds[3] = 199.628359130627004325297946252;
  down_bounds[4] = 1561.98209262665105101497431406;
  down_bounds[5] = 120290.050982402659741410388961;
  down_bounds[6] = 12760.0962484945616504106169486;
  down_bounds[7] = 0;
  down_bounds[8] = 0;
  down_bounds[9] = 133171.028020444858796622611408;
  vector<ld> up_bounds(10, 0);
  for (int i = 0; i < up_bounds.size(); ++i) {
    up_bounds[i] = mul * down_bounds[i] + 100;
  }

  registerTestlibCmd(argc, argv);

  size_t t = inf.readInt();
  if (t == 2) {
    for (int i = 0; i < t; ++i) {
      size_t n = inf.readInt();
      size_t m = inf.readInt();
      size_t k = inf.readInt();
      for (size_t j1 = 0; j1 < n * m; ++j1) {
        inf.readInt();
      }
      readOuf(ouf, m, k);
    }
    quitp(0, "ok");
  }
  int start;
  if (t == 3) {
    start = 0;
  } else {
    start = 3;
  }
  ld sum = 0;
  cout.precision(30);
  for (size_t i = start, j = 0; j < t; ++i, ++j) {
    size_t n = inf.readInt();
    size_t m = inf.readInt();
    size_t k = inf.readInt();
    vector<vector<int>> in(n, vector<int>(m));
    for (size_t j1 = 0; j1 < n; ++j1) {
      for (size_t j2 = 0; j2 < m; ++j2) {
        in[j1][j2] = inf.readInt();
      }
    }
    vector<vector<ld>> pa = readOuf(ouf, m, k);
    vector<vector<ld>> out = get_matrix_multiplication(in, pa);

    ld error = calc_error(in, out);
    ld grade;
    if (error + eps < down_bounds[i]) {
      cout << "j_error: " << down_bounds[i] << endl;
      cout << "p_error: " << error << endl;
      quitf(_fail, ":( participant has the better answer on test #%zu", i);
    } else if (error >= up_bounds[i]) {
      cout << error << " " << up_bounds[i] << endl;
      grade = 0;
    } else {
      grade = min(round(10 * (up_bounds[i] - error) /
                        (up_bounds[i] - down_bounds[i]) * 1000) /
                      1000,
                  (ld)10);
    }
    cout << "grade: " << grade << " error: " << error << endl;
    sum += grade;
  }
  quitp(sum, "ok");
}