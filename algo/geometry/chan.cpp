// This implementation is unstable for precision errors

#include <bits/stdc++.h>
using namespace std;
#define forn(i,n) for (int i = 0; i < int(n); ++i)
#define all(x) x.begin(), x.end()
typedef long double ld;

const int maxn = 100100;
const ld eps = 1e-9;

mt19937 rr(111);
ld rndEps() {
    return (ld(rr()) / rr.max() - 0.5) / 1e5;
}

bool gt(ld a, ld b) { return a - b > eps; }
bool lt(ld a, ld b) { return b - a > eps; }
bool eq(ld a, ld b) { return fabsl(a - b) < eps; }

struct pt {
    ld x, y, z;
    ld ox, oy, oz;
    int pr, nx;
    bool inHull;

    pt() {}

    pt(ld x, ld y, ld z): x(x), y(y), z(z) {}

    pt operator-(const pt &p) const {
        return pt(x - p.x, y - p.y, z - p.z);
    }

    ld operator*(const pt &p) const {
        return x * p.x + y * p.y + z * p.z;
    }

    pt operator%(const pt &p) const {
        return pt(y * p.z - z * p.y,
                  z * p.x - x * p.z,
                  x * p.y - y * p.x);
    }
    
    bool operator==(const pt &a) {
        return eq(x, a.x) && eq(y, a.y) && eq(z, a.z);
    }

    void transform(bool rev) {
        if (rev) {
            x = ox, y = oy, z = oz;
        } else {
            ox = x, oy = y, oz = z;
            x += rndEps(), y += rndEps(), z += rndEps();
        }
    }
};

ostream &operator<<(ostream &out, pt &p) {
    return out << p.x << ' ' << p.y << ' ' << p.z;
}

istream &operator>>(istream &in, pt &p) {
    return in >> p.x >> p.y >> p.z;
}

//BEGIN_CODE
typedef tuple<int, int, int> Facet;

