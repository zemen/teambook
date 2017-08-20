//NO_TEAMBOOK
#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
typedef long long ll;

//BEGIN_CODE
const int mod = 1e9 + 7;
template<typename T>
T add(T x) {
    return x;
}
template<typename T, typename... Ts>
T add(T x, Ts... y) {
    T res = x + add(y...);
    if (res >= mod)
        res -= mod;
    return res;
}
template<typename T, typename... Ts>
T sub(T x, Ts... y) {
    return add(x, mod - add(y...));
}
template<typename T, typename... Ts>
void udd(T &x, Ts... y) {
    x = add(x, y...);
}
template<typename T>
T mul(T x) {
    return x;
}
template<typename T, typename... Ts>
T mul(T x, Ts... y) {
    return (x * 1ll * mul(y...)) % mod;
}
template<typename T, typename... Ts>
void uul(T &x, Ts... y) {
    x = mul(x, y...);
}
int bin(int a, ll deg) {
    int r = 1;
    while (deg) {
        if (deg & 1)
            uul(r, a);
        deg >>= 1;
        uul(a, a);
    }
    return r;
}
int inv(int x) {
    assert(x);
    return bin(x, mod - 2);
}
