#include <bits/stdc++.h>
using namespace std;
#define forn(i,n) for (int i = 0; i < int(n); ++i)
const int inf = 1e9 + 1e5;

// left half is the smaller one
namespace Hungary {
    const int maxn = 505;
    int a[maxn][maxn];
    int p[2][maxn];
    int match[maxn];
    bool used[maxn];
    int from[maxn];
    int mind[maxn];
    int n, m;

    int hungary(int v) {
        used[v] = true;
        int u = match[v];
        int best = -1;
        forn (i, m + 1) {
            if (used[i])
                continue;
            int nw = a[u][i] - p[0][u] - p[1][i];
            if (nw <= mind[i]) {
                mind[i] = nw;
                from[i] = v;
            }
            if (best == -1 || mind[best] > mind[i])
                best = i;
        }
        v = best;
        int delta = mind[best];
        forn (i, m + 1) {
            if (used[i]) {
                p[1][i] -= delta;
                p[0][match[i]] += delta;
            } else
                mind[i] -= delta;
        }
        if (match[v] == -1)
            return v;
        return hungary(v);
    }

    void check() {
        int edges = 0, res = 0;
        forn (i, m)
            if (match[i] != -1) {
                ++edges;
                assert(p[0][match[i]] + p[1][i] == a[match[i]][i]);
                res += a[match[i]][i];
            } else
                assert(p[1][i] == 0);
        assert(res == -p[1][m]);
        forn (i, n) forn (j, m)
            assert(p[0][i] + p[1][j] <= a[i][j]);
    }
    
    int run() {
        forn (i, n)
            p[0][i] = 0;
        forn (i, m + 1) {
            p[1][i] = 0;
            match[i] = -1;
        }
        forn (i, n) {
            match[m] = i;
            fill(used, used + m + 1, false);
            fill(mind, mind + m + 1, inf);
            fill(from, from + m + 1, -1);
            int v = hungary(m);
            while (v != m) {
                int w = from[v];
                match[v] = match[w];
                v = w;
            }
        }
        check();
        return -p[1][m];
    }
};

int main() {
    int n = 300, m = 500;
    Hungary::n = n, Hungary::m = m;
    forn (i, n) forn (j, m) Hungary::a[i][j] = rand() % 200001 - 100000;
    cerr << Hungary::run() << "\n";
}
