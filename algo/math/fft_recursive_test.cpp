// NO_TEAMBOOK
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

const int sz = 1<<20;

int revb[sz];
vector<base> ang[21];

void init(int n) {
    int lg = 0;
    while ((1<<lg) != n) {
        ++lg;
    }
    forn(i, n) {
        revb[i] = (revb[i>>1]>>1)^((i&1)<<(lg-1));
    }

    ld e = M_PI * 2 / n;
    ang[lg].resize(n);
    forn(i, n) {
        ang[lg][i] = { cos(e * i), sin(e * i) };
    }

    for (int k = lg - 1; k >= 0; --k) {
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
        if (rev) w.im *= -1;
        base u = a[i];
        base v = a[i+len] * w;
        a[i] = u + v;
        a[i+len] = u - v;
    }
}

void fft(base *a, int n, bool rev) {
    forn(i, n) {
        int j = revb[i];
        if (i < j) swap(a[i], a[j]);
    }
    int lg = 0;
    while ((1<<lg) != n) {
        ++lg;
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
    int n = 1<<19;
    mt19937 rr(55);
    forn(i, n) a[i] = rr() % 10000;
    forn(j, n) b[j] = rr() % 10000;

    int N = 1;
    while (N < 2*n) N *= 2;

    clock_t start = clock();
    init(N);
    cerr << "init time: " << (clock()-start) / 1000 << " ms" << endl;
    fft(a, N, 0);
    fft(b, N, 0);
    forn(i, N) a[i] = a[i] * b[i];
    fft(a, N, 1);
    clock_t end = clock();

    ld err = 0;
    forn(i, N) {
        err = max(err, (ld)fabsl(a[i].im));
        err = max(err, (ld)fabsl(a[i].re - (i64(a[i].re + 0.5))));
    }

    cerr << "Time: " << (end - start) / 1000 << " ms, err = " << err << endl;
}

int main() {
    test();
}
