#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define forn(i,n) for (int i = 0; i < int(n); ++i)
    
namespace MinCost {
    const ll infc = 1e12;

    struct Edge {
        int to;
        ll c, f, cost;

        Edge(int to, ll c, ll cost): to(to), c(c), f(0), cost(cost) {
        }
    };

    int N, S, T;
    int totalFlow;
    ll totalCost;
    const int maxn = 505;
    vector<Edge> edge;
    vector<int> g[maxn];

    void addEdge(int u, int v, ll c, ll cost) {
        g[u].push_back(edge.size());
        edge.emplace_back(v, c, cost);
        g[v].push_back(edge.size());
        edge.emplace_back(u, 0, -cost);
    }

    ll dist[maxn];
    int fromEdge[maxn];

    bool inQueue[maxn];
    bool fordBellman() {
        forn (i, N)
            dist[i] = infc;
        dist[S] = 0;
        inQueue[S] = true;
        vector<int> q;
        q.push_back(S);
        for (int ii = 0; ii < int(q.size()); ++ii) {
            int u = q[ii];
            inQueue[u] = false;
            for (int e: g[u]) {
                if (edge[e].f == edge[e].c)
                    continue;
                int v = edge[e].to;
                ll nw = edge[e].cost + dist[u];
                if (nw >= dist[v])
                    continue;
                dist[v] = nw;
                fromEdge[v] = e;
                if (!inQueue[v]) {
                    inQueue[v] = true;
                    q.push_back(v);
                }
            }
        }
        return dist[T] != infc;
    }

    ll pot[maxn];
    bool dikstra() {
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
        forn (i, N)
            dist[i] = infc;
        dist[S] = 0;
        q.emplace(dist[S], S);
        while (!q.empty()) {
            int u = q.top().second;
            ll cdist = q.top().first;
            q.pop();
            if (cdist != dist[u])
                continue;
            for (int e: g[u]) {
                int v = edge[e].to;
                if (edge[e].c == edge[e].f)
                    continue;
                ll w = edge[e].cost + pot[u] - pot[v];
                assert(w >= 0);
                ll ndist = w + dist[u];
                if (ndist >= dist[v])
                    continue;
                dist[v] = ndist;
                fromEdge[v] = e;
                q.emplace(dist[v], v);
            }
        }
        if (dist[T] == infc)
            return false;
        forn (i, N) {
            if (dist[i] == infc)
                continue;
            pot[i] += dist[i];
        }
        return true;
    }

    bool push() {
        //2 variants
        //if (!fordBellman())
        if (!dikstra())
            return false;
        ++totalFlow;
        int u = T;
        while (u != S) {
            int e = fromEdge[u];
            totalCost += edge[e].cost;
            edge[e].f++;
            edge[e ^ 1].f--;
            u = edge[e ^ 1].to;
        }
        return true;
    }
};

int main() {
    MinCost::N = 3, MinCost::S = 1, MinCost::T = 2;
    MinCost::addEdge(1, 0, 3, 5);
    MinCost::addEdge(0, 2, 4, 6);
    while (MinCost::push());
    cout << MinCost::totalFlow << ' ' << MinCost::totalCost << '\n'; //3 33
}
