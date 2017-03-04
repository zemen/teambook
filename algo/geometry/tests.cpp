#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
typedef long long ll;
#include "primitives.cpp"

//NO_TEAMBOOK

ll N = 1e5;
const int iters = 3e6;
mt19937_64 rr;

ld rnd() {
    return ll(rr()) % (2 * N + 1) - N;
}

pt pp() {
    return pt{rnd(), rnd()};
}

ld pdist(pt p, pt a, pt b) {
    return fabsl((p - a) % (p - b)) / (a - b).abs();
}

ld pdist(pt p, line l) {
    return fabsl(l.signedDist(p));
}

ld cdist(pt p, pt a, ld r) {
    return fabsl((p - a).abs() - r);
}

ld ortogonality(pt a, pt b) {
    return (a * b) / N;
}

ld testLineProjection() {
    pt p = pp();
    pt a = pp();
    pt b = pp();
    pt x = lineProjection(p, a, b);
    ld val = 0;
    val = max(val, pdist(x, a, b));
    val = max(val, ortogonality(x - p, a - b));
    return val / N;
}

ld testLinesIntersection1() {
    pt a = pp();
    pt b = pp();
    pt c = pp();
    pt d = pp();
    line l1(a, b);
    line l2(c, d);
    pt x = linesIntersection(l1, l2);
    if (x.x == 1e18)
        return 0;
    ld val = max(pdist(x, l1), pdist(x, l2));
    return val / N;
}

ld testLinesIntersection2() {
    pt a = pp();
    pt b = pp();
    pt c = pp();
    pt d = pp();
    pt x = linesIntersection(a, b, c, d);
    if (x.x == 1e18)
        return 0;
    ld val = max(pdist(x, a, b), pdist(x, c, d));
    return val / N;
}

ld testLineCircleIntersection() {
    pt a = pp();
    pt b = pp();
    line l(a, b);
    pt c = pp();
    ld r = fabsl(rnd());
    ld val = 0;
    auto pts = lineCircleIntersection(l, c, r);
    for (auto x: pts) {
        ld cval = 0;
        cval = max(cval, cdist(x, c, r));
        cval = max(cval, pdist(x, a, b));
        cval /= N;
        val = max(val, cval);
    }
    return val;
}

ld testCirclesIntersction() {
    pt a = pp();
    pt b = pp();
    ld r1 = fabsl(rnd());
    ld r2 = fabsl(rnd());
    auto pts = circlesIntersction(a, r1, b, r2);
    ld val = 0;
    for (auto x: pts) {
        ld cval = 0;
        cval = max(cval, cdist(x, a, r1));
        cval = max(cval, cdist(x, b, r2));
        cval /= N;
        val = max(val, cval);
    }
    return val;
}

ld testCircleTangents() {
    pt p = pp();
    pt a = pp();
    ld r = fabsl(rnd());
    auto pts = circleTangents(p, a, r);
    ld val = 0;
    for (auto x: pts) {
        ld cval = 0;
        cval = max(cval, cdist(x, a, r));
        cval = max(cval, ortogonality(x - a, x - p));
        cval /= N;
        val = max(val, cval);
    }
    return val;
}

ld testCirclesBitangents() {
    pt a = pp();
    pt b = pp();
    ld r1 = fabsl(rnd());
    ld r2 = fabsl(rnd());
    auto lns = circlesBitangents(a, r1, b, r2);
    ld val = 0;
    for (auto l: lns) {
        ld cval = 0;
        cval = max(cval, fabsl(r1 - pdist(a, l)));
        cval = max(cval, fabsl(r2 - pdist(b, l)));
        cval /= N;
        val = max(val, cval);
    }
    return val;
}

ld worst;


#define RUN(f) \
    worst = 0;                                      \
    for (ll n: {1e1, 1e3, 1e4, 1e5, 1e6, 1e15}) {   \
        N = n;                                      \
        forn (iter, iters)                          \
            worst = max(worst, f());                \
        worst = log(worst) / log(10);               \
        cout << #f << ": 1e" << int(round(log(n) / log(10))) << " -> " << worst << "\n";  \
    }                                               \
    cout << '\n';


int main() {
    cout << fixed;
    cout.precision(1);
    cout << "Relative error test\n\n";

    RUN(testLineProjection);
    RUN(testLinesIntersection1);
    RUN(testLinesIntersection2);
    RUN(testLineCircleIntersection);
    RUN(testCirclesIntersction);
    RUN(testCircleTangents);
    RUN(testCirclesBitangents);
}
