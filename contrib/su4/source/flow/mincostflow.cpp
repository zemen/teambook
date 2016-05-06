
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
const ll LINF = 1e18;
const ldb EPS = 1e-8;
const ldb PI = acos(-1.0);
const int MAXN = 300;
const int MAXM = 1e5 + 100;

//BEGIN ALGO
/*
 * Mincostmaxflow algorithm
 * O(n^3 m)
 * O(n^3) on unit capacities
 * */
struct edge {
    int st, d;
    ll f, c;
    ll w;
    edge * inv;
    edge() : st(0), d(0), f(0), c(0), w(0) {}
    edge(int st, int d, ll c, ll w) : st(st), d(d), f(0), c(c), w(w) {}
};

vector <edge*> e[MAXN];
edge me[MAXM];
int m = 0; //edges
int n; //vertices
int source;
int sink;

void addEdge(int u, int v, ll c, ll w) {
    me[m] = edge(u, v, c, w);
    edge * to = &me[m++];
    me[m] = edge(v, u, 0, -w);
    edge * back = &me[m++];
    to->inv = back;
    back->inv = to;
    e[u].pb(to);
    e[v].pb(back);
}

bool used[MAXN];
ll phi[MAXN];
ll d[MAXN];
edge * p[MAXN];

void ford() {
    FOR(i, n)
        d[i] = LINF;
    d[source] = 0;
    FOR(it, n - 1) {
        FOR(i, m) {
            edge* ed = &me[i];
            if (ed->c == ed->f)
                continue;
            if (d[ed->d] > d[ed->st] + ed->w) {
                d[ed->d] = d[ed->st] + ed->w;
                p[ed->d] = &me[i];
            }
        }
    }
}

void dijkstra() {
    FOR(i, n) {
        d[i] = LINF;
        used[i] = false;
    }
    d[source] = 0;
    FOR(it, n) {
        int mn = -1;
        FOR(i, n) {
            if (used[i])
                continue;
            if (mn == -1 || d[mn] > d[i])
                mn = i;
        }
        if (mn == -1 || d[mn] >= LINF)
            break;
        used[mn] = true;
        for (auto ed : e[mn]) {
            if (ed->c == ed->f)
                continue;
            if (d[ed->d] > d[mn] + ed->w - phi[ed->d] + phi[mn]) {
                d[ed->d] = d[mn] + ed->w - phi[ed->d] + phi[mn];
                p[ed->d] = ed;
            }

        }
    }
}


ll flow = 0;
ll mincostflow() {
    ll cost = 0;
    clr(phi);
    for (int iter = 0;; ++iter) {
        if (iter == 0) {
            ford();
        } else {
            dijkstra();
        }
        if (d[sink] == LINF)
            break;
        FOR(i, n) {
            if (d[i] < LINF)
                phi[i] += d[i];
        }
        int st = sink;
        ll pushed = LINF;
        while (st != source) {
            pushed = min(pushed, (p[st]->c - p[st]->f));
            st = p[st]->st;
        }
        flow += pushed;
        st = sink;
        while (st != source) {
            p[st]->f += pushed;
            p[st]->inv->f -= pushed;
            cost += pushed * p[st]->w;
            st = p[st]->st;
        }
    }
    return cost;
}

int main() {
    int k;
    cin >> n >> k;
    cin >> sink >> source;
    FOR(i, k) {
        int u, v;
        ll c, w;
        cin >> u >> v >> c >> w;
        addEdge(u, v, c, w);
    }
    cout << mincostflow();
    
    return 0;
}
//END ALGO
