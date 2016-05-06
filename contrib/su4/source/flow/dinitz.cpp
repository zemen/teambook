
#include <cassert>
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
#ifdef LOCAL
#define print(a) cerr << #a << ": " << a << '\n';
#else
#define print(a)
#endif

typedef long long ll;
typedef long double ldb;

const int INF = 1e9;
const ldb EPS = 1e-8;
const ldb PI = acos(-1.0);
const int MAXN = 300;
const int MAXM = 1e5 + 100;
//BEGIN ALGO
/*
 * Dinitz's max flow algorithm with scaling
 * O(n^2 m)
 * O(sqrt(n) m) on unit network
 * O(min(sqrt(m), n^(2/3)) m) on network with unit capacities
 * O(log U max(sqrt(m), n^(2/3)) m) with scaling
 */
struct edge {
    int d;
    int f, c;
    edge * inv;
    edge() : d(0), f(0), c(0) {}
    edge(int d, int c) : d(d), f(0), c(c) {}
};

vector <edge*> e[MAXN];
edge me[MAXM];
int m = 0; //edges
int n; //vertices
int source;
int sink;

void addEdge(int u, int v, int c) {
    me[m] = edge(v, c);
    edge * to = &me[m++];
    me[m] = edge(u, 0);
    edge * back = &me[m++];
    to->inv = back;
    back->inv = to;
    e[u].pb(to);
    e[v].pb(back);
}

int minc; //for scaling

int used[MAXN];
int level[MAXN];
int first[MAXN]; //first unused edge

void qAdd(queue<int> &q, int v, int dist) {
    if (used[v])
        return;
    used[v] = true;
    q.push(v);
    level[v] = dist;
}

bool bfs(int start) {
    queue<int> q;
    clr(used);
    memset(level, -1, sizeof(level));
    qAdd(q, start, 0);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto ed : e[cur]) {
            if (ed->c - ed->f <= minc)
                continue;
            qAdd(q, ed->d, level[cur] + 1);
        }
    }
    return level[sink] != -1;
}

int dfs(int v, int flow) {
    if (v == sink)
        return flow;
    for (;first[v] < e[v].size(); ++first[v]) {
        edge * ed = e[v][first[v]];
        if (ed->c - ed->f <= minc || level[ed->d] != level[v] + 1)
            continue;
        if (int pushed = dfs(ed->d, min(flow, ed->c - ed->f))) {
            ed->f += pushed;
            ed->inv->f -= pushed;
            return pushed;
        }
    }
    return 0;
}

int dinitz() {
    minc = 0;
    FOR(i, m) {
        minc = max(minc, me[i].c);
    }
    int flow = 0;
    do {
        minc /= 2;
        while (bfs(source)) {
            clr(first);
            while (int pushed = dfs(source, INF)) {
                flow += pushed;
            }
        }
    } while (minc > 0);
    return flow;
}

int main() {
    int k;
    cin >> n >> k;
    cin >> sink >> source;
    FOR(i, k) {
        int u, v, c;
        cin >> u >> v >> c;
        addEdge(u, v, c);
    }
    int flow = dinitz();
    cout << flow << '\n';
    return 0;
}
//END ALGO