namespace Chan {
int n;
pt p[maxn];

ld turn(int p1, int p2, int p3) {
    assert(p1 != -1 && p2 != -1 && p3 != -1);
    return (p[p2].x - p[p1].x) * (p[p3].y - p[p1].y) - 
        (p[p3].x - p[p1].x) * (p[p2].y - p[p1].y);
}

//replace y with z
ld turnz(int p1, int p2, int p3) {
    assert(p1 != -1 && p2 != -1 && p3 != -1);
    return (p[p2].x - p[p1].x) * (p[p3].z - p[p1].z) - 
        (p[p3].x - p[p1].x) * (p[p2].z - p[p1].z);
}

ld gett(int p1, int p2, int p3) {
    return turnz(p1, p2, p3) / turn(p1, p2, p3);
}

void act(int i) {
    if (p[i].inHull) {
        p[p[i].nx].pr = p[i].pr;
        p[p[i].pr].nx = p[i].nx;
    } else {
        p[p[i].nx].pr = p[p[i].pr].nx = i;
    }
    p[i].inHull ^= 1;
}

vector<int> buildHull(int l, int r, bool upper) {
    if (l + 1 >= r) {
        p[l].pr = p[l].nx = -1;
        p[l].inHull = true;
        return {};
    }
    int mid = (l + r) / 2;
    auto L = buildHull(l, mid, upper);
    auto R = buildHull(mid, r, upper);
    reverse(all(L));
    reverse(all(R));
    int u = mid - 1, v = mid;
    while (true) {
        if (p[u].pr != -1 && 
                ((turn(p[u].pr, u, v) < 0) ^ upper))
            u = p[u].pr;
        else if (p[v].nx != -1 && 
                ((turn(u, v, p[v].nx) < 0) ^ upper))
            v = p[v].nx;
        else
            break;
    }

    ld T = -1e100;
    ld t[6];
    vector<int> A;
    while (true) {
        forn (i, 6)
            t[i] = 1e100;
        if (!L.empty()) {
            int id = L.back();
            t[0] = gett(p[id].pr, id, p[id].nx);
        }
        if (!R.empty()) {
            int id = R.back();
            t[1] = gett(p[id].pr, id, p[id].nx);
        }
        if (p[u].pr != -1)
            t[2] = gett(p[u].pr, u, v);
        if (p[u].nx != -1)
            t[3] = gett(u, p[u].nx, v);
        if (p[v].pr != -1)
            t[4] = gett(u, p[v].pr, v);
        if (p[v].nx != -1)
            t[5] = gett(u, v, p[v].nx);
        ld nt = 1e100;
        int type = -1;
        forn (i, 6)
            if ((t[i] - T >= 1e-15) && t[i] < nt)
                nt = t[i], type = i;
        if (type == -1)
            break;

        if (type == 0) {
            act(L.back());
            if (L.back() < u)
                A.push_back(L.back());
            L.pop_back();
        } else if (type == 1) {
            act(R.back());
            if (R.back() > v)
                A.push_back(R.back());
            R.pop_back();
        } else if (type == 2) {
            A.push_back(u);
            u = p[u].pr;
        } else if (type == 3) {
            u = p[u].nx;
            A.push_back(u);
        } else if (type == 4) {
            v = p[v].pr;
            A.push_back(v);
        } else if (type == 5) {
            A.push_back(v);
            v = p[v].nx;
        } else 
            assert(false);
        T = nt;
    }
    assert(L.empty() && R.empty());

    p[u].nx = v, p[v].pr = u;
    for (int i = u + 1; i < v; ++i)
        p[i].inHull = false;
    for (int i = int(A.size()) - 1; i >= 0; --i) {
        int id = A[i];
        if (id <= u || id >= v) {
            if (u == id)
                u = p[u].pr;
            if (v == id)
                v = p[v].nx;
            act(id);
        } else {
            p[id].pr = u, p[id].nx = v;
            act(id);
            if (id >= mid)
                v = id;
            else
                u = id;
        }
    }

    return A;
}

//facets are oriented ccw if look from the outside
vector<Facet> getFacets() {
    forn (i, n)
        p[i].transform(false);
    //WARNING: original order of points is changed
    sort(p, p + n, [](const pt &a, const pt &b) {
                return a.x < b.x;
            });

    vector<Facet> facets;
    forn (q, 2) {
        auto movie = buildHull(0, n, q);
        for (auto x: movie) {
            if (!p[x].inHull)
                facets.emplace_back(p[x].pr, x, p[x].nx);
            else
                facets.emplace_back(p[x].pr, p[x].nx, x);
            act(x);
        }
    }
    forn (i, n)
        p[i].transform(true);
    return facets;
}
} //namespace Chan
//END_CODE

int main() {
    int n;
    cin >> n;
    Chan::n = n;
    forn (i, n)
        cin >> Chan::p[i];
    auto facets = Chan::getFacets();
    set<int> nodes;
    for (auto f: facets) {
        nodes.insert(get<0>(f));
        nodes.insert(get<1>(f));
        nodes.insert(get<2>(f));
    }
    assert(nodes.size() * 2 == facets.size() + 4);
    ld V = 0, S = 0;
    for (auto f: facets) {
        pt v1 = Chan::p[get<1>(f)] - Chan::p[get<0>(f)];
        pt v2 = Chan::p[get<2>(f)] - Chan::p[get<0>(f)];
        pt v3 = Chan::p[get<0>(f)];
        pt vv = v1 % v2;
        forn (i, n) {
            pt v4 = Chan::p[i] - Chan::p[get<0>(f)];
            assert(v4 * vv < 0.1);
        }
        S += sqrtl(vv.x * vv.x + vv.y * vv.y + vv.z * vv.z) / 2;
        V += vv * v3 / 6;
    }
    cout.precision(10);
    cout << fixed;
    cout << S << ' ' << V << '\n';
}
