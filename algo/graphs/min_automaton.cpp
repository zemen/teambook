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

const int maxn = 200500;
const int A = 15;

int n;
int col[maxn];

//BEGIN_CODE
vi inc[maxn][A];
int lst[maxn], pos[maxn], part[maxn];
int lp[maxn], rp[maxn], nrp[maxn];
int upd[maxn], used[maxn], inq[maxn];
vector<int> q;
int dtime;
int np; // number of classes
vector<int> toRefine[A];

void doSwap(int x, int y) {
    swap(lst[pos[x]], lst[pos[y]]);
    swap(pos[x], pos[y]);
}

void refine(const vi& a) {
    ++dtime;
    vector<int> updated;
    for (int x: a) {
        if (used[x] == dtime) continue;
        used[x] = dtime;

        int p = part[x];
        if (upd[p] != dtime) {
            upd[p] = dtime;
            nrp[p] = rp[p];
            updated.pb(p);
        }

        doSwap(x, lst[nrp[p]-1]);
        --nrp[p];
    }

    for (int p: updated) {
        if (lp[p] == nrp[p]) continue;
        lp[np] = nrp[p];
        rp[np] = rp[p];
        rp[p] = nrp[p];
        for (int i = lp[np]; i < rp[np]; ++i) {
            part[lst[i]] = np;
        }

        if (inq[p] || rp[np] - lp[np] < rp[p] - rp[np]) {
            inq[np] = 1;
            q.push_back(np);
        } else {
            inq[p] = 1;
            q.push_back(p);
        }

        ++np;
    }
}

void solve() {
    forn(i, n) lst[i] = i;
    sort(lst, lst+n, [](int i, int j) {
        return col[i] < col[j];
    });

    forn(i, n) {
        if (i && col[lst[i]] != col[lst[i-1]]) {
            rp[np] = i;
            lp[++np] = i;
        }
        part[lst[i]] = np;
        pos[lst[i]] = i;
    }
    rp[np++] = n;

    forn(i, np) {
        inq[i] = 1;
        q.push_back(i);
    }

    forn(i, q.size()) {
        int p = q[i];
        inq[p] = false;
        forn(c, A) {
            toRefine[c].clear();
            for (int id = lp[p]; id < rp[p]; ++id) {
                toRefine[c].insert(
                    toRefine[c].end(), all(inc[lst[id]][c]));
            }
        }
        forn(c, A) if (!toRefine[c].empty()) {
            refine(toRefine[c]);
        }
    }

    forn(i, n) printf("%d\n", part[i] + 1);
}
//END_CODE

void scan() {
    scanf("%d", &n);
    forn(i, n) {
        scanf("%d", &col[i]);
        int k;
        scanf("%d", &k);
        forn(j, k) {
            int to;
            scanf("%d", &to);
            inc[to-1][j].pb(i);
        }
    }
}


int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    scan();
    solve();

#ifdef LOCAL
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
