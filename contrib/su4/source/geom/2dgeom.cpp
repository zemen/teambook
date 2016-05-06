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

typedef long long ll;
typedef long double ldb;


//BEGIN ALGO
const ldb INF = 1e11;
const ldb EPS = 1e-8;
const ldb PI = acos(-1.0);
const int MAXN = 1e5 + 100;

bool eq(ldb a, ldb b) {
    return abs(a - b) < EPS;
}

ldb sqr(ldb x) {
    return x * x;
}

ldb sign(ldb x) {
    if (eq(x, 0))
        return 0;
    if (x > 0)
        return 1;
    else
        return -1;
}

struct point {
    ldb x, y;
    point() : x(0), y(0) {}
    point (ldb x, ldb y) : x(x), y(y) {}
    bool operator == (const point & p) const {
        return (eq(x, p.x) && eq(y, p.y));
    }
    ldb len() const {
        return sqrt(x * x + y * y);
    }
    point operator + (const point & o) const {
        return point(x + o.x, y + o.y);
    }
    point operator - (const point & o) const {
        return point(x - o.x, y - o.y);
    }
    ldb operator * (const point & o) const {
        return x * o.x + y * o.y;
    }
    ldb operator % (const point & o) const {
        return x * o.y - y * o.x;
    }
    point operator * (ldb d) const {
        return point(x * d, y * d);
    }
    //counter-clockwise rotations
    //by PI/2
    point rotate() const {
        return point(-y, x);
    }
    point rotate(ldb a) const {
        return point(cos(a) * x - sin(a) * y, cos(a) * y + sin(a) * x);
    }
    //positive if o is in counter-clockwise direction
    ldb angleTo(const point & o) const {
        return atan2((*this) % o, (*this) * o);
    }
    ldb distTo(const point & o) const {
        return ((*this) - o).len();
    }
    point norm(ldb l = 1.0) {
        return (*this) * (l / len());
    }
    void read() {
        double dx, dy;
        cin >> dx >> dy;
        x = dx, y = dy;
    }
    void print() const{
        cerr << x << ' ' << y << '\n';
    }
};
const point INFP(INF, INF);

struct line {
    point s, v;
    line() : s(), v() {}
    line(point a, point b) : s(a), v(b - a) {}
    bool operator == (const line & o) const {
        return abs(v % o.v) < EPS && abs(v % (s - o.s)) < EPS;
    }
    line(ldb a, ldb b, ldb c) {
        v = point(a, b).rotate();
        if (abs(b) > EPS) {
            s = point(0, -c / b);
        } else{
            s = point(-c / a, 0);
        }
    }
    //oriented distance, positive if to the right of v
    ldb distTo(const point & p) const {
        return (p - s) % v / v.len();
    }
    point intersect(const line & o) {
        if (abs(v % o.v) < EPS) {
            if ((*this) == o)
                return s;
            else
                return INFP;
        }
        ldb t = (v % (s - o.s)) / (v % o.v);
        return o.s + o.v * t;
    }
    //returns perpendicular direction, so that p + (return value) lies on the line
    point perpTo(const point & p) {
        ldb d = distTo(p);
        return (v.rotate() * sign(d)).norm(abs(d));
    }
    //-1 if to the right, 1 if to the left, 0 if on
    int side(const point & p) const {
        if (abs((p - s) % v) < EPS)
            return 0;
        if ((p - s) % v > 0)
            return -1;
        return 1;
    }
};

struct distComp {
    point o;
    distComp() : o() {}
    distComp(point o) : o(o) {}
    bool operator ()(const point & a, const point & b) const {
        return a.distTo(o) < b.distTo(o);
    }
};

struct lowerLeftComp {
    bool operator () (const point & a, const point & b) const {
        if (!eq(a.y, b.y))
            return a.y < b.y;
        return a.x < b.x;
    }
};

struct angleComp {
    point o;
    angleComp() : o() {}
    angleComp(point o) : o(o) {}
    bool operator ()(const point & a, const point & b) const {
        if (abs((a - o) % (b - o)) > EPS) {
            return ((a - o) % (b - o)) > 0;
        }
        return a.distTo(o) < b.distTo(o);
    }
};

struct lineComp {
    bool operator() (const line & a, const line & b) const {
        point zero(1.0, PI);
        /*
        a.v.print();
        b.v.print();
        cerr << abs(a.v % b.v) << '\n' << '\n';*/
        if (abs(a.v % b.v) > EPS || a.v * b.v < -EPS) {
            return a.v.angleTo(zero) > b.v.angleTo(zero);
        }
        if (a == b)
            return false;
        return (b.s - a.s) % a.v > 0;
    }
};

//distance form o to [a, b]
ldb distToSeg(point o, point a, point b) {
    ldb res = min(o.distTo(a), o.distTo(b));

    if (((b - a)*(o - a) > -EPS) && ((a - b) * (o - b) > -EPS)) {
        res = min(res, abs(line(a, b).distTo(o)));
    }
    return res;
}

ldb distToCircle(point p, point o, ldb r) {
    return p.distTo(o) - r;
}

//checks fo intersection of [a, b] and [c, d]
bool hasIntersection(point a, point b, point c, point d) {
    point v1 = b - a;
    point v2 = d - c;
    if (((c - a) % v1) * ((d - a) % v1) > EPS)
        return false;
    if (((a - c) % v2) * ((b - c) % v2) > EPS)
        return false;
    return true;
}

vector<point> intersectSegments(point a, point b, point c, point d) {
    vector<point> res;
    if (!hasIntersection(a, b, c, d)) {
        return res;
    }
    line l1(a, b);
    line l2(c, d);
    if (!(l1 == l2)) {
        res.pb(l1.intersect(l2));
        return res;
    }
    vector <point> p = {a, b, c, d};
    sort(p.begin(), p.end(), distComp(a));
    return vector<point>{p[1], p[2]};
}

