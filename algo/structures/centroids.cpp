#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)

//BEGIN_CODE
const int maxn = 100100;
const int LG = 18; //2*maxn <= 2^LG

vector<int> g[LG][maxn];
int rt[LG][maxn];
int from[LG][maxn];

namespace Cenroids {

int D;
int cnt[maxn];
int CENTER, BEST;

void pre(int u, int prev = -1) {
    cnt[u] = 1;
    for (int v: g[D][u]) {
        if (v == prev)
            continue;
        pre(v, u);
        cnt[u] += cnt[v];
    }
}

void findCenter(int u, int prev = -1, int up = 0) {
    int worst = up;
    for (int v: g[D][u]) {
        if (v == prev)
            continue;
        findCenter(v, u, up + cnt[u] - cnt[v]);
        worst = max(worst, cnt[v]);
    }
    if (worst < BEST) {
        CENTER = u;
        BEST = worst;
    }
}

void markAll(int u, int prev = -1, int subtree = -1) {
    rt[D][u] = CENTER;
    from[D][u] = subtree;
    for (int v: g[D][u]) {
        if (v == prev)
            continue;
        g[D + 1][u].push_back(v);
        g[D + 1][v].push_back(u);
        if (subtree == -1)
            markAll(v, u, v);
        else
            markAll(v, u, subtree);
    }
}

void decompose(int u, int depth = 0) {
    D = depth;
    pre(u);
    CENTER = -1, BEST = 1e9;
    findCenter(u);
    assert(CENTER != -1);
    u = CENTER;
    markAll(u);
    D = depth + 1;
    for (int v: g[D][u]) {
        auto it = find(g[D][v].begin(), g[D][v].end(), u);
        assert(it != g[D][v].end());
        g[D][v].erase(it);
    }
    for (int v: g[D][u])
        decompose(v, depth + 1);
}

};
//END_CODE

int main() {
    #ifdef LOCAL
    assert(freopen("centroids.in", "r", stdin));
    #else
    #endif
    int n;
    cin >> n;
    forn (i, n - 1) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[0][u].push_back(v);
        g[0][v].push_back(u);
    }
    Cenroids::decompose(0);
}
