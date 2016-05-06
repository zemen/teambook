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
#include <iomanip>

using namespace std;

typedef long long ll;
typedef long double ldb;

#define forab(i, a, b) for(int i = int(a); i < int(b); ++i)
#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define forba(i, b, a) for(int i = int(b) - 1; i >= int(a); --i)

//BEGIN ALGO
const int MAXN = 100010;
const int MAXK = 26;
struct node {
    node *to[MAXK];
    node *suf;
    int len;

    node(): suf(), len() {
        memset(to, 0, sizeof(to));
    }

    node(int len): suf(), len(len) {
        memset(to, 0, sizeof(to));
    }
};

node mem[MAXN];
int msz;
node *getNode(int len) {
    mem[msz] = node(len);
    return &mem[msz++];
}

int n;
char s[MAXN];
int a[MAXN];

node *cur;
node *root[2];

void init() {
    msz = 0;
    root[0] = getNode(-1);
    root[1] = getNode(0);
    root[0]->suf = root[1]->suf = root[0];

    cur = root[0];
}

void add(int i) {
    int x = a[i];
    while (i - cur->len - 1 < 0 || a[i - cur->len - 1] != x)
        cur = cur->suf;

    if (!cur->to[x]) {
        cur->to[x] = getNode(cur->len + 2);

        if (cur->to[x]->len == 1) {
            cur->to[x]->suf = root[1];
        } else {
            node *tmp = cur->suf;
            while (a[i - tmp->len - 1] != x)
                tmp = tmp->suf;
            cur->to[x]->suf = tmp->to[x];
        }
    }
    cur = cur->to[x];
}
//END ALGO
int main()
{
    #ifdef LOCAL 
        freopen("input.txt", "r", stdin);
    #endif

    return 0;
}
