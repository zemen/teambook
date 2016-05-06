#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

//BEGIN ALGO
const int MAXY = 1e9;
const int MAXN = 100100;

typedef struct node* pnode;

struct node {
    int num, y, v;
    bool rev;
    pnode p, l, r, path;

    node(int cur) {
        num = 1;
        v = cur;
        y = random(MAXY);
        rev = false;
        v->p = v->l = v->r = v->path = NULL;
    }
};

int opCnt = 0;
int n, m;
pnode a[MAXN];

int random(int a) {
    return 1.0 * rand() / RAND_MAX * a;
}

int calculate(pnode v) {
    return v ? v->num : 0;
}

void calc(pnode v) {
    if (v) {
        v->num = calculate(v->l) + calculate(v->r) + 1;
    }
}

void setReverse(pnode v) {
    if (v) {
        v->rev = !v->rev;
    }
}

pnode next(pnode v) {
    if (v->l) {
        v = v->l;
        bool cur = v->rev;
        while ((v->r && !cur) || (v->l && cur)) {
            if (cur) {
                v = v->l;
            } else {
                v = v->r;
            }
            if (v->rev) {
                cur = !cur;
            }
        }
        return v;
    } else {
        while (v->p) {
            if (v->p->r == v) {
                return v->p;
            }
            v = v->p;
        }
        return NULL;
    }
}

void push(pnode t) {
    if (t && t->rev) {
        swap(t->l, t->r);
        setReverse(t->l);
        setReverse(t->r);
        t->rev = false;
        t->path = next(t);
    }
}

void makeSplit(pnode t, int k, pnode &l, pnode &r) {
    if (!t) {
        l = r = NULL;
    } else {
        push(t);
        int q = calculate(t->l);
        if (k <= q) {
            makeSplit(t->l, k, l, t->l);
            if (t->l) {
                t->l->p = t;
            }
            r = t;
        } else {
            makeSplit(t->r, k - q - 1, t->r, r);
            if (t->r) {
                t->r->p = t;
            }
            l = t;
        }
        calc(l);
        calc(r);
    }
}

void split(pnode t, int k, pnode &l, pnode &r) {
    makeSplit(t, k, l, r);
    if (l) {
        l->p = NULL;
    }
    if (r) {
        r->p = NULL;
    }
}

pnode merge(pnode l, pnode r) {
    if (!l) {
        return r;
    }
    if (!r) {
        return l;
    }
    push(l);
    push(r);
    if (l->y > r->y) {
        l->r = merge(l->r, r);
        l->r->p = l;
        calc(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        r->l->p = r;
        calc(r);
        return r;
    }
}

pnode getRoot(pnode v) {
    if (!v) {
        return NULL;
    }
    while (v->p) {
        v = v->p;
    }
    return v;
}

int nodeIndex(pnode v) {
    int res = 1;
    vector<pnode> path;
    while (v) {
        path.push_back(v);
        v = v->p;
    }
    reverse(path.begin(), path.end());
    for (size_t i = 1; i < path.size(); ++i) {
        pnode cur = path[i - 1], next = path[i];
        push(cur);
        if (next == cur->r) {
            res += calculate(cur->l) + 1;
        }
    }
    push(path.back());
    res += calculate(path.back()->l);
    return res;
}

pnode getNode(pnode t, int n) {
    while (true) {
        push(t);
        int q = calculate(t->l);
        if (n <= q) {
            t = t->l;
        } else if (n > q + 1) {
            n -= q - 1;
            t = t->r;
        } else {
            break;
        }
    }
    return t;
}

void expose(pnode v) {
    pnode a, b, c, t = getRoot(v);
    int k = nodeIndex(v);
    split(t, k, a, b);
    v = getNode(a, 1)->path;
    while (v) {
        k = nodeIndex(v);
        t = getRoot(v);
        split(t, k, b, c);
        a = merge(b, a);
        v = getNode(a, 1)->path;
    }
}

void makeRoot(pnode v) {
    expose(v);
    setReverse(getRoot(v));
}

int get(int u, int v) {
    makeRoot(a[u]);
    expose(a[v]);
    if (getRoot(a[u]) != getRoot(a[v])) {
        return -1;
    } else {
        return getRoot(a[u])->num - 1;
    }
}

void pushPath(pnode v) {
    vector<pnode> path;
    while (v) {
        path.push_back(v);
        v = v->p;
    }
    reverse(path.begin(), path.end());
    for (size_t i = 0; i < path.size(); ++i) {
        push(path[i]);
    }
}

void link(int u, int v) {
    makeRoot(a[u]);
    pushPath(a[u]);
    a[u]->path = a[v];
}

void cut(int u, int v) {
    pushPath(a[u]);
    if (a[u]->path != a[v]) {
        swap(u, v);
    }
    pnode x, y;
    if (getRoot(a[u]) == getRoot(a[v])) {
        split(getRoot(a[u]), nodeIndex(a[v]), x, y);
    }
    pushPath(a[u]);
    a[u]->path = NULL;
}

int main() {
    freopen("linkcut.in", "r", stdin);
    freopen("linkcut.out", "w", stdout);
    srand(time(NULL));
    scanf("%d%d\n", &n, &m);
    for (int i = 0; i < n; ++i) {
        a[i] = new node(i);
    }
    for (int i = 0; i < m; ++i) {
        opCnt = i;
        char cmd[10];
        int u, v;
        scanf("%s %d%d\n", cmd, &u, &v);
        u--, v--;
        if (strcmp(cmd, "get") == 0) {
            printf("%d\n", get(u, v));
        } else if (strcmp(cmd, "link") == 0) {
            link(u, v);
        } else {
            cut(u, v);
        }
    }
    return 0;
}

//END ALGO
