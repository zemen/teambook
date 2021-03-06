//https://contest.yandex.ru/contest/3644/problems/A/
#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define all(x) x.begin(), x.end()
#define forn(i,n) for (int i = 0; i < int(n); ++i)
typedef long long ll;
typedef long long i64;
typedef long double ld;
const int inf = int(1e9) + int(1e5);
const ll infl = ll(2e18) + ll(1e10);

#include "primitives.cpp"

//BEGIN_CODE
struct Cmp {
    pt M, v0;

    bool operator()(const pt &a, const pt &b) {
        pt va{v0 * (a - M), v0 % (a - M)};
        pt vb{v0 * (b - M), v0 % (b - M)};
        return cmpAngle(va, vb);
    }
};

struct Hull {
    vector<pt> h;
    int n;

    void build() {
        sort(all(h));
        h.erase(unique(all(h)), h.end());
        vector<pt> top, bot;
        for (auto p: h) {
            while (sz(bot) > 1 && (p - bot.back()) %
                    (p - *next(bot.rbegin())) >= -eps)
                bot.pop_back();
            bot.push_back(p);
            while (sz(top) > 1 && (p - top.back()) %
                    (p - *next(top.rbegin())) <= eps)
                top.pop_back();
            top.push_back(p);
        }
        if (sz(top))
            top.pop_back();
        reverse(all(top));
        if (sz(top))
            top.pop_back();
        h = bot;
        h.insert(h.end(), all(top));
        n = sz(h);
    }

    bool visSide(pt a, int i) {
        return (h[(i + 1) % n] - a) % (h[i % n] - a) > eps;
    }

    bool vis(pt a, int i) {
        return visSide(a, i) || visSide(a, i + n - 1);
    }

    bool isTangent(pt a, int i) {
        return visSide(a, i) != visSide(a, i + n - 1);
    }

    int binSearch(int l, int r, pt a) {
        //tricky binsearch; l < r not necessarily
        while (abs(l - r) > 1) {
            int c = (l + r) / 2;
            if (vis(a, c))
                l = c;
            else
                r = c;
        }
        assert(isTangent(a, l));
        return l % n;
    }

    //check: n >= 3
    pair<int, int> tangents(pt a) {
        assert(n >= 3);
        pt M = (h[0] + h[1] + h[2]) * (1. / 3);
        if (a == M)
            return {-1, -1};
        Cmp cmp{M, h[0] - M};
        //assert(is_sorted(all(h), cmp));
        int pos = upper_bound(all(h), a, cmp) - h.begin();
        pt L = h[(pos + n - 1) % n], R = h[pos % n];
        if ((R - L) % (a - L) >= -eps)
            return {-1, -1}; //point inside hull
        int pos2 = upper_bound(all(h), M*2-a, cmp) - h.begin();
        assert(pos % n != pos2 % n);
        if (pos > pos2)
            pos2 += n;
        return {binSearch(pos, pos2, a),
                binSearch(pos + n - 1, pos2 - 1, a)};
    }
};
//END_CODE

int main() {
    Hull h;
    h.h = {pt{0, 0}, pt{0, 1}, pt{1, 0}};
    h.build(); //{0, 0}, {1, 0}, {0, 1} after build
    auto tgs = h.tangents(pt{1, 1});
    cerr << tgs.first << ' ' << tgs.second << '\n'; //2 1
}
