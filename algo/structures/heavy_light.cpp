/*
    Heavy-light with 2 operations: add value to vertex, get maximum on path
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i,n) for (int i = 0; i < int(n); ++i)
#define sz(x) ((int) (x).size())

//BEGIN_CODE
const int maxn = 100500;
const int maxd = 17;

vector<int> g[maxn];

struct Tree {
    vector<int> t;
    int base;

    Tree(): base(0) {
    }

    Tree(int n) {
        base = 1;
        while (base < n)
            base *= 2;
        t = vector<int>(base * 2, 0);
    }

    void put(int v, int delta) {
        assert(v < base);
        v += base;
        t[v] += delta;
        while (v > 1) {
            v /= 2;
            t[v] = max(t[v * 2], t[v * 2 + 1]);
        }
    }

    //Careful here: cr = 2 * maxn
    int get(int l, int r, int v=1, int cl=0, int cr = 2*maxn) {
        cr = min(cr, base);
        if (l <= cl && cr <= r)
            return t[v];
        if (r <= cl || cr <= l)
            return 0;
        int cc = (cl + cr) / 2;
        return max(get(l, r, v * 2, cl, cc),
            get(l, r, v * 2 + 1, cc, cr));
    }
};

namespace HLD {
    int h[maxn];
    int timer;
    int in[maxn], out[maxn], cnt[maxn];
    int p[maxd][maxn];
    int vroot[maxn];
    int vpos[maxn];
    int ROOT;
    Tree tree[maxn];

    void dfs1(int u, int prev) {
        p[0][u] = prev;
        in[u] = timer++;
        cnt[u] = 1;
        for (int v: g[u]) {
            if (v == prev)
                continue;
            h[v] = h[u] + 1;
            dfs1(v, u);
            cnt[u] += cnt[v];
        }
        out[u] = timer;
    }

    int dfs2(int u, int prev) {
        int to = -1;
        for (int v: g[u]) {
            if (v == prev)
                continue;
            if (to == -1 || cnt[v] > cnt[to])
                to = v;
        }
        int len = 1;
        for (int v: g[u]) {
            if (v == prev)
                continue;
            if (to == v) {
                vpos[v] = vpos[u] + 1;
                vroot[v] = vroot[u];
                len += dfs2(v, u);
            }
            else {
                vroot[v] = v;
                vpos[v] = 0;
                dfs2(v, u);
            }
        }
        if (vroot[u] == u)
            tree[u] = Tree(len);
        return len;
    }

    void init(int n) {
        timer = 0;
        h[ROOT] = 0;
        dfs1(ROOT, ROOT);
        forn (d, maxd - 1)
            forn (i, n)
                p[d + 1][i] = p[d][p[d][i]];
        vroot[ROOT] = ROOT;
        vpos[ROOT] = 0;
        dfs2(ROOT, ROOT);
        //WARNING: init all trees
    }

    bool isPrev(int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    }

    int lca(int u, int v) {
        for (int d = maxd - 1; d >= 0; --d)
            if (!isPrev(p[d][u], v))
                u = p[d][u];
        if (!isPrev(u, v))
            u = p[0][u];
        return u;
    }

    //for each v: h[v] >= toh
    int getv(int u, int toh) {
        int res = 0;
        while (h[u] >= toh) {
            int rt = vroot[u];
            int l = max(0, toh - h[rt]), r = vpos[u] + 1;
            res = max(res, tree[rt].get(l, r));
            if (rt == ROOT)
                break;
            u = p[0][rt];
        }
        return res;
    }

    int get(int u, int v) {
        int w = lca(u, v);
        return max(getv(u, h[w]), getv(v, h[w] + 1));
    }

    void put(int u, int val) {
        int rt = vroot[u];
        int pos = vpos[u];
        tree[rt].put(pos, val);
    }
};
//END_CODE

void solve() {
    int n;
    cin >> n;
    forn (i, n)
        g[i].clear();
    forn (i, n - 1) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    HLD::init(n);
    int q;
    cin >> q;
    forn (i, q) {
        char type;
        int u, v;
        cin >> type >> u >> v;
        if (type == 'I')
            HLD::put(u - 1, v);
        else
            cout << HLD::get(u - 1, v - 1) << '\n';
    }
}

int main() {
    #ifdef LOCAL
    assert(freopen("hld.in", "r", stdin));
    #else
    #endif
    solve();
}
