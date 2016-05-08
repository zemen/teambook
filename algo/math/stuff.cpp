#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int M = 1e6;

int phi[M];

void calcPhi() {
  for (int i = 1; i < M; ++i)
    phi[i] = i;
  for (int j = 1; j < M; ++j)
    for (int i = 2 * j; i < M; i += j)
      phi[i] -= phi[j];
}

const int mod = 1e9 + 7;

int add(int x, int y) { x += y; if (x >= mod) x -= mod; return x; }
int sub(int x, int y) { x -= y; if (x < 0) x += mod; return x; }
int mul(ll x, ll y) { return x * y % mod; }

int inv[M];

void calcInv() {
  inv[1] = 1;
  for (int i = 2; i < M; ++i) {
    inv[i] = mul(sub(0, mod / i), inv[mod % i]); 
    assert(mul(i, inv[i]) == 1);
  }
}

int main() {
  calcPhi();
  assert(phi[30] == 1 * 2 * 4);
  calcInv();
  return 0;
}
