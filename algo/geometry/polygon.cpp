#include <bits/stdc++.h>
using namespace std;
#define forn(i,n) for (int i = 0; i < int(n); ++i)

#include "primitives.cpp"

//BEGIN_CODE
bool pointInsidePolygon(pt a, pt *p, int n) {
    double sumAng = 0;
    forn (i, n) {
        pt A = p[i], B = p[(i + 1) % n];
        if (pointInsideSegment(a, A, B))
            return true;
        sumAng += atan2((A - a) % (B - a), (A - a) * (B - a));
    }
    return fabs(sumAng) > 1;
}

//p must be oriented counterclockwise
bool segmentInsidePolygon(pt a, pt b, pt *p, int n) {
    if (!pointInsidePolygon((a + b) / 2, p, n))
        return false;
    if (a == b)
        return true;
    forn (i, n) {
        pt c = p[i];
        if (eq((a - c) % (b - c), 0) &&
                gt(0, (a - c) * (b - c))) {
            //point on segment
            pt pr = p[(i + n - 1) % n];
            pt nx = p[(i + 1) % n];
            if (gt((c - pr) % (nx - c), 0))
                return false;
            ld s1 = (pr - a) % (b - a);
            ld s2 = (nx - a) % (b - a);
            if ((gt(s1, 0) || gt(s2, 0)) &&
                    (gt(0, s1) || gt(0, s2)))
                return false;
        }
        //interval intersection
        pt d = p[(i + 1) % n];
        ld s1 = (a - c) % (d - c);
        ld s2 = (b - c) % (d - c);
        if (ge(s1, 0) && ge(s2, 0))
            continue;
        if (ge(0, s1) && ge(0, s2))
            continue;

        s1 = (c - a) % (b - a);
        s2 = (d - a) % (b - a);
        if (ge(s1, 0) && ge(s2, 0))
            continue;
        if (ge(0, s1) && ge(0, s2))
            continue;

        return false;
    }
    return true;
}
