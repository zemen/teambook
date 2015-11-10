#include <iostream>
#include <unordered_set>
#include <set>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cstdlib>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define fore(i, b, e) for (int i = (int)(b); i <= (int)(e); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long i64;
typedef unsigned long long u64;
const int inf = 1e9+100500;
const int maxn = 100500;

struct node {
    int x, y;
    node *l, *r;
    node(int x) : x(x), y(rand()), l(r=NULL) {}
};

void split(node *t, node *&l, node *&r, int x) {
    if (!t) return (void)(l=r=NULL);
    if (x <= t->x) {
        split(t->l, l, t->l, x), r = t;
    } else {
        split(t->r, t->r, r, x), l = t;
    }
}

node *merge(node *l, node *r) {
    if (!l) return r;
    if (!r) return l;
    if (l->y > r->y) {
        l->r = merge(l->r, r);
        return l;
    } else {
        r->l = merge(l, r->l);
        return r;
    }
}

node *insert(node *t, node *n) {
    node *l, *r;
    split(t, l, r, n->x);
    return merge(l, merge(n, r));
}

node *insert(node *t, int x) {
    return insert(t, new node(x));
}

node *fast_insert(node *t, node *n) {
    if (!t) return n;
    node *root = t;
    while (true) {
        if (n->x < t->x) {
            if (!t->l || t->l->y < n->y) {
                split(t->l, n->l, n->r, n->x), t->l = n;
                break;
            } else {
                t = t->l;
            }
        } else {
            if (!t->r || t->r->y < n->y) {
                split(t->r, n->l, n->r, n->x), t->r = n;
                break;
            } else {
                t = t->r;
            }
        }
    }
    return root;
}

node *fast_insert(node *t, int x) {
    return fast_insert(t, new node(x));
}

void print(node* t) {
    if (t) {
        print(t->l);
        printf("%d ", t->x);
        print(t->r);
    }
    fflush(stdout);
}

int main() {
    node *t = NULL;
    unordered_set<int> q;
    forn(i, 1000000) {
        int x = rand();
        q.insert(x);
//         t = insert(t, x);
//         t = fast_insert(t, x);
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
}
