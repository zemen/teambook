#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
typedef long long ll;

const int mod = 7340033;
const int root = 2187;

void fft(int *a, int n, bool rev);

int mul(ll a, ll b) {
    return a * b % mod;
}

int sub(int a, int b) {
    return (a + mod - b) % mod;
}

int sum(int a, int b) {
    return (a + b) % mod;
}

int binpow(int a, int deg) {
    int res = 1;
    while (deg) {
        if (deg % 2)
            res = mul(res, a);
        deg /= 2;
        a = mul(a, a);
    }
    return res;
}

//BEGIN_CODE
vector <int> mul(vector <int> a, vector <int> b, 
        bool carry = true) {
    int n = sz(a);
    if (carry) {
        a.resize(n * 2);
        b.resize(n * 2);
    }
    fft(a.data(), a.size(), false);
    fft(b.data(), b.size(), false);
    for (int i = 0; i < sz(a); ++i)
        a[i] = mul(a[i], b[i]);
    fft(a.data(), a.size(), true);
    a.resize(n);
    return a;
}

vector <int> inv(vector <int> v) {
    int n = 1;
    while (n < sz(v))
        n <<= 1;
    v.resize(n, 0);
    vector <int> res(1, binpow(v[0], mod - 2));
    for (int k = 1; k < n; k <<= 1) {
        vector <int> A(k * 2, 0);
        copy(v.begin(), v.begin() + k, A.begin());
        vector <int> C = res;
        C.resize(k * 2, 0);
        A = mul(A, C, false);
        for (int i = 0; i < 2 * k; ++i)
            A[i] = sub(0, A[i]);
        A[0] = sum(A[0], 1);
        for (int i = 0; i < k; ++i)
            assert(A[i] == 0);
        copy(A.begin() + k, A.end(), A.begin());
        A.resize(k);
        vector <int> B(k);
        copy(v.begin() + k, v.begin() + 2 * k, B.begin());
        C.resize(k);
        B = mul(B, C);
        for (int i = 0; i < k; ++i)
            A[i] = sub(A[i], B[i]);
        A = mul(A, C);
        res.resize(k * 2);
        copy(A.begin(), A.end(), res.begin() + k);
    }
    return res;
}
