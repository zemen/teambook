#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i, n) for (int i = 0; i < int(n); ++i)
typedef long long i64;
typedef long long ll;
const ll infl = 2e18;

// BEGIN_CODE
namespace Dinic {
const int maxn = 100100;
struct Edge {
    int to;
    ll c, f;
    Edge(int to, ll c): to(to), c(c), f(0) {}
};

vector<Edge> es;
vector<int> g[maxn];
int q[maxn], d[maxn], pos[maxn];
int N, S, T;

void addEdge(int u, int v, ll c) {
    g[u].push_back(sz(es));
    es.emplace_back(v, c);
    g[v].push_back(sz(es));
    es.emplace_back(u, 0);
}

bool bfs() {
    fill(d, d + N, maxn);
    d[S] = 0, q[0] = S;
    int rq = 1;
    forn (lq, rq) {
        int u = q[lq];
        for (int id: g[u]) {
            if (es[id].c == es[id].f)
                continue;
            int v = es[id].to;
            if (d[v] == maxn) {
                d[v] = d[u] + 1;
                q[rq++] = v;
            }
        }
    }
    return d[T] != maxn;
}

ll dfs(int u, ll curf) {
    if (u == T)
        return curf;
    ll ret = 0;
    for (int &i = pos[u]; i < sz(g[u]); ++i) {
        int id = g[u][i];
        int v = es[id].to;
        ll delta = min(curf, es[id].c - es[id].f);
        if (delta == 0 || d[v] != d[u] + 1)
            continue;
        delta = dfs(v, delta);
        curf -= delta;
        ret += delta;
        es[id].f += delta;
        es[id ^ 1].f -= delta;
        if (curf == 0)
            return ret;
    }
    return ret;
}

ll dinic(int S, int T) {
    Dinic::S = S, Dinic::T = T;
    ll res = 0;
    while (bfs()) {
        fill(pos, pos + N, 0);
        while (ll cur = dfs(S, infl))
            res += cur;
    }
    return res;
}

} // namespace Dinic

void test() {
    Dinic::N = 4;
    Dinic::addEdge(0, 1, 1);
    Dinic::addEdge(0, 2, 2);
    Dinic::addEdge(2, 1, 1);
    Dinic::addEdge(1, 3, 2);
    Dinic::addEdge(2, 3, 1);
    cout << Dinic::dinic(0, 3) << endl; // 3
}
/*
LR-поток находит не максимальный поток.
Добавим новый сток S' и исток T'. Заменим ребро (u, v, l, r)
LR-сети на ребра (u, T', l), (S', v, l), (u, v, r - l).
Добавим ребро (T, S, k). Ставим значение k=inf, пускаем поток.
Проверяем, что все ребра из S' насыщены (иначе ответ не
существует).  Бинпоиском находим наименьшее k, что величина
потока не изменится.  Это k - величина МИНИМАЛЬНОГО потока,
удовлетворяющего ограничениям. */
// END_CODE

int main() {
    int m;
    cin >> Dinic::N >> m;
    forn(i, m) {
        int u, v, c;
        cin >> u >> v >> c;
        Dinic::addEdge(u-1, v-1, c);
    }
    cout << Dinic::dinic(0, Dinic::N-1) << endl;
}

// http://informatics.mccme.ru/mod/statements/view3.php?id=262&chapterid=2784
