#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>
#include <cstring>
#include <set>
#include <algorithm>
#include <map>
#include <vector>
#include <cassert>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef long double ldb;

#define forab(i, a, b) for(int i = int(a); i < int(b); ++i)
#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define forba(i, b, a) for(int i = int(b) - 1; i >= int(a); --i)

//BEGIN ALGO
const int MAXN = 1e6 + 10;
const int MAXK = 26 * 2;

struct node {
    node *to[MAXK];
    node *suf, *pr;
    int lst;
    vector<int> num;

    node(): suf(), pr(), lst() {
        num.clear();
        memset(to, 0, sizeof(to));
    }

    node(node *pr, int lst): suf(), pr(pr), lst(lst) {
        num.clear();
        memset(to, 0, sizeof(to));
    }
};

node mem[MAXN];
int msz;

node *getNode(node *pr=NULL, int lst=-1) {
    mem[msz] = (pr ? node(pr, lst) : node());
    return &mem[msz++];
}

node *root;

void init() {
    msz = 0;
    root = getNode();
}

void add(node *t, char *s, int num) {
    if (*s == 0) {
        t->num.push_back(num);
        return;
    }

    int a = (('A' <= *s && *s <= 'Z') ? (*s - 'A') : (*s - 'a' + 26));
    if (!t->to[a])
        t->to[a] = getNode(t, a);
    add(t->to[a], s + 1, num);
}

node *q[MAXN];
int b, e;

void buildSufLinks() {
    b = e = 0;
    
    root->suf = root;
    forn(i, MAXK)
        if (root->to[i])
            q[e++] = root->to[i];
        else
            root->to[i] = root;

    while (b < e) {
        node *t = q[b++];

        if (t->pr == root)
            t->suf = root;
        else
            t->suf = t->pr->suf->to[t->lst];

        forn(i, MAXK)
            if (!t->to[i])
                t->to[i] = t->suf->to[i];
            else
                q[e++] = t->to[i];
    }
}

char s[100010];

int n;
bool ans[1010];
char t[1010];

void solve(node *t, char *s) {
    forn(i, t->num.size())
        ans[t->num[i]] = true;

    if (*s == 0)
        return;

    int a = (('A' <= *s && *s <= 'Z') ? (*s - 'A') : (*s - 'a' + 26));
    solve(t->to[a], s + 1);
}

int main()
{
    #ifdef LOCAL 
        freopen("input.txt", "r", stdin);
    #endif

    int T;
    scanf("%d", &T);
    forn(testNum, T) {
        scanf(" %s %d", s, &n);

        forn(i, n)
            ans[i] = false;

        init();
        forn(i, n) {
            scanf(" %s ", t);
            add(root, t, i);
        }
        buildSufLinks();

        solve(root, s);

        forn(i, n)
            printf(ans[i] ? "y\n" : "n\n");
    }

    return 0;
}

//END ALGO
