#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define sz(x) ((int) (x).size())

#include "primitives.cpp"

bool cmpAngle(const pt &a, const pt &b) {
    bool ar = a.right(), br = b.right();
    if (ar ^ br)
        return ar;
    return a % b > eps;
}

struct Hull {
    vector<pt> top, bot;

    void append(pt p) {
        while (bot.size() > 1 && (p - bot.back())
                % (bot.back() - *next(bot.rbegin())) >= -eps)
            bot.pop_back();
        bot.push_back(p);
        while (top.size() > 1 && (p - top.back())
                % (top.back() - *next(top.rbegin())) <= eps)
            top.pop_back();
        top.push_back(p);
    }

    void build(vector<pt> h) {
        sort(h.begin(), h.end());
        h.erase(unique(h.begin(), h.end()), h.end());
        top.clear(), bot.clear();
        for (pt p: h)
            append(p);
    }

    pt kth(int k) {
        if (k < sz(bot))
            return bot[k];
        else
            return top[sz(top) - (k - sz(bot)) - 2];
    }

    pt mostDistant(pt dir) {
        if (bot.empty()) {
            //empty hull
            return pt{1e18, 1e18};
        }
        if (bot.size() == 1)
            return bot.back();
        dir = dir.rot();
        int n = sz(top) + sz(bot) - 2;
        int L = -1, R = n;
        while (L + 1 < R) {
            int C = (L + R) / 2;
            pt v = kth((C + 1) % n) - kth(C);
            if (cmpAngle(dir, v)) //finds upper bound
                R = C;
            else
                L = C;
        }
        return kth(R % n);
    }
};
