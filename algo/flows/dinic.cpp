#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
typedef long long i64;

// BEGIN_CODE
namespace Dinic {
const int maxn = 10010;

struct Edge {
    int to, c, f;
} es[maxn*2];
int ne = 0;

int n;
vector<int> e[maxn];
int q[maxn], d[maxn], pos[maxn];
int S, T;

void addEdge(int u, int v, int c) {
    assert(c <= 1000000000);
    es[ne] = {v, c, 0};
    e[u].push_back(ne++);
    es[ne] = {u, 0, 0};
    e[v].push_back(ne++);
}

bool bfs() {
    forn(i, n) d[i] = maxn;
    d[S] = 0, q[0] = S;
    int lq = 0, rq = 1;
    while (lq != rq) {
        int v = q[lq++];
        for (int id: e[v]) if (es[id].f < es[id].c) {
            int to = es[id].to;
            if (d[to] == maxn)
                d[to] = d[v] + 1, q[rq++] = to;
        }
    }
    return d[T] != maxn;
}

int dfs(int v, int curf) {
    if (v == T || curf == 0) return curf;
    for (int &i = pos[v]; i < (int)e[v].size(); ++i) {
        int id = e[v][i];
        int to = es[id].to;
        if (es[id].f < es[id].c && d[v] + 1 == d[to]) {
            if (int ret = dfs(to, min(curf, es[id].c - es[id].f))) {
                es[id].f += ret;
                es[id^1].f -= ret;
                return ret;
            }
        }
    }
    return 0;
}

i64 dinic(int S, int T) {
    Dinic::S = S, Dinic::T = T;
    i64 res = 0;
    while (bfs()) {
        forn(i, n) pos[i] = 0;
        while (int f = dfs(S, 1e9)) {
            assert(f <= 1000000000);
            res += f;
        }
    }
    return res;
}

} // namespace Dinic

void test() {
    Dinic::n = 4;
    Dinic::addEdge(0, 1, 1);
    Dinic::addEdge(0, 2, 2);
    Dinic::addEdge(2, 1, 1);
    Dinic::addEdge(1, 3, 2);
    Dinic::addEdge(2, 3, 1);
    cout << Dinic::dinic(0, 3) << endl; // 3

}
// END_CODE

int main() {
    int m;
    cin >> Dinic::n >> m;
    forn(i, m) {
        int u, v, c;
        cin >> u >> v >> c;
        Dinic::addEdge(u-1, v-1, c);
    }
    cout << Dinic::dinic(0, Dinic::n-1) << endl;
}

// http://informatics.mccme.ru/mod/statements/view3.php?id=262&chapterid=2784
