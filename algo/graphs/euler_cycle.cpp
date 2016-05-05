#include <bits/stdc++.h>
using namespace std;

const int maxn = 100100;
const int maxm = 100100;

struct Edge {
    int to, id;
};

bool usedEdge[maxm];
vector<Edge> g[maxn];
int ptr[maxn];

vector<int> cycle;
void eulerCycle(int u) {
    while (ptr[u] < (int) g[u].size() && usedEdge[g[u][ptr[u]].id])
        ++ptr[u];
    if (ptr[u] == (int) g[u].size())
        return;
    const Edge &e = g[u][ptr[u]];
    usedEdge[e.id] = true;
    eulerCycle(e.to);
    cycle.push_back(e.id);
    eulerCycle(u);
}

int edges = 0;
void addEdge(int u, int v) {
    g[u].push_back(Edge{v, edges});
    g[v].push_back(Edge{u, edges++});
}

int main() {
}
