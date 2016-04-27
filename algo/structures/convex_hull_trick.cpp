#include <bits/stdc++.h>
using namespace std;
#define forn(i,n) for (int i = 0; i < int(n); ++i)
typedef long long ll;
const ll infl = ll(2e18) + ll(2e15);

const int maxn = 4004;

/*
    WARNING!!!
    - finds maximum of A*x+B
    - double check max coords for int/long long overflow
    - set min x query in put function
    - add lines with non-descending A coefficient
*/
struct FastHull {
    int a[maxn];
    ll b[maxn];
    ll p[maxn];
    int c;

    FastHull(): c(0) {}

    ll get(int x) {
        if (c == 0)
            return -infl;
        int pos = upper_bound(p, p + c, x) - p - 1;
        assert(pos >= 0);
        return (ll) a[pos] * x + b[pos];
    }

    ll divideCeil(ll p, ll q) {
        assert(q > 0);
        if (p >= 0)
            return (p + q - 1) / q;
        return -((-p) / q);
    }

    void put(int A, ll B) {
        while (c > 0) {
            if (a[c - 1] == A && b[c - 1] >= B)
                return;
            ll pt = p[c - 1];
            if (a[c - 1] * pt + b[c - 1] < A * pt + B) {
                --c;
                continue;
            }
            ll q = A - a[c - 1];
            ll np = divideCeil(b[c - 1] - B, q);
            p[c] = np;
            a[c] = A;
            b[c] = B;
            ++c;
            return;
        }
        if (c == 0) {
            a[c] = A, b[c] = B;
            p[c] = -1e9; //min x query
            ++c;
            return;
        }
    }
    
};

struct SlowHull {
    vector<pair<int, ll>> v;

    void put(int a, ll b) {
        v.emplace_back(a, b);
    }

    ll get(ll x) {
        ll best = -infl;
        for (auto p: v)
            best = max(best, p.first * x + p.second);
        return best;
    }
};

int main() {
    FastHull hull1;
    SlowHull hull2;
    vector<int> as;
    forn (ii, 10000)
        as.push_back(rand() % int(1e8));
    sort(as.begin(), as.end());
    forn (ii, 10000) {
        int b = rand() % int(1e8);
        hull1.put(as[ii], b);
        hull2.put(as[ii], b);
        int x = rand() % int(2e8 + 1) - int(1e8);
        assert(hull1.get(x) == hull2.get(x));
    }
}
