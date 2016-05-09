#include <bits/stdc++.h>
using namespace std;
#define forn(i,n) for (int i = 0; i < int(n); ++i)
typedef long double ld;

const int maxn = 100100;
const ld eps = 1e-9;

mt19937 rr(111);
ld rndEps() {
    return (ld(rr()) / rr.max() - 0.5) / 1e6;
}

bool gt(ld a, ld b) { return a - b > eps; }
bool lt(ld a, ld b) { return b - a > eps; }

//BEGIN_CODE
struct pt {
    ld x, y, z;
    ld ox, oy, oz;
    int pr, nx;
    bool inHull;

    static pt *NIL;

    pt() {}

    pt(ld x, ld y, ld z): x(x), y(y), z(z) {}

    void transform(bool rev) {
        if (rev) {
            x = ox, y = oy, z = oz;
        } else {
            ox = x, oy = y, oz = z;
            x += rndEps(), y += rndEps(), z += rndEps();
        }
    }
};
//END_CODE

ostream &operator<<(ostream &out, pt &p) {
    return out << p.x << ' ' << p.y << ' ' << p.z;
}

istream &operator>>(istream &in, pt &p) {
    return in >> p.x >> p.y >> p.z;
}

typedef tuple<int, int, int> Facet;

//BEGIN_CODE
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
    reverse(L.begin(), L.end());
    reverse(R.begin(), R.end());
    int u = l, v = r - 1;
    while (true) {
        if (p[u].nx!=-1 && ((turn(u, p[u].nx, v)>0)^upper))
            u = p[u].nx;
        else if (p[v].pr!=-1 && ((turn(u, p[v].pr, v)>0)^upper))
            v = p[v].pr;
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
            if (gt(t[i], T) && t[i] < nt)
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
    cerr << facets.size() << " facets" << '\n';
    cerr << "vertices:\n";
    forn (i, n)
        cerr << Chan::p[i] << '\n';
    cerr << "facets:\n";
    for (auto f: facets)
        cerr << get<0>(f) << ' ' << get<1>(f) << ' ' << get<2>(f) << '\n';
}
