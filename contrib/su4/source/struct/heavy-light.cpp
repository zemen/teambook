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

#define sqr(a) ((a) * (a))

typedef long long ll;
typedef long double ldb;

const int INF = 1e9;
//BEGIN ALGO
const int MAXN = 1e5 + 10;
const int MAXK = 18;

struct tree {
    vector<int> x;
    int sz;

    tree(): sz() {
        x.clear();
    }

    void build(int n) {
        sz = 1;
        while (sz < n)
            sz *= 2;

        x.assign(2 * sz, 0);
    }

    void add(int p, int val) {
        p += sz;
        x[p] += val;

        while (p > 1) {
            p /= 2;
            x[p] = max(x[2 * p], x[2 * p + 1]);
        }
    }

    int getMax(int l, int r, int v, int L, int R) {
        if (r <= L || R <= l)
            return -INF;

        if (l <= L && R <= r)
            return x[v];

        return max(getMax(l, r, 2 * v, L, (L + R) / 2), getMax(l, r, 2 * v + 1, (L + R) / 2, R));
    }

    int getMax(int l, int r) {
        return getMax(l, r, 1, 0, sz);
    }
};

int n;
vector<int> e[MAXN];

vector<tree> t;
vector<int> root;
int tsz;

int tpos[MAXN];
int tnum[MAXN];

int d[MAXN];
int sz[MAXN];
int to[MAXK][MAXN];

int dfs(int v, int pr) {
    to[0][v] = pr;

    sz[v] = 1;

    for(auto u : e[v])
        if (u != pr) {
            d[u] = d[v] + 1;
            sz[v] += dfs(u, v);
        }

    return sz[v];
}

void buildTrees(int v, int pr, int num) {
    tnum[v] = num;

    for(auto u : e[v])
        if (u != pr) {
            if (2 * sz[u] >= sz[v])
                buildTrees(u, v, num);
            else {
                t.push_back(tree());
                root.push_back(u);
                tsz++;
                buildTrees(u, v, tsz - 1);
            }
        }

    tpos[v] = t[num].sz++;
}

int getMax(int a, int b) {
    int res = -INF;
    while (tnum[a] != tnum[b]) {
        res = max(res, t[tnum[a]].getMax(tpos[a], t[tnum[a]].sz));
        a = to[0][root[tnum[a]]];
    }
    res = max(res, t[tnum[a]].getMax(tpos[a], tpos[b] + 1));
    return res;
}

int lca(int a, int b) {
    if (d[a] > d[b])
        forba(k, MAXK, 0)
            if (d[a] - (1 << k) >= d[b])
                a = to[k][a];
    if (d[b] > d[a])
        forba(k, MAXK, 0)
            if (d[b] - (1 << k) >= d[a])
                b = to[k][b];

    if (a == b)
        return a;

    forba(k, MAXK, 0)
        if (to[k][a] != to[k][b]) {
            a = to[k][a];
            b = to[k][b];
        }

    return to[0][a];
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    scanf("%d", &n);
    
    forn(i, n) {
        e[i].clear();
    }

    forn(i, n - 1) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--, b--;

        e[a].push_back(b);
        e[b].push_back(a);
    }

    d[0] = 0;
    dfs(0, 0);

    t.push_back(tree());
    root.push_back(0);
    tsz = 1;
    buildTrees(0, 0, 0);

    forn(i, tsz)
        t[i].build(t[i].sz);

    forab(k, 1, MAXK)
        forn(i, n)
            to[k][i] = to[k - 1][to[k - 1][i]];

    int q;
    scanf("%d", &q);

    forn(i, q) {
        char ch;
        int a, b;

        scanf(" %c %d%d", &ch, &a, &b);

        if (ch == 'I') {
            a--;
            t[tnum[a]].add(tpos[a], b);
        } else {
            assert(ch == 'G');
            a--, b--;

            int c = lca(a, b);

            printf("%d\n", max(getMax(a, c), getMax(b, c)));
        }
    }

    return 0;
}
//END ALGO
