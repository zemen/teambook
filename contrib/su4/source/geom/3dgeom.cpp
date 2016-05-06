#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <string>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <queue>

using namespace std;

#define FOR(a, b) for (int a = 0; a < (b); ++a)
#define clr(a) memset(a, 0, sizeof(a))
#define pb(i) push_back(i)
#define forab(i, a, b) for(int i = int(a); i < int(b); ++i)
#define forba(i, b, a) for(int i = int(b) - 1; i >= int(a); --i)
#define forn(i, n) forab(i, 0, n)
#ifdef LOCAL
#define debug(a) cerr << #a << ": " << a << '\n';
#else
#define debug(a)
#endif

typedef long long ll;
typedef long double ldb;


//BEGIN ALGO
const int INF = 1e9;
const ldb EPS = 1e-8;
const ldb PI = acos(-1.0);
const int MAXN = 1e5;

bool eq(ldb a, ldb b) {
    return abs(a - b) < EPS;
}

ldb sqr(ldb x) {
    return x * x;
}

int sign(ldb x) {
    if (eq(x, 0))
        return 0;
    if (x > 0)
        return 1;
    else
        return -1;
}

struct point {
    ldb x, y, z;
    point() : x(0), y(0), z(0) {}
    point (ldb x, ldb y, ldb z) : x(x), y(y), z(z) {}
    bool operator == (const point & p) const {
        return (eq(x, p.x) && eq(y, p.y) && eq(z, p.z));
    }
    ldb len() const {
        return sqrt(x * x + y * y + z * z);
    }
    ldb len2() const {
        return x * x + y * y + z * z;
    }
    point operator + (const point & o) const {
        return point(x + o.x, y + o.y, z + o.z);
    }
    point operator - (const point & o) const {
        return point(x - o.x, y - o.y, z - o.z);
    }
    ldb operator * (const point & o) const {
        return x * o.x + y * o.y + z * o.z;
    }
    point operator % (const point & o) const {
        return point(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }
    point operator * (ldb d) const {
        return point(x * d, y * d, z * d);
    }
    //absolute value!
    ldb angleTo(const point & o) const {
        return atan2(((*this) % o).len(), (*this) * o);
    }
    ldb distTo(const point & o) const {
        return ((*this) - o).len();
    }
    point norm(ldb l = 1.0) {
        return (*this) * (l / len());
    }
    void read() {
        double dx, dy, dz;
        cin >> dx >> dy >> dz;
        x = dx, y = dy, z = dz;
    }
    void print() const{
        cerr << x << ' ' << y << ' ' << z << '\n';
    }
};
const point INFP(INF, INF, INF);

struct line {
    point s, v;
    line() : s(), v() {}
    line(point a, point b) : s(a), v(b - a) {}
    bool operator == (const line & o) const {
        return (v % o.v).len() < EPS && (v % (s - o.s)).len() < EPS;
    }
    //non-oriented distance
    ldb distTo(const point & p) const {
        return ((p - s) % v).len() / v.len();
    }
    bool on(const point & p) const {
        return ((p - s) % v).len() < EPS;
    }
    point intersect(const line & o) {
        if ((v % o.v).len() < EPS) {
            if ((*this) == o)
                return s;
            else
                return INFP;
        }
        point n = v % o.v;
        point p = o.s - s;
        if (sign(n * p) != 0) {
            return INFP;
        }
        ldb t;
        if (sign(n.x) != 0) {
            t = (p.y * o.v.z - p.z * o.v.y) / n.x;
        } else if (sign(n.y) != 0) {
            t = (p.z * o.v.x - p.x * o.v.z) / n.y;
        } else if (sign(n.z) != 0) {
            t = (p.x * o.v.y - p.y * o.v.x) / n.z;
        }
        point res = s + v * t;
        assert(on(res) && o.on(res));
        return res;
    }
    //returns perpendicular direction, so that p + (return value) lies on the line
    point perpTo(const point & p) {
        point n = (p - s) % v;
        ldb d = distTo(p);
        point pr = n % v;
        point res = pr.norm(d);
        assert(on(p + res));
        return res;
    }
    ldb distTo(const line & o) const {
        point up = s - o.s;
        up = up - v * ((v * up) / v.len2());
        point ort = o.v - v * (v * o.v / v.len2());
        if (sign(ort.len2()) != 0) {
            up = up - ort * (ort * up / ort.len2());
        }
        assert(sign(up * v) == 0);
        assert(sign(up * ort) == 0);
        assert(sign(up * o.v) == 0);
        return up.len();
    }
};
void closest(const line & l1, const line & l2, point & p1, point & p2) {
    if ((l1.v % l2.v).len() < EPS) {
        p1 = l1.s;
        p2 = l2.s - l1.v * (l1.v * (l2.s - l1.s) / l1.v.len2());
    } else {
        point p = l2.s - l1.s;
        ldb t1 = (l1.v * p * l2.v.len2() - l1.v * l2.v * (l2.v * p)) / (l1.v % l2.v).len2();
        ldb t2 = (-(l2.v * p * l1.v.len2()) + l1.v * l2.v * (l1.v * p)) / (l2.v % l1.v).len2();
        p1 = l1.s + l1.v * t1;
        p2 = l2.s + l2.v * t2;
    }
    assert(l1.on(p1));
    assert(l2.on(p2));
}

struct plane {
    point p, n;
    plane() : p(), n() {}
    plane(point p, point n) : p(p), n(n) {}
    plane(point a, point b, point c) {
        n = (b - a) % (c - a);
        p = a;
    }
    //-1 if under, 1 over, 0 if on
    int side(const point & x) const {
        return sign((x - p) * n);
    }
};

ldb vol(point p1, point p2, point p3) {
    return p1 * (p2 % p3);
}

point intersect(const plane & p, const line & l) {
    ldb d = p.n * l.v;
    if (sign(d) == 0) {
        if (p.side(l.s) == 0)
            return l.s;
        else
            return INFP;
    }
    ldb t = -(p.n * l.s - p.p * p.n) / d;
    point res = l.s + l.v * t;
    assert(p.side(res) == 0);
    return res;
}

point intersect(const plane & p1, const plane & p2, const plane & p3) {
    ldb d = vol(p1.n, p2.n, p3.n);
    assert(sign(d) != 0);
    point px(p1.n.x, p2.n.x, p3.n.x);
    point py(p1.n.y, p2.n.y, p3.n.y);
    point pz(p1.n.z, p2.n.z, p3.n.z);
    point p((p1.n * p1.p), (p2.n * p2.p), (p3.n * p3.p));
    point res(vol(p, py, pz) / d, vol(px, p, pz) / d, vol(px, py, p) / d);
    assert(p1.side(res) == 0);
    assert(p2.side(res) == 0);
    assert(p3.side(res) == 0);
    return res;
}

line intersect(const plane & p1, const plane &p2) {
    line res;
    res.v = p1.n % p2.n;
    plane p3;
    p3.n = res.v;
    res.s = intersect(p1, p2, p3);
    assert(p1.side(res.s) == 0);
    assert(p2.side(res.s) == 0);
}
//END ALGO
int main() {
    return 0;
}

