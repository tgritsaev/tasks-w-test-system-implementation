#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  int t = inf.readInt(1, 10, "t");
  inf.readEoln();
  for (int i = 0; i < t; ++i) {
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readSpace();
    int k = inf.readInt(1, 100, "k");
    inf.readEoln();

    for (int j = 0; j < n; ++j) {
      for (int p = 0; p < m; ++p) {
        inf.readInt(-1000, 1000, "k");
        if (p + 1 < m) {
          inf.readSpace();
        } else {
          inf.readEoln();
        }
      }
    }
  }
  inf.readEof();
}