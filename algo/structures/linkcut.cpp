#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for (int i = 0; i < int(n); ++i)

const int maxn = 110000;

//BEGIN CODE
namespace LinkCut {

typedef struct _node {
    _node *l, *r, *p, *pp;
    int size; bool rev;
    _node();

    explicit _node(nullptr_t) {
        l = r = p = pp = this;
        size = rev = 0;
    }
    
    void push() {
        if (rev) {
            l->rev ^= 1; r->rev ^= 1;
            rev = 0; swap(l,r);
        }
    }

    void update();
}* node;

node None = new _node(nullptr);
node v2n[maxn];

_node::_node(){
    l = r = p = pp = None;
    size = 1; rev = false;
}

void _node::update() {
    size = (this != None) + l->size + r->size;
    l->p = r->p = this;
}

void rotate(node v) {
    assert(v != None && v->p != None);
    assert(!v->rev);
    assert(!v->p->rev);
    node u = v->p;
    if (v == u->l)
        u->l = v->r, v->r = u;
    else 
        u->r = v->l, v->l = u;
    swap(u->p,v->p);
    swap(v->pp,u->pp);
    if (v->p != None) {
        assert(v->p->l == u || v->p->r == u);
        if (v->p->r == u)
            v->p->r = v;
        else
            v->p->l = v;
    }
    u->update();
    v->update();
}

void bigRotate(node v) {
    assert(v->p != None);
    v->p->p->push();
    v->p->push();
    v->push();
    if (v->p->p != None) {
        if ((v->p->l == v) ^ (v->p->p->r == v->p))
            rotate(v->p);
        else 
            rotate(v);
    }
    rotate(v);
}

inline void splay(node v) {
    while (v->p != None)
        bigRotate(v);
}

inline void splitAfter(node v) {
    v->push();
    splay(v);
    v->r->p = None;
    v->r->pp = v;
    v->r = None;
    v->update();
}

void expose(int x) {
    node v = v2n[x];
    splitAfter(v);
    while (v->pp != None) {
        assert(v->p == None);
        splitAfter(v->pp);
        assert(v->pp->r == None);
        assert(v->pp->p == None);
        assert(!v->pp->rev);
        v->pp->r = v;
        v->pp->update();
        v = v->pp;
        v->r->pp = None;
    }
    assert(v->p == None);
    splay(v2n[x]);
}

inline void makeRoot(int x) {
    expose(x);
    assert(v2n[x]->p == None);
    assert(v2n[x]->pp == None);
    assert(v2n[x]->r == None);
    v2n[x]->rev ^= 1;
}

inline void link(int x, int y) {
    makeRoot(x);
    v2n[x]->pp = v2n[y];
}

inline void cut(int x, int y) {
    expose(x);
    splay(v2n[y]);
    if (v2n[y]->pp != v2n[x]) {
        swap(x,y);
        expose(x);
        splay(v2n[y]);
        assert(v2n[y]->pp == v2n[x]);
    }
    v2n[y]->pp = None;
}

inline int get(int x, int y) {
    if (x == y)
        return 0;
    makeRoot(x);
    expose(y);
    expose(x);
    splay(v2n[y]);
    if (v2n[y]->pp != v2n[x])
        return -1;
    return v2n[y]->size;
}

}
//END CODE

LinkCut::_node mem[maxn];


int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    forn (i, n)
        LinkCut::v2n[i] = &mem[i];

    forn (i, m) {
        int a, b;
        if (scanf(" link %d %d", &a, &b) == 2)
            LinkCut::link(a - 1, b - 1);
        else if (scanf(" cut %d %d", &a, &b) == 2)
            LinkCut::cut(a - 1, b - 1);
        else if (scanf(" get %d %d", &a, &b) == 2)
            printf("%d\n", LinkCut::get(a - 1, b - 1));
        else
            assert(false);
    }
    return 0;
}
