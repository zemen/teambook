#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
typedef long long i64;

typedef double ld;

struct base {
    ld re, im;
    base(){}
    base(ld re) : re(re), im(0) {}
    base(ld re, ld im) : re(re), im(im) {}

    base operator+(const base& o) const { return {re+o.re, im+o.im}; }
    base operator-(const base& o) const { return {re-o.re, im-o.im}; }
    base operator*(const base& o) const {
        return {
            re*o.re - im*o.im,
            re*o.im + im*o.re
        };
    }
};

//BEGIN_CODE
const int maxlg = 20;

vector<base> ang[maxlg + 5];

void init_fft() {
    int n = 1 << maxlg;
    ld e = acosl(-1) * 2 / n;
    ang[maxlg].resize(n);
    forn(i, n) {
        ang[maxlg][i] = { cos(e * i), sin(e * i) };
    }

    for (int k = maxlg - 1; k >= 0; --k) {
        ang[k].resize(1 << k);
        forn(i, 1<<k) {
            ang[k][i] = ang[k+1][i*2];
        }
    }
}

void fft_rec(base *a, int lg, bool rev) {
    if (lg == 0) {
        return;
    }
    int len = 1 << (lg - 1);
    fft_rec(a, lg-1, rev);
    fft_rec(a+len, lg-1, rev);

    forn(i, len) {
        base w = ang[lg][i];
        if (rev) {
            w.im *= -1;
        }
        base u = a[i];
        base v = a[i+len] * w;
        a[i] = u + v;
        a[i+len] = u - v;
    }
}

//n must be power of 2
void fft(base *a, int n, bool rev) {
    int lg = 0;
    while ((1<<lg) != n) {
        ++lg;
    }
    int j = 0, bit;
    for (int i = 1; i < n; ++i) {
        for (bit = n >> 1; bit & j; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    fft_rec(a, lg, rev);
    if (rev) forn(i, n) {
        a[i] = a[i] * (1.0 / n);
    }
}

const int maxn = 1050000;

int n;
base a[maxn];
base b[maxn];

void test() {
    int n = 8;
    init_fft();
    base a[8] = {1,3,5,2,4,6,7,1};
    base b[16];
    fft(b, 16, 0);
    fft(a, n, 0);
    forn(i, n) cout << a[i].re << " "; cout << endl;
    forn(i, n) cout << a[i].im << " "; cout << endl;
    // 29 -5.82843 -7 -0.171573 5 -0.171573 -7 -5.82843
    // 0 -3.41421 6 0.585786 0 -0.585786 -6 3.41421
}
//END_CODE

int main() {
    test();
}
