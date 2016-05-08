#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define all(x) (x).begin(), (x).end()
const int inf = 1e9+100500;
typedef vector<int> vi;

// max width team notebook allows -----------------------------------

// BEGIN_CODE
// WARNING: this code wasn't submitted anywhere

namespace TwoChinese {

struct Edge {
    int to, w, id;
    bool operator<(const Edge& other) const {
        return to < other.to || (to == other.to && w < other.w);
    }
};
typedef vector<vector<Edge>> Graph;

const int maxn = 2050;

// global, for supplementary algorithms
int b[maxn];
int tin[maxn], tup[maxn];
int dtime; // counter for tin, tout
vector<int> st;
int nc; // number of strongly connected components
int q[maxn];

int answer;

void tarjan(int v, const Graph& e, vector<int>& comp) {
    b[v] = 1;
    st.push_back(v);
    tin[v] = tup[v] = dtime++;

    for (Edge t: e[v]) if (t.w == 0) {
        int to = t.to;
        if (b[to] == 0) {
            tarjan(to, e, comp);
            tup[v] = min(tup[v], tup[to]);
        } else if (b[to] == 1) {
            tup[v] = min(tup[v], tin[to]);
        }
    }

    if (tin[v] == tup[v]) {
        while (true) {
            int t = st.back();
            st.pop_back();
            comp[t] = nc;
            b[t] = 2;
            if (t == v) break;
        }
        ++nc;
    }
}

vector<Edge> bfs(
    const Graph& e,const vi& init, const vi& comp)
{
    int n = e.size();
    forn(i, n) b[i] = 0;
    int lq = 0, rq = 0;
    for (int v: init) b[v] = 1, q[rq++] = v;

    vector<Edge> result;

    while (lq != rq) {
        int v = q[lq++];
        for (Edge t: e[v]) if (t.w == 0) {
            int to = t.to;
            if (b[to]) continue;
            if (!comp.empty() && comp[v] != comp[to]) continue;
            b[to] = 1;
            q[rq++] = to;
            result.push_back(t);
        }
    }

    return result;
}

// warning: check that each vertex is reachable from root
vector<Edge> run(Graph e, int root) {
    int n = e.size();

    // find minimum incoming weight for each vertex
    vector<int> minw(n, inf);
    forn(v, n) for (Edge t: e[v]) {
        minw[t.to] = min(minw[t.to], t.w);
    }
    forn(v, n) for (Edge &t: e[v]) if (t.to != root) {
        t.w -= minw[t.to];
    }
    forn(i, n) if (i != root) answer += minw[i];

    // check if each vertex is reachable from root by zero edges
    vector<Edge> firstResult = bfs(e, {root}, {});
    if ((int)firstResult.size() + 1 == n) {
        return firstResult;
    }

    // find stongly connected comp-s and build compressed graph
    vector<int> comp(n);
    forn(i, n) b[i] = 0;
    nc = 0;
    dtime = 0;
    forn(i, n) if (!b[i]) tarjan(i, e, comp);

    // multiple edges may be removed here if needed
    Graph ne(nc);
    forn(v, n) for (Edge t: e[v]) {
        if (comp[v] != comp[t.to]) {
            ne[comp[v]].push_back({comp[t.to], t.w, t.id});
        }
    }

    // run recursively on compressed graph
    vector<Edge> subres = run(ne, comp[root]);

    // find incoming edge id for each component, init queue
    // if there is an edge (u, v) between different components
    // than v is added to queue
    vector<int> incomingId(nc);
    for (Edge e: subres) {
        incomingId[e.to] = e.id;
    }

    vector<Edge> result;
    vector<int> init;
    init.push_back(root);
    forn(v, n) for (Edge t: e[v]) {
        if (incomingId[comp[t.to]] == t.id) {
            result.push_back(t);
            init.push_back(t.to);
        }
    }

    // run bfs to add edges inside components and return answer
    vector<Edge> innerEdges = bfs(e, init, comp);
    result.insert(result.end(), all(innerEdges));

    assert((int)result.size() + 1 == n);
    return result;
}

} // namespace TwoChinese

void test () {
    auto res = TwoChinese::run({
        {{1,5,0},{2,5,1}},
        {{3,1,2}},
        {{1,2,3},{4,1,4}},
        {{1,1,5},{4,2,6}},
        {{2,1,7}}},
        0);
    cout << TwoChinese::answer << endl;
    for (auto e: res) cout << e.id << " ";
    cout << endl;
    // 9     0 6 2 7
}

// END_CODE

int main() {
    test();
    return 0;
    freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    TwoChinese::Graph e(n);
    vector<int> from(m), to(m), w(m);
    forn(i, m) {
        int u, v, ww;
        cin >> u >> v >> ww;
        e[u].push_back({v, ww, i});
        from[i] = u; to[i] = v; w[i] = ww;
    }

    auto res = TwoChinese::run(e, 0);
    cout << TwoChinese::answer << endl;
    for (auto e: res) {
        int i = e.id;
        cout << from[i] << " -> " << to[i] << " (" << w[i] << ")" << endl;
    }

    return 0;
}
