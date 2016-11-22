#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
typedef long long ll;
typedef long long i64;
typedef long double ld;
const int inf = int(1e9) + int(1e5);
const ll infl = ll(2e18) + ll(1e10);

#include "primitives.cpp"

bool cmpAngle(const pt &a, const pt &b) {
    bool ar = a.right(), br = b.right();
    if (ar != br)
        return ar;
    return a % b > eps;
}

//BEGIN_CODE
struct Hull {
    vector<pt> p, v;
    pt M;
    int n;

    void build() {
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());
        vector<pt> top, bot;
        for (auto P: p) {
            while (sz(top) > 1 && (P - top.back()) %
                    (top.back() - *next(top.rbegin())) <= eps)
                top.pop_back();
            top.push_back(P);
            while (sz(bot) > 1 && (P - bot.back()) %
                    (bot.back() - *next(bot.rbegin())) >= -eps)
                bot.pop_back();
            bot.push_back(P);
        }
        if (sz(top))
            top.pop_back();
        reverse(top.begin(), top.end());
        if (sz(top))
            top.pop_back();
        p = bot;
        p.insert(p.end(), top.begin(), top.end());

        n = sz(p);
        M = accumulate(p.begin(), p.end(), pt{0, 0});
        M = M * (1. / n);
        v.resize(n);
        forn (i, n)
            v[i] = p[i] - M;
        int r = min_element(v.begin(), v.end(), 
                cmpAngle) - v.begin();
        rotate(v.begin(), v.begin() + r, v.end());
        rotate(p.begin(), p.begin() + r, p.end());
        gassert(is_sorted(v.begin(), v.end(), cmpAngle));
    }

    bool visSide(pt a, int i) {
        return (p[(i + 1) % n] - a) % (p[i % n] - a) > eps;
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

    pair<int, int> tangents(pt a) {
        assert(n >= 3);
        if (a == M)
            return {-1, -1};
        int pos = lower_bound(v.begin(), v.end(), a - M,
                cmpAngle) - v.begin();
        pt L = p[(pos + n - 1) % n], R = p[pos % n];
        if ((R - L) % (a - L) >= -eps)
            return {-1, -1};
        int pos2 = lower_bound(v.begin(), v.end(), M - a,
                cmpAngle) - v.begin();
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
    h.p = {pt{0, 0}, pt{0, 1}, pt{1, 0}};
    h.build(); //{1, 0}, {0, 1}, {0, 0} after build
    auto tgs = h.tangents(pt{1, 1});
    cerr << tgs.first << ' ' << tgs.second << '\n'; //1 0
}

