#define _GLIBCXX_DEBUG
// Western Subregional 2015. D.
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

// BEGIN_CODE
struct Edge {
    int v, to, id, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};
typedef pair<multiset<Edge>*, int> Set; // real value: x-Set.se
Set merge(Set a, Set b) {
    if (a.fi == NULL) return b;
    if (b.fi->size() > a.fi->size()) swap(a, b);
    for (Edge e: *b.fi) {
        a.fi->insert(Edge{e.v, e.to, e.id, e.w - b.se + a.se});
    }
    return a;
}
Edge take(Set& set) {
    auto e = *set.fi->begin();
    set.fi->erase(set.fi->begin());
    assert(e.w >= set.se);
    e.w -= set.se;
    set.se += e.w;
    return e;
}

const int maxn = 200500; // must be >= n*2

int n;
int p[maxn];
int get(int x) { return x == p[x] ? x : (p[x] = get(p[x])); }

Set out[maxn]; // outgoing edges from v, endpoints swapped
int b[maxn], top[maxn], done[maxn];
int nc;
int root;
vector<int> edges;
vi cycle[maxn];
vi st;
i64 res;
Edge in[maxn];

void restore(Edge e) {
    edges.push_back(e.id);
    int v = e.v;
    int prev = v;
    while (v != -1) {
        done[v] = true;
        if (v >= n) {
            for (int x: cycle[v]) {
                if (x != prev) {
                    top[x] = -1;
                    restore(in[x]);
                }
            }
        }
        prev = v;
        v = top[v];
    }
}

void solve() {
    forn(i, n*2) p[i] = i, top[i] = -1;
    nc = n;
    root = 0;
    done[root] = true;
    forn(start, n) if (!b[start]) {
        st = {start};
        b[start] = 1;
        while (!done[st[0]]) {
            int v = st.back();
            b[v] = 1;
            if (done[v]) {
                assert(st.size() >= 2);
                st.pop_back();
                assert(!done[st.back()]);
                restore(in[st.back()]);
                assert(done[st.back()]);
                continue;
            }
            assert(!out[v].fi->empty());
            auto e = take(out[v]);
            in[v] = e;
            res += e.w;
            int to = get(e.to);
            if (to == v) continue;
            if (b[to] && !done[to]) {
                while (true) {
                    int u = st.back();
                    st.pop_back();
                    top[u] = nc;
                    p[get(u)] = nc;
                    out[nc] = merge(out[nc], out[u]);
                    cycle[nc].push_back(u);
                    if (u == to) break;
                }
                st.push_back(nc);
                b[nc] = 1;
                ++nc;
            } else {
                st.push_back(to);
            }
        }
    }
    forn(i, n) assert(done[i]);
    assert((int)edges.size() == n-1);
    cout << res << endl;
}

void scan() {
    int m;
    scanf("%d%d", &n, &m);
    forn(i, n) out[i].fi = new multiset<Edge>();
    forn(i, m) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        --u, --v;
        out[v].fi->insert(Edge{v, u, i, w});
    }
}
// END_CODE

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
//     freopen("delivery.in", "r", stdin);
//     freopen("delivery.out", "w", stdout);
#endif

    scan();
    solve();

#ifdef LOCAL
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
