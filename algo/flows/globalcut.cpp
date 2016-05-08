#include <bits/stdc++.h>
using namespace std;
#define forn(i,n) for (int i = 0; i < int(n); ++i)
const int inf = 1e9 + 1e5;
#define all(x) (x).begin(), (x).end()

const int maxn = 505;
namespace StoerWagner {
int g[maxn][maxn];
int dist[maxn];
bool used[maxn];
int n;

void addEdge(int u, int v, int c) {
    g[u][v] += c;
    g[v][u] += c;
}

int run() {
    vector<int> vertices;
    forn (i, n)
        vertices.push_back(i);
    int mincut = inf;
    while (vertices.size() > 1) {
        int u = vertices[0];
        for (auto v: vertices) {
            used[v] = false;
            dist[v] = g[u][v];
        }
        used[u] = true;
        forn (ii, vertices.size() - 2) {
            for (auto v: vertices)
                if (!used[v])
                    if (used[u] || dist[v] > dist[u])
                        u = v;
            used[u] = true;
            for (auto v: vertices)
                if (!used[v])
                    dist[v] += g[u][v];
        }
        int t = -1;
        for (auto v: vertices)
            if (!used[v])
                t = v;
        assert(t != -1);
        mincut = min(mincut, dist[t]);
        vertices.erase(find(all(vertices), t));
        for (auto v: vertices)
            addEdge(u, v, g[v][t]);
    }
    return mincut;
}
} // namespace StoerWagner

int main() {
    StoerWagner::n = 4;
    StoerWagner::addEdge(0, 1, 5);
    StoerWagner::addEdge(2, 3, 5);
    StoerWagner::addEdge(1, 2, 4);
    cerr << StoerWagner::run() << '\n'; // 4
}
