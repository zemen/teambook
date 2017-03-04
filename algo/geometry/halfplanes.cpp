#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define all(x) x.begin(), x.end()
#include "primitives.cpp"
typedef vector<int> vi;

bool cmpLine(const line &a, const line &b) {
    bool au = a.v.up(), bu = b.v.up();
    if (au != bu)
        return au;
    ld prod = a.v % b.v;
    if (!ze(prod))
        return prod > 0;
    // the strongest constraint is first for correct unique
    return a.c > b.c;
}

bool eqLine(const line &a, const line &b) {
    return a.v.up() == b.v.up() && ze(a.v % b.v);
}

//BEGIN_CODE
ld det3x3(line a, line b, line c) {
    return a.c * (b.v % c.v)
         + b.c * (c.v % a.v)
         + c.c * (a.v % b.v);
}

//check: bounding box is included
vector<pt> halfplanesIntersection(vector<line> l) {
    sort(all(l), cmpLine); //the strongest constraint is first
    l.erase(unique(all(l), eqLine), l.end());
    int n = sz(l);
    vi st;
    forn (iter, 2)
        forn (i, n) {
            while (sz(st) > 1) {
                int j = st.back(), k = *next(st.rbegin());
                if (l[k].v % l[i].v <= eps || 
                        det3x3(l[k], l[j], l[i]) <= eps)
                    break;
                st.pop_back();
            }
            st.push_back(i);
        }

    vi pos(n, -1);
    bool ok = false;
    forn (i, sz(st)) {
        int id = st[i];
        if (pos[id] != -1) {
            st = vi(st.begin() + pos[id], st.begin() + i);
            ok = true;
            break;
        } else
            pos[id] = i;
    }
    if (!ok)
        return {};

    vector<pt> res;
    pt M{0, 0};
    int k = sz(st);
    forn (i, k) {
        line l1 = l[st[i]], l2 = l[st[(i + 1) % k]];
        res.push_back(linesIntersection(l1, l2));
        M = M + res.back();
    }
    M = M * (1. / k);
    for (int id: st)
        if (l[id].signedDist(M) < -eps)
            return {};
    return res;
}
