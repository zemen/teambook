#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define y1 pizda

// BEGIN_CODE
const int M = 1e6;
int phi[M];
void calcPhi() {
    for (int i = 1; i < M; ++i)
        phi[i] = i;
    for (int j = 1; j < M; ++j)
        for (int i = 2 * j; i < M; i += j)
            phi[i] -= phi[j];
}
// END_CODE

const int mod = 1e9 + 7;

int add(int x, int y) { x += y; if (x >= mod) x -= mod; return x; }
int sub(int x, int y) { x -= y; if (x < 0) x += mod; return x; }
int mul(ll x, ll y) { return x * y % mod; }

// BEGIN_CODE
int inv[M];
void calcInv() {
    inv[1] = 1;
    for (int i = 2; i < M; ++i) {
        inv[i] = mul(sub(0, mod / i), inv[mod % i]);
        assert(mul(i, inv[i]) == 1);
    }
}
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

// primes to N
const ll n = 1000000000000LL;
const ll L = 1000000;
int small[L+1];
ll large[L+1];
void calc_pi() {
    for (int i = 1; i <= L; ++i) {
        small[i] = i-1;
        large[i] = n / i - 1;
    }
    for (ll p = 2; p <= L; ++p) {
        if (small[p] == small[p-1]) continue;
        int cntp = small[p-1];
        ll p2 = p*p;
        ll np = n / p;
        for (int i = 1; i <= min(L, n / p2); ++i) {
            ll x = np / i;
            if (x <= L) {
                large[i] -= small[x] - cntp;
            } else {
                large[i] -= large[p*i] - cntp;
            }
        }
        for (int i = L; i >= p2; --i) {
            small[i] -= small[i/p] - cntp;
        }
    }
}
ll pi(ll x) {
    if (x > L) return small[n/x];
    else return large[x];
}

int main() {
    calcPhi();
    assert(phi[30] == 1 * 2 * 4);
    calcInv();
    int x, y;
    gcd(3, 5, x, y);
    gcd(15, 10, x, y);
    crt(15, 13, 2, 5);
    crt(17, 3, 15, 2);
    return 0;
}
// END_CODE
