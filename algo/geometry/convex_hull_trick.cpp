//http://opentrains.snarknews.info/~ejudge/team.cgi?contest_id=001325 problem F
#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define sz(x) ((int) (x).size())

#include "primitives.cpp"

//BEGIN_CODE
struct Hull {
    vector<pt> top, bot;

    //check: add points in strictly increasing order
    void append(pt p) {
        while (sz(bot) > 1 && (p - bot.back()) % 
                    (p - *next(bot.rbegin())) >= -eps)
            bot.pop_back();
        bot.push_back(p);
        while (sz(top) > 1 && (p - top.back()) % 
                    (p - *next(top.rbegin())) <= eps)
            top.pop_back();
        top.push_back(p);
    }

    pt mostDistant(pt dir) {
        dir = dir.rot();
        auto &v = dir.x < 0 ? top : bot;
        int l = -1, r = sz(v) - 1;
        while (l + 1 < r) {
            int c = (l + r) / 2;
            if (dir % (v[c + 1] - v[c]) > 0)
                r = c;
            else
                l = c;
        }
        return v[r];
    }
};
