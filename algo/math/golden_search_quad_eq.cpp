#include <bits/stdc++.h>
typedef long double ld;
#define forn(i, n) for (int i = 0; i < int(n); ++i)

//BEGIN_CODE
ld f(ld x) {
    return 5 * x * x + 100 * x + 1; //-10 is minimum
}

ld goldenSearch(ld l, ld r) {
    ld phi = (1 + sqrtl(5)) / 2;
    ld resphi = 2 - phi;
    ld x1 = l + resphi * (r - l);
    ld x2 = r - resphi * (r - l);
    ld f1 = f(x1);
    ld f2 = f(x2);
    forn (iter, 60) {
        if (f1 < f2) {
            r = x2;
            x2 = x1;
            f2 = f1;
            x1 = l + resphi * (r - l);
            f1 = f(x1);
        } else {
            l = x1;
            x1 = x2;
            f1 = f2;
            x2 = r - resphi * (r - l);
            f2 = f(x2);
        }
    }
    return (x1 + x2) / 2;
}

int main() {
    std::cout << goldenSearch(-100, 100) << '\n';
}

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
