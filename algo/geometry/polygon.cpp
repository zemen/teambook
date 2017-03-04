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

//check: p is oriented ccw
bool segmentInsidePolygon(pt a, pt b, pt *p, int n) {
    if (!pointInsidePolygon((a + b) * .5, p, n))
        return false;
    if (ze((a - b).abs()))
        return true;
    forn (i, n) {
        pt c = p[i];
        if (ze((a - c) % (b - c)) &&
                (a - c) * (b - c) < -eps) {
            //point inside interval
            pt pr = p[(i + n - 1) % n];
            pt nx = p[(i + 1) % n];
            if ((c - pr) % (nx - c) > eps)
                return false;
            ld s1 = (pr - a) % (b - a);
            ld s2 = (nx - a) % (b - a);
            if ((s1 > eps || s2 > eps) &&
                    (s1 < -eps || s2 < -eps))
                return false;
        }
        //interval intersection
        pt d = p[(i + 1) % n];
        ld s1 = (a - c) % (d - c);
        ld s2 = (b - c) % (d - c);
        if (s1 >= -eps && s2 >= -eps)
            continue;
        if (s1 <= eps && s2 <= eps)
            continue;

        s1 = (c - a) % (b - a);
        s2 = (d - a) % (b - a);
        if (s1 >= -eps && s2 >= -eps)
            continue;
        if (s1 <= eps && s2 <= eps)
            continue;

        return false;
    }
    return true;
}
