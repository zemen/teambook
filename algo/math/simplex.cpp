#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
typedef long long ll;
typedef long long i64;
typedef long double ld;
const int inf = int(1e9) + int(1e5);
const ll infl = ll(2e18) + ll(1e10);

const int maxn = 505;
const int maxm = 505;

const ld eps = 1e-9;

bool eq(ld a, ld b) {
    return fabsl(a - b) < eps;
}

//BEGIN_CODE
namespace Simplex {

ld D[maxm][maxn]; // [n+2][m+2]
int B[maxm];
int N[maxn];
ld x[maxn];
int n, m;

//x >= 0, Ax <= b, c^Tx -> max
void init(int _n, int _m, ld A[][maxn], ld *b, ld *c) {
    n = _n, m = _m;
    forn (i, m)
        forn (j, n)
            D[i][j] = -A[i][j];
    forn (i, m) {
        D[i][n] = 1;
        D[i][n + 1] = b[i];
    }
    forn (j, n) {
        D[m][j] = c[j];
        D[m + 1][j] = 0;
    }
    D[m][n + 1] = D[m][n] = D[m + 1][n + 1] = 0;
    D[m + 1][n] = -1;
    iota(B, B + m, n);
    iota(N, N + n, 0);
    N[n] = -1;
}

void pivot(int b, int nb) {
    assert(D[b][nb] != 0);
    ld q = 1. / -D[b][nb];
    D[b][nb] = -1;
    forn (i, n + 2)
        D[b][i] *= q;
    forn (i, m + 2) {
        if (i == b)
            continue;
        ld coef = D[i][nb];
        D[i][nb] = 0;
        forn (j, n + 2)
            D[i][j] += coef * D[b][j];
    }
    swap(B[b], N[nb]);
}

bool betterN(int f, int i, int j) {
    if (eq(D[f][i], D[f][j]))
        return N[i] < N[j];
    return D[f][i] > D[f][j];
}

bool betterB(int nb, int i, int j) {
    ld ai = D[i][n + 1] / D[i][nb];
    ld aj = D[j][n + 1] / D[j][nb];
    if (eq(ai, aj))
        return B[i] < B[j];
    return ai > aj;
}

bool simplex(int phase) {
    int f = phase == 1 ? m : m + 1;
    while (true) {
        int nb = -1;
        forn (i, n + 1) {
            if (N[i] == -1 && phase == 1)
                continue;
            if (nb == -1 || betterN(f, i, nb))
                nb = i;
        }
        if (D[f][nb] <= eps)
            return phase == 1;
        assert(nb != -1);

        int b = -1;
        forn (i, m) {
            if (D[i][nb] >= -eps)
                continue;
            if (b == -1 || betterB(nb, i, b))
                b = i;
        }
        if (b == -1)
            return false;
        pivot(b, nb);
        if (N[nb] == -1 && phase == 2)
            return true;
    }
}

ld solve() {
    int b = -1;
    forn (i, m) {
        if (b == -1 || D[i][n + 1] < D[b][n + 1])
            b = i;
    }
    assert(b != -1);
    if (D[b][n + 1] < -eps) {
        pivot(b, n);
        if (!simplex(2) || D[m + 1][n + 1] < -eps)
            return -infl;
    }
    if (!simplex(1))
        return infl;

    forn (i, n)
        x[i] = 0;
    forn (i, m)
        if (B[i] < n)
            x[B[i]] = D[i][n + 1];

    return D[m][n + 1];
}

} //Simplex
//END_CODE

ld a[maxm][maxn];
ld b[maxm];
ld c[maxn];

int main() {
    #ifdef LOCAL
    assert(freopen("simplex.in", "r", stdin));
    #else
    #endif
    int n, m;
    cin >> n >> m;
    forn (i, m) {
        forn (j, n)
            cin >> a[i][j];
        cin >> b[i];
    }
    forn (i, n)
        cin >> c[i];
    Simplex::init(n, m, a, b, c);
    cout << Simplex::solve() << '\n';
    forn (i, n)
        cerr << Simplex::x[i] << ' ';
    cerr << '\n';
}
