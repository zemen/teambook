#include <bits/stdc++.h>
using namespace std;
#define forn(i,n) for (int i = 0; i < int(n); ++i)
//BEGIN_CODE
const int maxn = 200100; //2 x number of variables

namespace TwoSAT {
    int n; //number of variables
    bool used[maxn];
    vector<int> g[maxn];
    vector<int> gr[maxn];
    int comp[maxn];
    int res[maxn];
    vector<int> ord;

    //u*2 - false, u*2+1 - true
    void addEdge(int u, int v) { //u or v
        g[u ^ 1].push_back(v);
        g[v ^ 1].push_back(u);
        gr[u].push_back(v ^ 1);
        gr[v].push_back(u ^ 1);
    }

    void dfs1(int u) {
        used[u] = true;
        for (int v: g[u]) {
            if (used[v])
                continue;
            dfs1(v);
        }
        ord.push_back(u);
    }

    void dfs2(int u, int cc) {
        used[u] = true;
        comp[u] = cc;
        for (int v: gr[u]) {
            if (used[v])
                continue;
            dfs2(v, cc);
        }
    }

    bool run() {
        fill(used, used + 2 * n, false);
        forn (i, 2 * n)
            if (!used[i])
                dfs1(i);
        reverse(ord.begin(), ord.end());
        assert((int) ord.size() == (2 * n));
        fill(used, used + 2 * n, false);
        int cc = 0;
        for (int u: ord)
            if (!used[u])
                dfs2(u, cc++);
        forn (i, n) {
            if (comp[i * 2] == comp[i * 2 + 1])
                return false;
            res[i] = comp[i * 2] < comp[i * 2 + 1];
        }
        return true;
    }

    void clear() {
        ord.clear();
        forn (i, 2 * n) {
            g[i].clear();
            gr[i].clear();
            comp[i] = -1;
        }
    }
};

int main() {
    TwoSAT::n = 2;
    TwoSAT::addEdge(1, 3); //x or y
    TwoSAT::addEdge(1, 2); //x or !y
    TwoSAT::addEdge(2, 2); //!y or !y
    assert(TwoSAT::run());
    cout << TwoSAT::res[0] << ' ' << TwoSAT::res[1] << '\n';
    //1 0, x=true, y=false
}
