//BEGIN ALGO
typedef complex<double> base;

int rev[MAXN];
base wlen_pw[MAXN];
 
// n - power of 2
void fft(base a[], int n, bool invert) {
    for (int i = 0; i < n; ++i) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    }
 
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        int len2 = len >> 1;
 
        base wlen(cos(ang), sin(ang));
        wlen_pw[0] = base(1, 0);
        for (int i = 1; i < len2; ++i) {
            wlen_pw[i] = wlen_pw[i - 1] * wlen;
        }
 
        for (int i = 0; i < n; i += len) {
            base t,
                *pu = a + i,
                *pv = a + i + len2, 
                *pu_end = a + i + len2,
                *pw = wlen_pw;
            for (; pu != pu_end; ++pu, ++pv, ++pw) {
                t = *pv * *pw;
                *pv = *pu - t;
                *pu += t;
            }
        }
    }
 
    if (invert) {
        for (int i = 0; i < n; ++i) {
            a[i] /= n;
        }
    }
}
 
// n - power of 2, log_n = log2(n)
void calc_rev(int n, int log_n) {
    for (int i = 0; i < n; ++i) {
        rev[i] = 0;
        for (int j = 0; j < log_n; ++j) {
            if (i & (1 << j)) {
                rev[i] |= 1 << (log_n - 1 - j);
            }
        }
    }
}
//END ALGO
