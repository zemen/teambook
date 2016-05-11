// submitted to WF2014::L
// NO TEAMBOOK
#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define fore(i, b, e) for (int i = (int)(b); i <= (int)(e); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long i64;
typedef unsigned long long u64;
typedef __float128 ld;

const ld eps = 1e-12;

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

istream &operator>>(istream &in, pt &p) {
    double a, b;
    in >> a >> b;
    p = {a, b};
    return in;
}
// ostream &operator<<(ostream &out, const pt &p) { return out << p.x << ' ' << p.y; }

bool pointInsideSegment(pt p, pt a, pt b) {
    if (!eq((p - a) % (p - b), 0))
        return false;
    return ge(0, (a - p) * (b - p));
}

bool checkSegmentIntersection(pt a, pt b, pt c, pt d) {
    if (eq((a - b) % (c - d), 0)) {
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

pair<bool, pt> segmentsIntersection(pt a, pt b, pt c, pt d) {
    if (!checkSegmentIntersection(a, b, c, d) ||
            eq(0, (b-a) % (c-d))) {
        return {false, {0,0}};
    }
    ld S = (b - a) % (d - c);
    ld s1 = (c - a) % (d - a);
    return {1, a + (b - a) / S * s1};
}

bool pointInsidePolygon(pt a, pt *p, int n) {
    double sumAng = 0;
    forn (i, n) {
        pt A = p[i], B = p[(i + 1) % n];
        if (pointInsideSegment(a, A, B))
            return true;
        sumAng += atan2l((A - a) % (B - a), (A - a) * (B - a));
    }
    return fabs(sumAng) > 1;
}

struct SVG {
    FILE *out;
    ld sc = 1;

    SVG() { open(); }
    void open() {
        out = fopen("image.svg", "w");
        fprintf(out, "<svg xmlns='http://www.w3.org/2000/svg' viewBox='-1000 -1000 2000 2000'>\n");
    }

    void line(pt a, pt b) {
//         a = a - pt{25, 25};
//         b = b - pt{25, 25};
        a = a * sc, b = b * sc;
        fprintf(out, "<line x1='%Lf' y1='%Lf' x2='%Lf' y2='%Lf'\
        stroke-width='10' stroke='black'/>\n", a.x, -a.y, b.x, -b.y);
    }

    void point(pt a, ld r = -1, string col = "red") {
//         a = a - pt{25, 25};
        r = (r == -1 ? 22 : sc * r);
        a = a * sc;
        fprintf(out, "<circle cx='%Lf' cy='%Lf' r='%Lf' fill='%s'/>\n", a.x, -a.y, r, col.c_str());
    }

    void text(pt a, string s) {
        a = a * sc;
        fprintf(out, "<text x='%Lf' y='%Lf' font-size='10px'>%s</text>\n", a.x, -a.y, s.c_str());
    }

    void close() {
        fprintf(out, "</svg>\n");
        fclose(out);
        out = 0;
    }

    ~SVG() {
        if (out)
            close();
    }
} svg;

const int maxn = 100500;

// BEGIN_CODE
int m, n; // segs, points
pair<pt, pt> segs[maxn];
pt p[maxn], from, to;
map<pt, int> shr;
vi e[maxn]; // points adjacent to point
int getPoint(pt x) {
    if (shr.count(x)) return shr[x];
    p[n] = x;
    return shr[x] = n++;
}
// END_CODE

void scan() {
    cin >> m >> from >> to;
    forn(i, m) cin >> segs[i].fi >> segs[i].se;
}
// BEGIN_CODE
// segIntersection: {bool, point}, true iff exactly one point
void genIntersections() {
    forn(i, m) {
        getPoint(segs[i].fi);
        getPoint(segs[i].se);
        forn(j, i) {
            auto t = segmentsIntersection(
                segs[i].fi, segs[i].se, segs[j].fi, segs[j].se);
            if (t.fi) getPoint(t.se);
        }
    }
    // END_CODE
//     cerr << m << " segments, " << n << " points" << endl;
    forn(i, m) svg.line(segs[i].fi, segs[i].se);
//     forn(i, n) svg.point(p[i]);
    // BEGIN_CODE
}

set<pii> zero;
set<pii> zerofe;


void genGraph() {
    forn(i, m) {
        vi pts;
        forn(j, n) if (pointInsideSegment(
                    p[j], segs[i].fi, segs[i].se)) {
            pts.push_back(j);
        }
        sort(all(pts), [](int i, int j) {
            return p[i] < p[j]; });
        forn(j, pts.size() - 1) {
            int u = pts[j], v = pts[j+1];
            e[u].push_back(v);
            e[v].push_back(u);
            if (i+1 == m) {
                zero.emplace(u, v);
                zero.emplace(v, u);
            }
        }
    }
    forn(i, n) {
        sort(all(e[i]), [i](int x, int y) {
            pt a = p[x] - p[i];
            pt b = p[y] - p[i];
            if (a.right() != b.right()) return a.right();
            return a % b > 0;
        });
    }
}

vector<pt> faces[maxn];
bool inner[maxn];
int nf;
map<pii, int> faceForEdge;
vi ef[maxn]; // graph on faces

void genFaces() {
    forn(i, n) for (int to: e[i]) {
        if (faceForEdge.count({i, to})) continue;
        int f = nf++;
        int v = i, u = to;
        do {
            faces[f].push_back(p[v]);
            faceForEdge[{v, u}] = f;
            auto it = lower_bound(all(e[u]), v,
                [u] (int x, int y) {
                    pt a = p[x] - p[u];
                    pt b = p[y] - p[u];
                    if (a.right()!=b.right()) return a.right();
                    return a % b > 0;
            });
            assert(*it == v);
            if (it == e[u].begin()) it = e[u].end();
            v = u;
            u = *--it;
        } while (v != i || u != to);
    }
    forn(i, nf) {
        ld s = 0;
        forn(j, faces[i].size()) {
            s += faces[i][j] % faces[i][(j+1)%faces[i].size()];
        }
        inner[i] = gt(s, 0);
    }
    // END_CODE
//     cerr << nf << " faces" << endl;
//     int nInner = accumulate(inner, inner + nf, 0);
//     cerr << nInner << " inner, " << nf - nInner << " outer\n";
    // BEGIN_CODE
    forn(v, n) for (int to: e[v]) {
        int f1 = faceForEdge[{v, to}];
        int f2 = faceForEdge[{to, v}];
        if (f1 != f2) {
            ef[f1].push_back(f2);
            ef[f2].push_back(f1);
            if (zero.count({v, to})) {
                zerofe.emplace(f1, f2);
                zerofe.emplace(f2, f1);
            }
        }
    }
}
// END_CODE

int locate(pt p) {
    forn(i, nf) if (inner[i]) {
        if (pointInsidePolygon(
                p, faces[i].data(), faces[i].size())) {
            return i;
        }
    }
    return -1;
}

int q[maxn*2], d[maxn*2];
bool b[maxn];

int bfs(int from, int to) {
    if (nf == 0) return 0;
    forn(i, nf) d[i] = 1000000;
    int lq = maxn, rq = maxn;
    if (from != -1) {
        q[rq++] = from;
        d[from] = 0;
    } else {
        forn(i, nf) if (!inner[i]) {
            q[rq++] = i;
            d[i] = 0;
        }
    }
    while (lq != rq) {
        int v = q[lq++];
        if (b[v]) continue;
        b[v] = 1;
        for (int to: ef[v]) if (d[to] > d[v] + 1) {
            if (zerofe.count({v, to})) {
                if (d[to] > d[v]) {
                    d[to] = d[v];
                    q[--lq] = to;
                }
            } else {
                d[to] = d[v] + 1;
                q[rq++] = to;
            }
        }
    }
    if (to != -1) {
        return d[to];
    } else {
        int res = maxn;
        forn(i, nf) if (!inner[i]) res = min(res, d[i]);
        return res;
    }
}

void solve() {
    pt ab = from - to;
    pt dir = ab * (0.35 / ab.abs());
//     ab = ab * ((ab.abs() - 0.7) / ab.abs());
    segs[m++] = {from + dir, to - dir};


    genIntersections();
    genGraph();
    genFaces();
    svg.point(from, -1, "red");
    svg.point(to, -1, "blue");
    cout << bfs(locate(from), locate(to)) << endl;
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    cerr.precision(1);
    cerr << fixed;

//     svg.line({0,0},{0,50});
//     svg.line({0,0},{50,0});
//     svg.line({50,50},{0,50});
//     svg.line({50,50},{50,0});

    scan();
    solve();

#ifdef LOCAL
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
