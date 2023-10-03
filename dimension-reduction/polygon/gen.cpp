#include "testlib.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>

using namespace std;

int round_(long double x) {
  int y = round(x);
  if (y == -0) {
    return 0;
  } else {
    return y;
  }
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int n = atoi(argv[1]);
  if (n == 0) {
    cout << 3 << endl;
    std::mt19937 gen{10};
    normal_distribution<> d0{0, 1};

    int n = 20, m = 20, k = 10;
    cout << n << " " << m << " " << k << endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (j <= 1) {
          cout << round_(d0(gen)) << " ";
        } else {
          cout << j;
          if (j + 1 < m) {
            cout << " ";
          }
        }
      }
      cout << endl;
    }

    normal_distribution<> d1{-25, 10};
    n = 100;
    m = 1000;
    k = 100;
    cout << n << " " << m << " " << k << endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (j <= 1) {
          cout << round_(d1(gen)) << " ";
        } else {
          cout << j;
          if (j + 1 < m) {
            cout << " ";
          }
        }
      }
      cout << endl;
    }

    normal_distribution<> d2{0, 1};
    n = 100;
    m = 1000;
    k = 100;
    cout << n << " " << m << " " << k << endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (j <= 1) {
          cout << round_(d2(gen)) << " ";
        } else {
          cout << j;
          if (j + 1 < m) {
            cout << " ";
          }
        }
      }
      cout << endl;
    }

  } else if (n == 1) {
    cout << 7 << endl;

    std::mt19937 gen{10};
    normal_distribution<> d0{0, 1};

    int n = 20, m = 20, k = 10;
    cout << n << " " << m << " " << k << endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << round_(d0(gen));
        if (j + 1 < m) {
          cout << " ";
        }
      }
      cout << endl;
    }

    normal_distribution<> d1{25, 10};
    n = 20;
    m = 20;
    k = 10;
    cout << n << " " << m << " " << k << endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << round_(d1(gen));
        if (j + 1 < m) {
          cout << " ";
        }
      }
      cout << endl;
    }

    normal_distribution<> d2{-25, 10};
    n = 100;
    m = 1000;
    k = 100;
    cout << n << " " << m << " " << k << endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << round_(d2(gen));
        if (j + 1 < m) {
          cout << " ";
        }
      }
      cout << endl;
    }
    normal_distribution<> d3{0, 1};

    n = 100;
    m = 1000;
    k = 100;
    cout << n << " " << m << " " << k << endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << round_(d3(gen));
        if (j + 1 < m) {
          cout << " ";
        }
      }
      cout << endl;
    }

    n = 100;
    m = 1000;
    k = 100;
    cout << n << " " << m << " " << k << endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << (abs((int)gen()) % 2000) - 1000;
        if (j + 1 < m) {
          cout << " ";
        }
      }
      cout << endl;
    }

    n = 100;
    m = 1000;
    k = 100;
    cout << n << " " << m << " " << k << endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if ((int)gen() % 2 == 0) {
          cout << abs((int)gen()) % 25 - 50;
        } else {
          cout << abs((int)gen()) % 25 + 25;
        }
        if (j + 1 < m) {
          cout << " ";
        }
      }
      cout << endl;
    }

    normal_distribution<> d4{25, 10};

    n = 100;
    m = 1000;
    k = 100;
    cout << n << " " << m << " " << k << endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << round_(d4(gen));
        if (j + 1 < m) {
          cout << " ";
        }
      }
      cout << endl;
    }
  }
}