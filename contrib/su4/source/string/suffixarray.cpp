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

#define sqr(a) ((a) * (a))

typedef long long ll;
typedef long double ldb;

//BEGIN ALGO
const int MAXN = 3e5 + 10;
const int MAXK = 26;
const ldb EPS = 1e-10;

int n;
char s[MAXN];
int a[MAXN];

int p[MAXN];
int c[MAXN];
int csz;

int p2[MAXN];
int c2[MAXN];
int cnt[MAXN];

void buildSufArray() {

    csz = MAXK;
    forn(i, n) {
        c[i] = a[i];
        p[i] = i;
    }

    for(int l = 0; l < n; l = (l ? 2 * l : 1)) {
        forn(i, n) {
            p2[i] = p[i] - l;
            if (p2[i] < 0)
                p2[i] += n;
        }

        forn(i, csz)
            cnt[i] = 0;
        forn(i, n)
            cnt[c[p2[i]]]++;
        forab(i, 1, csz)
            cnt[i] += cnt[i - 1];
        forba(i, n, 0)
            p[--cnt[c[p2[i]]]] = p2[i];

        c2[p[0]] = 0;
        csz = 1;
        int prm = p[0] + l;
        if (prm >= n)
            prm -= n;
        forab(i, 1, n) {
            int m = p[i] + l;
            if (m >= n)
                m -= n;

            if (c[p[i]] != c[p[i - 1]] || c[m] != c[prm])
                csz++;

            c2[p[i]] = csz - 1;
            prm = m;
        }
        forn(i, n)
            c[i] = c2[i];
    }

    int pr = 0;
    forn(i, n)
        if (i > 0 && c[p[i]] != c[p[i - 1]]) {
            sort(p + pr, p + i);
            pr = i;
        }
    sort(p + pr, p + n);
}

int lcp[MAXN];
int num[MAXN];

void calcLCP() {
    forn(i, n)
        num[p[i]] = i;

    int len = 0;
    forn(i, n) {
        len = max(0, len - 1);
        if (num[i] == n - 1) {
            len = 0;
            continue;
        }

        int j = p[num[i] + 1];
        while (max(i, j) + len < n && a[i + len] == a[j + len])
            len++;
        lcp[num[i]] = len;
    }
}
//END ALGO
int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);

#endif
     
    return 0;
}

