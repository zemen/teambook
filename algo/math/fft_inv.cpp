#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
typedef long long ll;
typedef long long i64;
typedef long double ld;
const int inf = int(1e9) + int(1e5);
const ll infl = ll(2e18) + ll(1e10);

#include "fft.cpp"


//BEGIN_CODE
const int M = 1 << LG;
//check: a[0] not zero, lg < LG
//check: to is of length (1 << (lg + 1))
base c[M], d[M], e[M];
void fft_inv(base *a, base *to, int lg) {
    base r0 = base(1) / a[0];
    for (int i = 0; i < (1 << lg); ++i)
        a[i] *= r0;
    fill(to, to + (1 << lg), 0);
    to[0] = 1;

    for (int i = 1; i <= lg; ++i) {
        int n = 1 << i;
        int n2 = 1 << (i + 1);
        int hn = 1 << (i - 1);

        fill(c, c + n2, 0);
        fill(d, d + n2, 0);
        fill(e, e + n2, 0);

        copy(a, a + n, c);
        fft(c, i + 1, false);

        copy(to, to + hn, d);
        fft(d, i + 1, false);

        for (int i = 0; i < n2; ++i)
            e[i] = c[i] * d[i];
        fft(e, i + 1, true);

        //cerr << "i = " << i << endl;
        //assert(abs(e[0] - base(1)) < 1e-9);
        //for (int i = 1; i < hn; ++i)
            //assert(abs(e[i]) < 1e-9);

        for (int i = 0; i < hn; ++i) {
            e[i] = -e[i + hn];
            e[i + hn] = 0;
        }
        for (int i = n; i < n2; ++i)
            e[i] = 0;

        fft(e, i, false);
        for (int i = 0; i < n; ++i)
            e[i] *= d[2 * i];
        fft(e, i, true);
        for (int i = 0; i < hn; ++i)
            to[i + hn] = e[i];

    }
    for (int i = 0; i < (1 << lg); ++i)
        to[i] *= r0;
}
//END_CODE

int main() {
    vector<base> a{1, 0, 1, 0, 0, 0, 0, 0};
    vector<base> b(16);

    init_fft();
    fft_inv(a.data(), b.data(), 3);
    forn (i, 16)
        cerr << roundl(b[i].real()) << ' ';
    cerr << '\n';
}
