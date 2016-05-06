#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <set>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

typedef long long ll;
typedef long double ldb;

#define forab(i, a, b) for(int i = int(a); i < int(b); ++i)
#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define forba(i, b, a) for(int i = int(b) - 1; i >= int(a); --i)

//BEGIN ALGO
const int MAXN = 200010;
const int MAXK = 26;
const int INF = (int)1e9;

struct node {
    int l, r;
    node *pr, *suf;
    node *to[MAXK];

    node(): l(), r(), pr(), suf() {
        memset(to, 0, sizeof(to));
    }

    node(int l, int r, node *pr): l(l), r(r), pr(pr), suf() {
        memset(to, 0, sizeof(to));
    }
};

node mem[MAXN];
int msz;

node *getNode(int l, int r, node *pr) {
    mem[msz] = node(l, r, pr);
    return &mem[msz++];
}

int n;
char s[MAXN];
int a[MAXN];

node *root, *preRoot;
node *cur;
int pos;

void init() {
    msz = 0;
    preRoot = getNode(-1, -1, NULL);
    root = getNode(-1, 0, preRoot);
    forn(i, MAXK)
        preRoot->to[i] = root;
    root->suf = preRoot;
    cur = root;
    pos = 0;
}

node *add(int i) {
    node *tmp = cur;
    
    if (cur->r == pos) {
        if (!cur->to[a[i]]) {
            cur->to[a[i]] = getNode(i, INF, cur);
            cur = cur->suf;
            pos = cur->r;
            add(i);
            return tmp;
        }
        cur = cur->to[a[i]];
        pos = cur->l;
    }

    if (pos == -1 || a[pos] == a[i]) {
        pos++;
        return tmp;
    }

    tmp = getNode(cur->l, pos, cur->pr);
    cur->pr->to[a[cur->l]] = tmp;
    tmp->to[a[pos]] = cur;
    cur->pr = tmp;
    cur->l = pos;
    tmp->to[a[i]] = getNode(i, INF, tmp);

    pos = tmp->l;
    cur = tmp->pr->suf->to[a[pos]];
    while (tmp->r - pos > cur->r - cur->l) {
        pos += cur->r - cur->l;
        cur = cur->to[a[pos]];
    }

    pos = cur->l + (tmp->r - pos);
    tmp->suf = add(i);
    return tmp;
}

int calc_cnt(node *t) {
    if (!t)
        return 0;

    int cnt = min(n, t->r) - max(0, t->l);
    forn(i, MAXK)
        cnt += calc_cnt(t->to[i]);

    return cnt;
}

int main()
{
    #ifdef LOCAL 
        freopen("input.txt", "r", stdin);
    #endif

    scanf(" %s ", s);
    n = strlen(s);
    forn(i, n)
        a[i] = s[i] - 'a';
    init();

    forn(i, n)
        add(i);

    cout << calc_cnt(root) << '\n';

    return 0;
}
//END ALGO
