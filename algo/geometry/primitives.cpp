#pragma once
#include <bits/stdc++.h>
#define forn(i, n) for (int i = 0; i < int(n); ++i)
using namespace std;
typedef long double ld;

const ld eps = 1e-9;

bool ze(ld a) { return fabsl(a) < eps; }
bool eq(ld a, ld b) { return ze(a - b); }
ld sqr(ld x) { return x * x; }

#ifdef LOCAL
#define gassert assert
#else
void gassert(bool) {}
#endif

struct pt {
    ld x, y;

    pt operator+(const pt &p) const { return pt{x + p.x, y + p.y}; }
    pt operator-(const pt &p) const { return pt{x - p.x, y - p.y}; }
    ld operator*(const pt &p) const { return x * p.x + y * p.y; }
    ld operator%(const pt &p) const { return x * p.y - y * p.x; }

    pt operator*(const ld &a) const { return pt{x * a, y * a}; }
    pt operator/(const ld &a) const { gassert(!ze(a)); return pt{x / a, y / a}; }
    void operator*=(const ld &a) { x *= a, y *= a; }
    void operator/=(const ld &a) { gassert(!ze(a)); x /= a, y /= a; }

    bool operator<(const pt &p) const {
        if (eq(x, p.x)) return y - p.y < -eps;
        return x < p.x;
    }

    bool operator==(const pt &p) const { return eq(x, p.x) && eq(y, p.y); }
    bool operator!=(const pt &p) const { return !(*this == p); }

    bool right() const { return pt{0, 0} < *this; }

    pt rot() { return pt{-y, x}; }
    ld abs() const { return hypotl(x, y); }
    ld abs2() const { return x * x + y * y; }
};

istream &operator>>(istream &in, pt &p) { return in >> p.x >> p.y; }
ostream &operator<<(ostream &out, const pt &p) { return out << p.x << ' ' << p.y; }

//BEGIN_CODE
//WARNING! do not forget to normalize vector (a,b)
struct line {
    ld a, b, c;
    int id;

    line(pt p1, pt p2) {
        gassert(p1 != p2);
        pt n = (p2 - p1).rot();
        n /= n.abs();
        a = n.x, b = n.y;
        c = -(n * p1);
    }

    bool right() const {
        return a > eps || (ze(a) && b > eps);
    }

    line(ld _a, ld _b, ld _c): a(_a), b(_b), c(_c) {
        ld d = pt{a, b}.abs();
        gassert(!ze(d));
        a /= d, b /= d, c /= d;
    }

    ld signedDist(pt p) {
        return p * pt{a, b} + c;
    }
};

ld pointSegmentDist(pt p, pt a, pt b) {
    ld res = min((p - a).abs(), (p - b).abs());
    if (a != b && (p - a) * (b - a) >= 0 &&
            (p - b) * (a - b) >= 0)
        res = min(res,
            fabsl((p - a) % (b - a)) / (b - a).abs());
    return res;
}

pt linesIntersection(line l1, line l2) {
    ld D = l1.a * l2.b - l1.b * l2.a;
    if (ze(D)) {
        if (eq(l1.c, l2.c)) {
            //equal lines
        } else {
            //no intersection
        }
    }
    ld dx = -l1.c * l2.b + l1.b * l2.c;
    ld dy = -l1.a * l2.c + l1.c * l2.a;
    pt res{dx / D, dy / D};
    //gassert(ze(l1.signedDist(res)));
    //gassert(ze(l2.signedDist(res)));
    return res;
}

bool pointInsideSegment(pt p, pt a, pt b) {
    if (!ze((p - a) % (p - b)))
        return false;
    return (a - p) * (b - p) <= eps;
}

bool checkSegmentIntersection(pt a, pt b, pt c, pt d) {
    if (ze((a - b) % (c - d))) {
        if (pointInsideSegment(a, c, d) ||
            pointInsideSegment(b, c, d) ||
            pointInsideSegment(c, a, b) ||
            pointInsideSegment(d, a, b)) {
            //intersection of parallel segments
            return true;
        }
        return false;
    }

    ld s1, s2;
    forn (q, 2) {
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

// WARNING! run checkSegmentIntersecion before and process
// parallel case manually
pt segmentsIntersection(pt a, pt b, pt c, pt d) {
    ld S = (b - a) % (d - c);
    ld s1 = (c - a) % (d - a);
    return a + (b - a) / S * s1;
}

vector<pt> circlesIntersction(pt a, ld r1, pt b, ld r2) {
    ld d2 = (a - b).abs2();
    ld d = (a - b).abs();

    if (a == b && eq(r1, r2)) {
        //equal circles
    }
    if (d2 - sqr(r1 + r2) > eps || sqr(r1 - r2) - d2 > eps) {
        //empty intersection
        return {};
    }
    int num = 2;
    if (eq(sqr(r1 + r2), d2) || eq(sqr(r1 - r2), d2))
        num = 1;
    ld cosa = (sqr(r1) + d2 - sqr(r2)) / ld(2 * r1 * d);
    ld oh = cosa * r1;
    pt h = a + ((b - a) / d * oh);
    if (num == 1)
        return {h};
    ld hp = sqrtl(max(0.L, 1 - cosa * cosa)) * r1;

    pt w = ((b - a) / d * hp).rot();
    return {h + w, h - w};
}

//a is circle center, p is point
vector<pt> circleTangents(pt a, ld r, pt p) {
    ld d2 = (a - p).abs2();
    ld d = (a - p).abs();

    if (sqr(r) - d2 > eps) {
        //no tangents
        return {};
    }
    if (eq(sqr(r), d2)) {
        //point lies on circle - one tangent
        return {p};
    }

    pt B = p - a;
    pt H = B * sqr(r) / d2;
    ld h = sqrtl(d2 - sqr(r)) * ld(r) / d;
    pt w = (B / d * h).rot();
    H = H + a;
    return {H + w, H - w};
}

vector<pt> lineCircleIntersection(line l, pt a, ld r) {
    ld d = l.signedDist(a);
    if (fabsl(d) - r > eps)
        return {};
    pt h = a - pt{l.a, l.b} * d;
    if (eq(fabsl(d), r))
        return {h};
    pt w(pt{l.a, l.b}.rot() * sqrtl(max<ld>(0, sqr(r)-sqr(d))));
    return {h + w, h - w};
}

//modified magic from e-maxx
vector<line> commonTangents(pt a, ld r1, pt b, ld r2) {
    if (a == b && eq(r1, r2)) {
        //equal circles
        return {};
    }
    vector<line> res;
    pt c = b - a;
    ld z = c.abs2();
    for (int i = -1; i <= 1; i += 2)
        for (int j = -1; j <= 1; j += 2) {
            ld r = r2 * j - r1 * i;
            ld d = z - sqr(r);
            if (d < -eps)
                continue;
            d = sqrtl(max<ld>(0, d));
            pt magic = pt{r, d} / z;
            line l(magic * c, magic % c, r1 * i);
            l.c -= pt{l.a, l.b} * a;
            res.push_back(l);
        }
    return res;
}
