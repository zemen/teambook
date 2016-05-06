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
const int MAXN = 510;

//BEGIN ALGO
/* Hungarian algorithm
 * O(n^2 m)
 * */
//one-based indices!
ldb a[MAXN][MAXN]; //given matrix
ldb u[MAXN]; //row potentials
ldb v[MAXN]; //column potentials
int p[MAXN]; //column pair, 0 if none; p[0] = current row
int way[MAXN]; //previous column in path
ldb minv[MAXN]; //column minimum
bool used[MAXN];

int n, m; //rows, columns

/* the algorithm boils down to this:
 * find optimal potentials(u[i] + v[j] == a[i][j]);
 * this is accomplished by searching for complementary
 * path in hard edges graph (edge is hard, if above condition is satisfied);
 * if such path can't be found, change potentials */
ldb hungary() {
    FOR(i, n + 1)
        u[i] = 0;
    FOR(i, m + 1)
        v[i] = 0; //set potentials to zero
    FOR(i, m + 1) {
        p[i] = 0;
        way[i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0; //free column to find
        FOR(i, m + 1) {
            minv[i] = INF;
            used[i] = false;
        }
        do {
            used[j0] = true;
            int i0 = p[j0]; //i0 adjacent to j0
            ldb delta = INF;
            int j1; //column, where minimum is
            //update minv and delta
            for (int j = 1; j <= m; ++j) {
                if (!used[j]) {
                    ldb cur = a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j] - EPS) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta - EPS) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            //update potetials and minv
            FOR(j, m + 1) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);
        //complementary path is found, now we invert it
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    return -v[0];
}

int main() {
    cin >> n >> m;
    FOR(i, n)
        FOR(j, m)
            cin >> a[i + 1][j + 1];
    cout << hungary() << '\n';
    
    return 0;
}
//END ALGO
