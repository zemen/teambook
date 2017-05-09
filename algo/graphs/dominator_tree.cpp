#define _GLIBCXX_DEBUG
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

//BEGIN_CODE
struct Dom {
    int n;
    vector<vi> e, re; // graph (on v), reverse graph (on id)
    vi id, p, sdom, dom, dsu, best;
    vector<vi> bucket;
    int dtime = 0;

    Dom() {}
    Dom(int n) : n(n), e(n), re(n), id(n, -1), p(n),
        sdom(n), dom(n), dsu(n), best(n), bucket(n)
    {  }

    void find(int v) {
        if (v != dsu[v]) {
            find(dsu[v]);
            if (sdom[best[dsu[v]]] <= sdom[best[v]]) {
                best[v] = best[dsu[v]];
            }
            dsu[v] = dsu[dsu[v]];
        }
    }

    void dfs1(int v) {
        id[v] = dtime++;
        for (int to: e[v]) {
            if (id[to] == -1) {
                dfs1(to);
                p[id[to]] = id[v];
            }
            re[id[to]].push_back(id[v]);
        }
    }

    void pre() {
        dfs1(0);
        iota(all(best), 0);
        iota(all(sdom), 0);
        iota(all(dsu), 0);
    }

    void run() {
        pre();
        for (int v = n-1; v >= 0; --v) {
            for (int w: bucket[v]) {
                find(w);
                dom[w] = best[w];
            }
            for (int u: re[v]) {
                find(u);
                sdom[v] = min(sdom[v], sdom[best[u]]);
            }
            if (v) {
                bucket[sdom[v]].pb(v);
                dsu[v] = p[v]; // unite(v, p[v])
            }
        }

        for (int v = 1; v < n; ++v) {
            if (dom[v] != sdom[v]) {
                dom[v] = dom[dom[v]];
            }
        }

        vi ndom(n), rev(n);
        forn(i, n) rev[id[i]] = i;
        forn(i, n) ndom[i] = rev[dom[id[i]]];
        dom = ndom;
    }
};
//END_CODE

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    forn(TTT, 1) {
    int n, m;
    cin >> n >> m;
    Dom d(n);
    forn(i, m) {
        int u, v;
        cin >> u >> v;
        d.e[u-1].pb(v-1);
    }
    d.run();
    set<int> doms;
//     for (int x: d.dom) doms.insert(d.rev[x]);
    for (int x: d.dom) doms.insert(x);
    cout << doms.size() << "\n";

    bool fi = true;
    for (int x: doms) {
        if (!fi) cout << " ";
        fi = false;
        cout << x+1;
    }
    cout << "\n";
    }

#ifdef LOCAL
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
