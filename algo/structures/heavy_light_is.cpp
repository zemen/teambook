// timus 1553
#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
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
typedef long double ld;
typedef long long ll;

const int maxn = 100500;

struct Rmq {
    vi rmq;
    int sz;
    Rmq() {}
    Rmq(int n) {
        sz = 1;
        while (sz < n) sz *= 2;
        rmq.assign(sz * 2, 0);
    }

    void put(int i, int x) {
        i += sz;
        rmq[i] += x;
        for (i /= 2; i; i /= 2) {
            rmq[i] = max(rmq[i*2], rmq[i*2+1]);
        }
    }

    int get(int l, int r) {
        --r;
        l += sz;
        r += sz;
        int res = 0;
        while (l < r) {
            if (l%2 == 1) res = max(res, rmq[l]);
            if (r%2 == 0) res = max(res, rmq[r]);
            l = (l+1)/2;
            r = (r-1)/2;
        }
        if (l == r) res = max(res, rmq[l]);
        return res;
    }
};

// BEGIN_CODE
int n;
vi e[maxn];
int p[maxn], s[maxn], h[maxn], root[maxn];
Rmq rmq[maxn];

void dfs1(int v, int anc) {
    s[v] = 1;
    if (anc != -1) e[v].erase(find(all(e[v]), anc));
    for (int to: e[v]) {
        p[to] = v;
        h[to] = h[v] + 1;
        dfs1(to, v);
        s[v] += s[to];
    }
}

void dfs2(int v, int rt) {
    root[v] = rt;
    if (e[v].empty()) {
        rmq[rt] = Rmq(h[v] - h[rt] + 1);
        return;
    }
    int mxv = e[v][0];
    for (int to: e[v]) {
        if (s[to] > s[mxv]) mxv = to;
    }
    for (int to: e[v]) {
        dfs2(to, to == mxv ? rt : to);
    }
}

int get(int u, int v) {
    int res = 0;
    int t;
    while (root[u] != root[v]) {
        if (h[root[u]] > h[root[v]]) {
            t = rmq[root[u]].get(0, h[u] - h[root[u]] + 1);
            u = p[root[u]];
        } else {
            t = rmq[root[v]].get(0, h[v] - h[root[v]] + 1);
            v = p[root[v]];
        }
        res = max(res, t);
    }
    int r = root[u];
    if (h[u] > h[v]) {
        t = rmq[r].get(h[v] - h[r], h[u] - h[r] + 1);
    } else {
        t = rmq[r].get(h[u] - h[r], h[v] - h[r] + 1);
    }
    return max(res, t);
}

void put(int v, int x) {
    rmq[root[v]].put(h[v] - h[root[v]], x);
}

void init() {
    const int ROOT = 0;
    dfs1(ROOT, -1);
    dfs2(ROOT, ROOT);
}
// END_CODE

void scan() {
    cin >> n;
    forn(i, n-1) {
        int u, v;
        cin >> u >> v;
        e[--u].pb(--v);
        e[v].pb(u);
    }
}


void solve() {
    int q;
    cin >> q;
    forn(i, q) {
        char c;
        int x, y;
        cin >> c >> x >> y;
        if (c == 'I') {
            put(x-1, y);
        } else {
            cout << get(x-1, y-1) << "\n";
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio(false);

    scan();
    solve();

#ifdef LOCAL
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
