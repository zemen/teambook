#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define forab(i, a, b) for (int i = int(a); i < int(b); ++i)
#include "primitives.cpp"

ld det3x3(line &l1, line &l2, line &l3) {
    return l1.a * (l2.b * l3.c - l2.c * l3.b) +
           l1.b * (l2.c * l3.a - l2.a * l3.c) +
           l1.c * (l2.a * l3.b - l2.b * l3.a);
}

vector<pt> halfplanesIntersecion(vector<line> lines) {
    sort(lines.begin(), lines.end(),
        [](const line &a, const line &b) {
                bool ar = a.right(), br = b.right();
                if (ar ^ br)
                    return ar;
                ld prod = (pt{a.a, a.b} % pt{b.a, b.b});
                if (!ze(prod))
                    return prod > 0;
                return a.c < b.c;
            });
    vector<line> lines2;
    pt pr;
    forn (i, lines.size()) {
        pt cur{lines[i].a, lines[i].b};
        if (i == 0 || cur != pr)
            lines2.push_back(lines[i]);
        pr = cur;
    }
    lines = lines2;
    int n = lines.size();
    forn (i, n)
        lines[i].id = i;
    vector<line> hull;
    forn (i, 2 * n) {
        line l = lines[i % n];
        while ((int) hull.size() >= 2) {
            ld D = det3x3(*next(hull.rbegin()), hull.back(), l);
            if (D >= -eps)
                break;
            hull.pop_back();
        }
        hull.push_back(l);
    }
    vector<int> firstTime(n, -1);
    vector<line> v;
    forn (i, hull.size()) {
        int cid = hull[i].id;
        if (firstTime[cid] == -1) {
            firstTime[cid] = i;
            continue;
        }
        forab(j, firstTime[cid], i)
            v.push_back(hull[j]);
        break;
    }
    n = v.size();
    if (v.empty()) {
        //empty intersection
        return {};
    }
    v.push_back(v[0]);
    vector<pt> res;
    pt center{0, 0};
    forn (i, n) {
        res.push_back(linesIntersection(v[i], v[i + 1]));
        center = center + res.back();
    }
    center = center / n;
    for (auto l: lines)
        if (l.signedDist(center) < -eps) {
            //empty intersection
            return {};
        }
    return res;
}
