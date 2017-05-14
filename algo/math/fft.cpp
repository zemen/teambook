#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
typedef long long i64;
typedef long double ld;

//BEGIN_CODE
const int LG = 20;
typedef complex<ld> base;

vector<base> ang[LG + 5];

void init_fft() {
    int n = 1 << LG;
    ld e = acosl(-1) * 2 / n;
    ang[LG].resize(n);
    forn(i, n)
        ang[LG][i] = polar(ld(1), e * i);

    for (int k = LG - 1; k >= 0; --k) {
        ang[k].resize(1 << k);
        forn(i, 1 << k)
            ang[k][i] = ang[k + 1][i * 2];
    }
}

void fft_rec(base *a, int lg, bool inv) {
    if (lg == 0)
        return;
    int hlen = 1 << (lg - 1);
    fft_rec(a, lg-1, inv);
    fft_rec(a + hlen, lg-1, inv);

    forn (i, hlen) {
        base w = ang[lg][i];
        if (inv)
            w = conj(w);
        base u = a[i];
        base v = a[i + hlen] * w;
        a[i] = u + v;
        a[i + hlen] = u - v;
    }
}

void fft(base *a, int lg, bool inv) {
    int n = 1 << lg;
    int j = 0, bit;
    for (int i = 1; i < n; ++i) {
        for (bit = n >> 1; bit & j; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    fft_rec(a, lg, inv);
    if (inv) {
        forn(i, n)
            a[i] /= n;
    }
}

void test() {
    int lg = 3;
    int n = 1 << lg;
    init_fft();
    base a[] = {1,3,5,2,4,6,7,1};
    fft(a, lg, 0);
    forn(i, n)
        cout << a[i].real() << " ";
    cout << '\n';
    forn(i, n)
        cout << a[i].imag() << " ";
    cout << '\n';
    // 29 -5.82843 -7 -0.171573 5 -0.171573 -7 -5.82843
    // 0 -3.41421 6 0.585786 0 -0.585786 -6 3.41421
}
//END_CODE

