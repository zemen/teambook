#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
#define all(x) (x).begin(), (x).end()
typedef long long ll;
typedef long long i64;
typedef long double ld;
const int inf = int(1e9) + int(1e5);
const ll infl = ll(2e18) + ll(1e10);

const ld eps = 1e-9;
bool ze(ld x) {
    return fabsl(x) < eps;
}
struct pt {
    ld x, y, z;

    pt operator+(const pt &p) const {
        return pt{x + p.x, y + p.y, z + p.z};
    }

    pt operator-(const pt &p) const {
        return pt{x - p.x, y - p.y, z - p.z};
    }

    ld operator*(const pt &p) const {
        return x * p.x + y * p.y + z * p.z;
    }

    pt operator*(ld a) const {
        return pt{x * a, y * a, z * a};
    }

    pt operator%(const pt &p) const {
        return pt{y * p.z - z * p.y,
                  z * p.x - x * p.z,
                  x * p.y - y * p.x};
    }

    ld abs() const {
        return sqrtl(*this * *this);
    }

    ld abs2() const {
        return *this * *this;
    }

    pt norm() const {
        ld d = abs();
        return pt{x / d, y / d, z / d};
    }
};

//BEGIN_CODE
struct Plane {
    pt v;
    ld c;

    Plane(pt a, pt b, pt c) {
        v = ((b - a) % (c - a)).norm();
        this->c = a * v;
    }

    ld dist(pt p) {
        return p * v - c;
    }
};

pt projection(pt p, pt a, pt b) {
    pt v = b - a;
    if (ze(v.abs2())) {
        //stub: bad line
        return a;
    }
    return a + v * (((p - a) * v) / (v * v));
}

pair<pt, pt> planesIntersection(Plane a, Plane b) {
    pt dir = a.v % b.v;
    if (ze(dir.abs2())) {
        //stub: parallel planes
        return {pt{1e18, 1e18, 1e18}, pt{1e18, 1e18, 1e18}};
    }
    ld s = a.v * b.v;
    pt v3 = b.v - a.v * s;
    pt h = a.v * a.c + v3 * ((b.c - a.c * s) / (v3 * v3));
    return {h, h + dir};
}

pair<pt, pt> commonPerpendicular(pt a, pt b, pt c, pt d) {
    pt v = (b - a) % (d - c);
    ld S = v.abs();
    if (ze(S)) {
        //stub: parallel lines
        return {pt{1e18, 1e18, 1e18}, pt{1e18, 1e18, 1e18}};
    }
    v = v.norm();
    pt sh = v * (v * c - v * a);
    pt a2 = a + sh;
    ld s1 = ((c - a2) % (d - a2)) * v;
    pt p = a + (b - a) * (s1 / S);
    return {p, p + sh};
}

/*
Absolute error test
testProjection: 1e1 -> -16.3
testProjection: 1e3 -> -14.1
testProjection: 1e4 -> -13.1
testProjection: 1e5 -> -12.3
testProjection: 1e6 -> -11.2
testPlanesIntersection: 1e1 -> -11.5
testPlanesIntersection: 1e3 -> -8.6
testPlanesIntersection: 1e4 -> -8.3
testPlanesIntersection: 1e5 -> -7.4
testPlanesIntersection: 1e6 -> -6.5
testCommonPerpendicular: 1e1 -> -13.5
testCommonPerpendicular: 1e3 -> -11.4
testCommonPerpendicular: 1e4 -> -10.5
testCommonPerpendicular: 1e5 -> -8.7
testCommonPerpendicular: 1e6 -> -8.6
*/
//END_CODE

ll N = 1e5;
const int iters = 3e6;
mt19937_64 rr(random_device{}());

ld rnd() {
    return ll(rr()) % (2 * N + 1) - N;
}

pt pp() {
    return pt{rnd(), rnd(), rnd()};
}

ld pdist(pt p, pt a, pt b) {
    if (ze((a - b).abs()))
        return (a - p).abs();
    return ((p - a) % (p - b)).abs() / (a - b).abs();
}

ld ortogonality(pt a, pt b) {
    if (ze(a.abs()) || ze(b.abs()))
        return 0;
    return a * b / a.abs() / b.abs();
}

ld testPlanesIntersection() {
    Plane P(pp(), pp(), pp());
    Plane Q(pp(), pp(), pp());
    pt p, q;
    tie(p, q) = planesIntersection(P, Q);
    if (p.x == 1e18)
        return 0;
    ld res = 0;
    for (auto x: {p, q}) {
        res = max<ld>(res, fabsl(P.dist(x)));
        res = max<ld>(res, fabsl(Q.dist(x)));
    }
    return res;
}

ld testProjection() {
    pt p = pp();
    pt a = pp();
    pt b = pp();
    pt q = projection(p, a, b);
    ld res = 0;
    res = max(res, pdist(q, a, b));
    res = max(res, ortogonality(p - q, b - a));
    return res;
}

ld testCommonPerpendicular() {
    pt a = pp();
    pt b = pp();
    pt c = pp();
    pt d = pp();
    pt p, q;
    tie(p, q) = commonPerpendicular(a, b, c, d);
    if (p.x == 1e18)
        return 0;
    ld res = pdist(p, a, b);
    res = max(res, pdist(q, c, d));
    res = max(res, ortogonality(p - q, a - b));
    res = max(res, ortogonality(p - q, c - d));
    return res;
}

ld worst;

#define RUN(f) \
    worst = 0;                                      \
    for (ll n: {1e1, 1e3, 1e4, 1e5, 1e6}) {         \
        N = n;                                      \
        forn (iter, iters)                          \
            worst = max(worst, f());                \
        worst = log(double(worst)) / log(10);       \
        cout << #f << ": 1e" << int(round(log(n) / log(10))) << " -> " << double(worst) << "\n";  \
    }                                               \
    cout << '\n';

void test() {
    cout << fixed;
    cout.precision(1);
    cout << "Absolute error test\n\n";

    RUN(testProjection);
    RUN(testPlanesIntersection);
    RUN(testCommonPerpendicular);
}

int main() {
    test();
}