vector<point> intersectLineAndCircle(line l, point o, ldb r) {
    vector<point> res;
    ldb d = abs(l.distTo(o));
    if (d > r + EPS)
        return res;
    point p = l.perpTo(o);
    ldb a = acos(p.len() / r);
    p = p.norm(r);
    res.pb(o + p.rotate(a));
    if (abs(a) > EPS) {
        res.pb(o + p.rotate(-a));
    }
    return res;
}

vector<point> intersectCircles(point o1, ldb r1, point o2, ldb r2) {
    vector<point> res;
    if (o1.distTo(o2) > r1 + r2) {
        return res;
    }
    point d = o2 - o1;
    ldb a = acos((sqr(d.len()) + sqr(r1) - sqr(r2)) / (2 * r1 * d.len()));
    d = d.norm(r1);
    res.pb(o1 + d.rotate(a));
    if (abs(a) > EPS)
        res.pb(o1 + d.rotate(-a));
    return res;
}

//median centroid of a triangle (== mass centroid)
point median(point a, point b, point c) {
    return point((a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3);
}

//mass centroid of an arbitrary polygon (assumes p[n] == p[0])
point massCentroid(point * p, int n) {
    point o;
    ldb s = 0;
    point c;
    FOR(i, n) {
        ldb cs = p[i] % p[i + 1] / 2;
        c = c + median(o, p[i], p[i + 1]) * cs;
        s += cs;
    }
    c = c * (1 / s);
    return c;
}

vector<line> pointTangents(point p, point o, ldb r) {
    ldb d = p.distTo(o);
    ldb a = acos(r / d);
    point v = (p - o).norm(r);
    vector<line> res;
    res.pb(line(p, o + v.rotate(a)));
    res.pb(line(p, o + v.rotate(-a)));
    return res;
}

vector<line> commonTangents(point o1, ldb r1, point o2, ldb r2) {
    vector<line> res;
    point v = (o2 - o1);
    point w = v.rotate(PI/2 + asin(abs(r2 - r1) / v.len()));
    res.pb(line(o1 + w.norm(r1), o2 + w.norm(r2)));
    w = v.rotate(-PI/2 - asin(abs(r2 - r1) / v.len()));
    res.pb(line(o1 + w.norm(r1), o2 + w.norm(r2)));
    
    if (o1.distTo(o2) < r1 + r2 - EPS)
        return res;
    ldb a = acos((r1 + r2) / o1.distTo(o2));
    res.pb(line(o1 + (o2 - o1).rotate(a).norm(r1), o2 + (o1 - o2).rotate(-a).norm(r2)));
    res.pb(line(o1 + (o2 - o1).rotate(-a).norm(r1), o2 + (o1 - o2).rotate(a).norm(r2)));
    return res;
}

//return symmetric to point p with respect to line l
point symmetric(point p, line l) {
    return p + l.perpTo(p) * 2;
}

point p[MAXN];

vector<point> convexHull(point * p, int n) {
    lowerLeftComp comp;
    int mn = 0;
    FOR(i, n) {
        if (comp(p[i], p[mn]))
            mn = i;
    }
    swap(p[0], p[mn]);
    angleComp acomp(p[0]);
    sort(p + 1, p + n, acomp);
    vector<point> h;
    FOR(i, n) {
        while (h.size() >= 2 && ((p[i] - h[h.size() - 1]) %  (h[h.size() - 1] - h[h.size() - 2]) > -EPS))
            h.pop_back();
        h.pb(p[i]);
    }
    return h;
}

//assume polygon is counterclockwise-ordered
bool contains(point * p, int n, point q) {
    point o = p[0];
    if (((q - o) % (p[1] - o)) >EPS || ((q - o) % (p[n - 1] - o)) < -EPS)
        return false;
    int l = 0, r = n - 1;
    while (l < r - 1) {
        int m = (l + r) / 2;
        if ((q - o) % (p[m] - o) > EPS)
            r = m;
        else
            l = m;
    }
    point x = p[l];
    point y = p[r];
    return ((q - x) % (y - x)) < EPS;
}

vector<point> halfplaneIntersect(vector<line> h) {
    vector<point> box;
    box.pb(point(INF, -INF));
    box.pb(point(INF, INF));
    box.pb(point(-INF, INF));
    box.pb(point(-INF, -INF));
    FOR(i, 4) {
        h.pb(line(box[i], box[(i + 1) % 4]));
    }
    sort(h.begin(), h.end(), lineComp());
    int m = 0;
    FOR(i, h.size()) {
        if (i == 0 || abs(h[i].v % h[i - 1].v) > EPS)
            h[m++] = h[i];
    }
    h.resize(m);
    vector<point> p;
    vector<line> l;
    l.pb(h[0]);
    int del = 0;
    for (int i = 1; i < h.size(); ++i) {
        while (p.size() > del && h[i].side(p[p.size() - 1]) <= 0) {
            p.erase(p.end() - 1);
            l.erase(l.end() - 1);
        }
        if (del == p.size()) {
            if (l[l.size() - 1].v % h[i].v < EPS)
                return vector<point>();
        }
        while (p.size() > del && h[i].side(p[del]) <= 0)
            ++del;
        point np = h[i].intersect(l[l.size() - 1]);
        if (l[del].side(np) >= 0) {
            p.pb(np);
            l.pb(h[i]);
        }
    }
    p.erase(p.begin(), p.begin() + del);
    l.erase(l.begin(), l.begin() + del);
    if (l.size() <= 1)
        return p;
    p.pb(l[0].intersect(l[l.size() - 1]));
    return p;
}
//END ALGO
int main() {
    return 0;
}

