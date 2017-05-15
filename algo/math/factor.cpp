#include <bits/stdc++.h>
#define forn(i,n) for (int i = 0; i < int(n); ++i)
using namespace std;
typedef long long ll;
typedef long double ld;

ll gcd(ll a, ll b) {
    while (a && b)
        if (a >= b)
            a %= b;
        else
            b %= a;
    return a ^ b;
}

ll mul(ll, ll, ll);

ll binpow(ll a, ll deg, ll mod) {
    ll res = 1;
    while (deg) {
        if (deg % 2)
            res = mul(res, a, mod);
        deg /= 2;
        a = mul(a, a, mod);
    }
    return res;
}

mt19937 rr(random_device{}());

//BEGIN_CODE
//WARNING: only mod <= 1e18
ll mul(ll a, ll b, ll mod) {
    ll res = a * b - (ll(ld(a) * ld(b) / ld(mod)) * mod);
    while (res < 0)
        res += mod;
    while (res >= mod)
        res -= mod;
    return res;
}

bool millerRabinTest(ll n, ll a) {
    if (gcd(n, a) > 1)
        return false;
    ll x = n - 1;
    int l = 0;
    while (x % 2 == 0) {
        x /= 2;
        ++l;
    }
    ll c = binpow(a, x, n);
    for (int i = 0; i < l; ++i) {
        ll nx = mul(c, c, n);
        if (nx == 1) {
            if (c != 1 && c != n - 1)
                return false;
            else
                return true;
        }
        c = nx;
    }
    return c == 1;
}

bool isPrime(ll n) {
    if (n == 1)
        return false;
    if (n % 2 == 0)
        return n == 2;
    // < 2^32: 2, 7, 61
    // < 3e18: 2, 3, 5, 7, 11, 13, 17, 19, 23
    // < 2^64: 2, 325, 9375, 28178, 450775, 9780504, 1795265022
    for (ll a = 2; a < min<ll>(8, n); ++a)
        if (!millerRabinTest(n, a))
            return false;
    return true;
}

//WARNING: p is not sorted
void factorize(ll x, vector<ll> &p) {
    if (x == 1)
        return;
    if (isPrime(x)) {
        p.push_back(x);
        return;
    }
    for (ll d: {2, 3, 5})
        if (x % d == 0) {
            p.push_back(d);
            factorize(x / d, p);
            return;
        }
    while (true) {
        ll x1 = rr() % (x - 1) + 1;
        ll x2 = (mul(x1, x1, x) + 1) % x;
        int i1 = 1, i2 = 2;
        while (true) {
            ll c = (x1 + x - x2) % x;
            if (c == 0)
                break;
            ll g = gcd(c, x);
            if (g > 1) {
                factorize(g, p);
                factorize(x / g, p);
                return;
            }
            if (i1 * 2 == i2) {
                i1 *= 2;
                x1 = x2;
            }
            ++i2;
            x2 = (mul(x2, x2, x) + 1) % x;
        }
    }
}
//END_CODE

bool isPrimeSlow(int x) {
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
            return false;
    return x != 1;
}

void test() {
    forn (i, 100000) {
        if (i == 0)
            continue;
        assert(isPrime(i) == isPrimeSlow(i));
        vector<ll> p;
        factorize(i, p);
        ll prod = 1;
        for (ll x: p) {
            assert(x > 1);
            assert(isPrimeSlow(x));
            prod *= x;
        }
        assert(prod == i);
    }
}

int main() {
    test();
}
