#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <string>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <queue>

using namespace std;

#define FOR(a, b) for (int a = 0; a < (b); ++a)
#define clr(a) memset(a, 0, sizeof(a))
#define pb(i) push_back(i)
#define forab(i, a, b) for(int i = int(a); i < int(b); ++i)
#define forba(i, b, a) for(int i = int(b) - 1; i >= int(a); --i)
#define forn(i, n) forab(i, 0, n)
#ifdef LOCAL
#define print(a) cerr << #a << ": " << a << '\n';
#else
#define print(a)
#endif

typedef long long ll;
typedef long double ldb;

const int INF = 1e9;
const ldb EPS = 1e-8;
const ldb PI = acos(-1.0);
const int MAXN = 1e5;
const ll MOD = 1e9 + 7;
//const ll MOD = 7;
//const ll PARTS = 2;
const ll PARTS = 1e5;

ll c[22];

//BEGIN ALGO
//fast power
ll power(ll x, ll d) {
    if (d == 0)
        return 1;
    if (d % 2 == 1) {
        return power(x, d - 1) * x % MOD;
    }
    ll h = power(x, d / 2);
    return h * h % MOD;
}

ll inv(ll x) {
    return power(x, MOD - 2);
}

//max power MOD in n
ll ppow(ll n) {
    ll res = 0;
    while (n > 0) {
        res += n / MOD;
        n /= MOD;
    }
    return res;
}

ll prod; //product from 1 to MOD - 1 modulo MOD
ll mul(ll n) { //product from 1 to n modulo MOD
    ll res = 1;
    for (ll i = 1; i <= n; ++i) {
        res *= i;
        res %= MOD;
    }
    return res;
}

//fact(n) modulo MOD
ll fact(ll n) {
    if (n <= 1) {
        return 1;
    }
    ll res = 1;
    res = res * power(prod, n / MOD) % MOD;
    res = res * mul(n % MOD) % MOD;
    res = res * fact(n / MOD) % MOD;
    return res;
}

//C(n, k) modulo MOD
ll getc(ll n, ll k) {
    ll pp = ppow(n);
    ll f = fact(n);
    ll pp1 = ppow(k);
    ll pp2 = ppow(n - k);
    if ( pp > pp1 + pp2)
        return 0;
    ll f1 = fact(k);
    ll f2 = fact(n - k);
    return f * inv(f1) % MOD * inv(f2) % MOD;
}

//Extended gcd
ll gcdex(ll a, ll b, ll &x, ll & y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }
    ll xo, yo;
    ll d = gcdex(b % a, a, xo, yo);
    x = yo - (b / a) * xo;
    y = xo;
    return d;
}

//Chinese remainder
//returns -1 if inconsistent
ll crt(ll mod1, ll r1, ll mod2, ll r2) {
    ll d = __gcd(mod1, mod2);
    if (r1 % d != r2 % d)
        return -1;
    ll rd = r1 % d;
    mod1 /= d;
    mod2 /= d;
    r1 /= d;
    r2 /= d;
    if (mod1 < mod2) {
        swap(mod1, mod2);
        swap(r1, r2);
    }
    ll k = (r2 - r1 % mod2 + mod2) % mod2;
    ll x, y;
    gcdex(mod1, mod2, x, y);
    x %= mod2;
    if (x < 0)
        x += mod2;
    k *= x;
    k %= mod2;
    return (k * mod1 + r1) * d + rd;
}
//END ALGO
int main() {
}

