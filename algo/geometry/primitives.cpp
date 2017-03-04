#pragma once
#include <bits/stdc++.h>
#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define sz(x) ((int) (x).size())
using namespace std;
typedef long double ld;

const ld eps = 1e-9;

bool ze(ld a) { return fabsl(a) < eps; }
bool eq(ld a, ld b) { return ze(a - b); }
ld sqr(ld x) { return x * x; }
ld Sqrt(ld x) { return sqrtl(max<ld>(0, x)); }

struct pt {
    ld x, y;

    pt operator+(const pt &p) const { return pt{x + p.x, y + p.y}; }
    pt operator-(const pt &p) const { return pt{x - p.x, y - p.y}; }
    ld operator*(const pt &p) const { return x * p.x + y * p.y; }
    ld operator%(const pt &p) const { return x * p.y - y * p.x; }
    pt operator*(const ld &a) const { return pt{x * a, y * a}; }
    bool operator==(const pt &p) const { return eq(x, p.x) && eq(y, p.y); }

    bool up() const { return ze(y) ? x > 0 : y > 0; }

    bool operator<(const pt &p) const {
        if (!eq(x, p.x))
            return x < p.x;
        if (!eq(y, p.y))
            return y < p.y;
        return false;
    }

    pt rot() { return pt{-y, x}; }
    pt rotCw(pt e) { return pt{e * *this, e % *this}; }
    ld abs() const { return hypotl(x, y); }
    ld abs2() const { return x * x + y * y; }
};

istream &operator>>(istream &in, pt &p) { return in >> p.x >> p.y; }
ostream &operator<<(ostream &out, const pt &p) { return out << p.x << ' ' << p.y; }

bool cmpAngle(const pt &a, const pt &b) {
    bool au = a.up(), bu = b.up();
    if (au != bu)
        return au;
    return a % b > eps;
}

//BEGIN_CODE
struct line {
    pt v;
    ld c; // v * p = c

    //check: p1 != p2
    line(pt p1, pt p2) {
        v = (p2 - p1).rot();
        v = v * (1. / v.abs());
        c = v * p1;
    }

    // Convert from ax + by + c = 0

    //check: a^2+b^2 > 0
    line(ld a, ld b, ld _c): v(pt{a, b}), c(-_c) {
        ld d = v.abs();
        v = v * (1. / d);
        c /= d;
    }

    //check: v.abs() == 1
    ld signedDist(pt p) {
        return v * p - c;
    }
};

//check: a != b
pt lineProjection(pt p, pt a, pt b) {
    pt v = (b - a).rot();
    ld s = (p - a) % (b - a);
    return p + v * (s / v.abs2());
}

ld pointSegmentDist(pt p, pt a, pt b) {
    if ((p - a) * (b - a) <= 0 || ze((b - a).abs()))
        return (p - a).abs();
    if ((p - b) * (a - b) <= 0)
        return (p - b).abs();
    return fabsl((p - a) % (p - b)) / (b - a).abs();
}

pt linesIntersection(line l1, line l2) {
    ld d = l1.v.x * l2.v.y - l1.v.y * l2.v.x;
    if (ze(d)) {
        if (eq(l1.c, l2.c)) {
            //stub: equal lines
        } else {
            //stub: empty intersection
        }
        return pt{1e18, 1e18};
    }
    ld dx = l1.c * l2.v.y - l1.v.y * l2.c;
    ld dy = l1.v.x * l2.c - l1.c * l2.v.x;
    return pt{dx / d, dy / d};
}

pt linesIntersection(pt a, pt b, pt c, pt d) {
    ld s = (b - a) % (d - c);
    if (ze(s)) {
        //stub: parallel or equal lines
        return pt{1e18, 1e18};
    }
    ld s1 = (c - a) % (d - a);
    return a + (b - a) * (s1 / s);
}

bool pointInsideSegment(pt p, pt a, pt b) {
    if (!ze((p - a) % (p - b)))
        return false;
    ld prod = (a - p) * (b - p);
    return ze(prod) || prod < 0;
    if (ze(prod)) {
        //stub: coincides with segment end
        return true;
    }
    return prod < 0;
}

bool checkSegmentIntersection(pt a, pt b, pt c, pt d) {
    if (ze((a - b) % (c - d))) {
        if (pointInsideSegment(a, c, d) ||
            pointInsideSegment(b, c, d) ||
            pointInsideSegment(c, a, b) ||
            pointInsideSegment(d, a, b)) {
            //stub: intersection of parallel segments
            return true;
        }
        return false;
    }
    ld s1, s2;
    forn (iter, 2) {
        s1 = (c - a) % (b - a);
        s2 = (d - a) % (b - a);
        if (s1 > eps && s2 > eps)
            return false;
        if (s1 < -eps && s2 < -eps)
            return false;
        swap(a, c), swap(b, d);
    }
    return true;
}

vector<pt> lineCircleIntersection(line l, pt a, ld r) {
    ld d = l.signedDist(a);
    pt h = a - l.v * d;
    if (eq(fabsl(d), r))
        return {h};
    else if (fabsl(d) > r)
        return {};
    pt w = l.v.rot() * Sqrt(sqr(r) - sqr(d));
    return {h + w, h - w};
}

vector<pt> circlesIntersction(pt a, ld r1, pt b, ld r2) {
    ld d = (a - b).abs();
    if (ze(d) && eq(r1, r2)) {
        //stub: equal circles
        return {};
    }
    //  intersection is non-empty iff
    //  triangle with sides r1, r2, d exists
    ld per = r1 + r2 + d;
    ld mx = max(max(r1, r2), d);
    int num = 2;
    if (eq(mx * 2, per)) {
        num = 1;
    } else if (mx * 2 > per)
        return {};
    ld part = (sqr(r1) + sqr(d) - sqr(r2)) / ld(2 * d);
    pt h = a + (b - a) * (part / d);
    if (num == 1)
        return {h};
    ld dh = Sqrt(sqr(r1) - sqr(part));
    pt w = ((b - a) * (dh / d)).rot();
    return {h + w, h - w};
}

vector<pt> circleTangents(pt p, pt a, ld r) {
    ld d = (p - a).abs();
    if (eq(r, d))
        return {p};
    else if (r > d)
        return {};
    ld len = Sqrt(sqr(d) - sqr(r));
    vector<pt> res;
    pt vec = (a - p) * (len / sqr(d));
    for (int sgn: {-1, 1})
        res.push_back(p + vec.rotCw(pt{len, r * sgn}));
    return res;
}

vector<line> circlesBitangents(pt a, ld r1, pt b, ld r2) {
    ld d = (a - b).abs();
    if (ze(d) && eq(r1, r2)) {
        //stub: equal circles
        return {};
    }

    vector<line> res;
    for (int s1: {-1, 1})
        for (int s2: {-1, 1}) {
            //  inner tangent iff s1 != s2
            //  treat radii as signed
            ld r = s2 * r2 - s1 * r1;
            if (eq(fabsl(r), d)) {
                //  incident tangents; need only one copy
                if (s1 == 1)
                    continue;
            } else if (fabsl(r) > d)
                continue;
            ld len = Sqrt(sqr(d) - sqr(r));
            line l(a, a + (b - a).rotCw(pt{len, r}));
            l.c -= s1 * r1;
            res.push_back(l);
        }
    return res;
}
