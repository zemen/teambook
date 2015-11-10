#include <iostream>
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

struct node;
void updson(node* p, node* v, node* was);

struct node {
    int val;
    node *l, *r, *p;
    node() {}
    node(int val) : val(val), l(r=p=NULL) {}

    bool isRoot() const { return !p; }
    bool isRight() const { return p && p->r == this; }
    bool isLeft() const { return p && p->l == this; }
    void setLeft(node* t) {
        if (t) t->p = this;
        l = t;
    }
    void setRight(node *t) {
        if (t) t->p = this;
        r = t;
    }
};

void updson(node *p, node *v, node *was) {
    if (p) {
        if (p->l == was) p->l = v;
        else p->r = v;
    }
    if (v) v->p = p;
}

void rightRotate(node *v) {
    assert(v && v->l);
    node *u = v->l;
    node *p = v->p;
    v->setLeft(u->r);
    u->setRight(v);
    updson(p, u, v);
}

void leftRotate(node *v) {
    assert(v && v->r);
    node *u = v->r;
    node *p = v->p;
    v->setRight(u->l);
    u->setLeft(v);
    updson(p, u, v);
}

void splay(node *v) {
    while (v->p) {
        if (!v->p->p) {
            if (v->isLeft()) rightRotate(v->p);
            else leftRotate(v->p);
        } else if (v->isLeft() && v->p->isLeft()) {
            rightRotate(v->p->p);
            rightRotate(v->p);
        } else if (v->isRight() && v->p->isRight()) {
            leftRotate(v->p->p);
            leftRotate(v->p);
        } else if (v->isLeft()) {
            rightRotate(v->p);
            leftRotate(v->p);
        } else {
            leftRotate(v->p);
            rightRotate(v->p);
        }
    }
    v->p = NULL;
}

node *insert(node *t, node *n) {
    if (!t) return n;
    int x = n->val;
    while (true) {
        if (x < t->val) {
            if (t->l) {
                t = t->l;
            } else {
                t->setLeft(n);
                t = t->l;
                break;
            }
        } else {
            if (t->r) {
                t = t->r;
            } else {
                t->setRight(n);
                t = t->r;
                break;
            }
        }
    }
    splay(t);
    return t;
}

void print(node* t) {
    if (t) {
        if (t->l) assert(t->l->p == t);
        if (t->r) assert(t->r->p == t);
        print(t->l);
        printf("%d ", t->val);
        print(t->r);
    }
    fflush(stdout);
}

void printCool(node* t, int d = 0) {
    if (t) {
        if (d == 0) assert(!t->p);
        if (t->l) assert(t->l->p == t);
        if (t->r) assert(t->r->p == t);
        printCool(t->r, d+2);
        cout << string(d, ' ') << t->val << endl;
        printCool(t->l, d+2);
    }
}

node *insert(node *t, int x) {
    return insert(t, new node(x));
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif

    node *t = NULL;
    forn(i, 1000000) {
        int x = rand();
        t = insert(t, x);
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
