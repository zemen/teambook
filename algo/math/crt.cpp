#include <bits/stdc++.h>

using namespace std;

#define y1 hui

int gcd(int a, int b, int &x, int &y) {
  if (a == 0) {
    x = 0, y = 1;
    return b;
  }
  int x1, y1;
  int g = gcd(b % a, a, x1, y1);
  x = y1 - x1 * (b / a);
  y = x1;
  assert(a * x + b * y == g);
  return g;
}

int crt(int mod1, int mod2, int rem1, int rem2) {
  int r = (rem2 - (rem1 % mod2) + mod2) % mod2;
  int x, y;
  int g = gcd(mod1, mod2, x, y);
  assert(r % g == 0);

  x %= mod2;
  if (x < 0)
    x += mod2;

  int ans = (x * (r / g)) % mod2;
  ans = ans * mod1 + rem1;

  assert(ans % mod1 == rem1);
  assert(ans % mod2 == rem2);
  return ans;
}

int main() {
  int x, y;
  gcd(3, 5, x, y);
  gcd(15, 10, x, y);
  crt(15, 13, 2, 5);
  crt(17, 3, 15, 2);
  return 0;
}
