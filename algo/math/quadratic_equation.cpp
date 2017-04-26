//https://en.wikipedia.org/wiki/Loss_of_significance

#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
#define all(x) (x).begin(), (x).end()
typedef long long ll;
typedef long long i64;
typedef long double ld;
const int inf = int(1e9) + int(1e5);
const ll infl = ll(2e18) + ll(1e10);

const ld eps = 1e-12;
bool ze(ld x) {
    return fabsl(x) < eps;
}

//BEGIN_CODE
vector<ld> sqrRoots(ld a, ld b, ld c) {
    ld d = b * b - 4 * a * c;
    if (ze(d))
        return {-b / (2 * a)};
    if (d < 0)
        return {};
    d = sqrtl(d);
    if (ze(b)) {
        ld x1 = -d / (2 * a);
        ld x2 = d / (2 * a);
        if (x1 > x2)
            swap(x1, x2);
        return {x1, x2};
    }
    ld sgn = b > 0 ? 1 : -1;
    ld x1 = (-b - sgn * d) / (2 * a);
    ld x2 = c / (a * x1);
    if (x1 > x2)
        swap(x1, x2);
    return {x1, x2};
}
//END_CODE

vector<ld> stupid(ld a, ld b, ld c) {
    ld d = b * b - 4 * a * c;
    if (ze(d))
        return {-b / (2 * a)};
    if (d < 0)
        return {};
    d = sqrtl(d);
    ld x1 = (-b - d) / (2 * a);
    ld x2 = (-b + d) / (2 * a);
    if (x1 > x2)
        swap(x1, x2);
    return {x1, x2};
}

void test() {
    ld a = 1;
    ld b = -1.786737601482363;
    ld c = 2.054360090947453e-8;
    cerr.precision(20);

    auto X = sqrRoots(a, b, c);
    //cerr << X[0] << '\n' << X[1] << '\n';
    for (auto x: X)
        cerr << "error " << x * x * a + x * b + c << '\n';

    X = stupid(a, b, c);
    //cerr << X[0] << '\n' << X[1] << '\n';
    for (auto x: X)
        cerr << "error " << x * x * a + x * b + c << '\n';
}

int main() {
    test();
}
