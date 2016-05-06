#include <bits/stdc++.h>
#define forn(i, n) for (int i = 0; i < int(n); ++i)
using namespace std;
typedef long double ld;

const ld eps = 1e-9;

bool eq(ld a, ld b) { return fabsl(a - b) < eps; }
bool ge(ld a, ld b) { return a - b > -eps; }
bool gt(ld a, ld b) { return a - b > eps; }
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
    pt operator/(const ld &a) const { gassert(!eq(a, 0)); return pt{x / a, y / a}; }
    void operator*=(const ld &a) { x *= a, y *= a; }
    void operator/=(const ld &a) { gassert(!eq(a, 0)); x /= a, y /= a; }

    bool operator<(const pt &p) const {
        if (eq(x, p.x)) return gt(p.y, y);
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
        return gt(a, 0) || (eq(a, 0) && gt(b, 0));
    }

    line(ld _a, ld _b, ld _c): a(_a), b(_b), c(_c) {
        ld d = pt{a, b}.abs();
        gassert(!eq(d, 0));
        a /= d, b /= d, c /= d;
    }

    ld signedDist(pt p) {
        return p * pt{a, b} + c;
    }
};

ld pointSegmentDist(pt p, pt a, pt b) {
    ld res = min((p - a).abs(), (p - b).abs());
    if (a != b && ge((p - a) * (b - a), 0) && ge((p - b) * (a - b), 0))
        res = min(res, fabsl((p - a) % (b - a)) / (b - a).abs());
    return res;
}

pt linesIntersection(line l1, line l2) {
    ld D = l1.a * l2.b - l1.b * l2.a;
    if (eq(D, 0)) {
        if (eq(l1.c, l2.c)) {
            //equal lines
        } else {
            //no intersection
        }
    }
    ld dx = -l1.c * l2.b + l1.b * l2.c;
    ld dy = -l1.a * l2.c + l1.c * l2.a;
    pt res{dx / D, dy / D};
    //gassert(eq(l1.signedDist(res), 0));
    //gassert(eq(l2.signedDist(res), 0));
    return res;
}

bool pointInsideSegment(pt p, pt a, pt b) {
    if (!eq((p - a) % (p - b), 0))
        return false;
    return ge(0, (a - p) * (b - p));
}

bool checkSegmentIntersection(pt a, pt b, pt c, pt d) {
    if (eq((a - b) % (c - d), 0)) {
        if (pointInsideSegment(a, c, d) || pointInsideSegment(b, c, d) || 
                pointInsideSegment(c, a, b) || pointInsideSegment(d, a, b)) {
            //intersection of parallel segments
            return true;
        }
        return false;
    }

    ld s1, s2;

    s1 = (c - a) % (b - a);
    s2 = (d - a) % (b - a);
    if (gt(s1, 0) && gt(s2, 0))
        return false;
    if (gt(0, s1) && gt(0, s2))
        return false;

    swap(a, c), swap(b, d);

    s1 = (c - a) % (b - a);
    s2 = (d - a) % (b - a);
    if (gt(s1, 0) && gt(s2, 0))
        return false;
    if (gt(0, s1) && gt(0, s2))
        return false;

    return true;
}

//WARNING! run checkSegmentIntersecion before and process parallel case manually
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
    if (gt(d2, sqr(r1 + r2)) || gt(sqr(r1 - r2), d2)) {
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

    if (gt(sqr(r), d2)) {
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
    if (gt(fabsl(d), r))
        return {};
    pt h = a - pt{l.a, l.b} * d;
    if (eq(fabsl(d), r))
        return {h};
    pt w = pt{l.a, l.b}.rot() * sqrtl(max<ld>(0, sqr(r) - sqr(d)));
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
            if (gt(0, d))
                continue;
            d = sqrtl(max<ld>(0, d));
            pt magic = pt{r, d} / z;
            line l(magic * c, magic % c, r1 * i);
            l.c -= pt{l.a, l.b} * a;
            res.push_back(l);
        }
    return res;
}
