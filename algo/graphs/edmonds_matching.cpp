#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
const int maxn = 505;
typedef vector<int> vi;

// BEGIN_CODE
int n;
vi e[maxn];
int mt[maxn], p[maxn], base[maxn], b[maxn], blos[maxn];
int q[maxn];
int blca[maxn]; // used for lca

int lca(int u, int v) {
    forn(i, n) blca[i] = 0;
    while (true) {
        u = base[u];
        blca[u] = 1;
        if (mt[u] == -1) break;
        u = p[mt[u]];
    }
    while (!blca[base[v]]) {
        v = p[mt[base[v]]];
    }
    return base[v];
}

void mark_path(int v, int b, int ch) {
    while (base[v] != b) {
        blos[base[v]] = blos[base[mt[v]]] = 1;
        p[v] = ch;
        ch = mt[v];
        v = p[mt[v]];
    }
}

int find_path(int root) {
    forn(i, n) {
        base[i] = i;
        p[i] = -1;
        b[i] = 0;
    }

    b[root] = 1;
    q[0] = root;
    int lq = 0, rq = 1;
    while (lq != rq) {
        int v = q[lq++];
        for (int to: e[v]) {
            if (base[v] == base[to] || mt[v] == to) continue;
            if (to==root || (mt[to] != -1 && p[mt[to]] != -1)) {
                int curbase = lca(v, to);
                forn(i, n) blos[i] = 0;
                mark_path(v, curbase, to);
                mark_path(to, curbase, v);
                forn(i, n) if (blos[base[i]]) {
                    base[i] = curbase;
                    if (!b[i]) b[i] = 1, q[rq++] = i;
                }
            } else if (p[to] == -1) {
                p[to] = v;
                if (mt[to] == -1) {
                    return to;
                }
                to = mt[to];
                b[to] = 1;
                q[rq++] = to;

            }
        }
    }
    return -1;
}

int matching() {
    forn(i, n) mt[i] = -1;
    int res = 0;
    forn(i, n) if (mt[i] == -1) {
        int v = find_path(i);
        if (v != -1) {
            ++res;
            while (v != -1) {
                int pv = p[v], ppv = mt[p[v]];
                mt[v] = pv, mt[pv] = v;
                v = ppv;
            }
        }
    }
    return res;
}
// END_CODE

int a[20][20];
int d[1<<20];
int mts() {
    forn(v, n) for (int to: e[v]) a[v][to] = 1;
    d[0] = 1;
    int res = 0;
    forn(mask, 1<<n) if (d[mask]) {
        res = max(res, __builtin_popcount(mask));
        forn(i, n) if (!(mask&(1<<i))) {
            forn(j, n) if (!(mask&(1<<j))) {
                if (a[i][j]) d[mask^(1<<i)^(1<<j)] = 1;
            }
        }
    }
    return res/2;
}

int main() {
    freopen("input.txt", "r", stdin);
    int m;
    cin >> n >> m;
    forn(i, m) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    int res = matching();
//     int stup = mts();
//     cerr << "stupid: " << stup << endl;
//     assert(res == stup);
    cout << res << endl;
//     forn(i, n) if (mt[i] > i) {
//         cout << i << " " << mt[i] << endl;
//     }
}
