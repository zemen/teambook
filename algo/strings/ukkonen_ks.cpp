#include <bits/stdc++.h>

using namespace std;

#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
#define forab(i,a,b) for (int i = int(a); i < int(b); ++i)

typedef long long ll;
typedef long double ld;

const int INF = 1000001000;
const ll INFL = 2000000000000001000;

const int maxc = 26;
const int maxn = 2000000;

typedef int Link;

string s;

struct Node
{
    int l, r;
    Link to[maxc];
    Link par, link;

    Node(int l, int r): l(l), r(r), par(0), link(0)
    {
        memset(to, 0, sizeof(to));
    }

    Node(): Node(0, 0) {}
};

Node t[maxn];
int nodes = 3;
const Link root = 1;
const Link blank = 2;
Link cur = root;
int pos = 0;

Link newNode(int l, int r)
{
    t[nodes] = Node(l, r);
    return nodes++;
}

int charAt(int pos)
{
    return s[pos] - 'a';
}

void setParent(Link u, Link v)
{
    if (v)
        t[v].to[charAt(t[u].l)] = u;
    t[u].par = v;
}

void init()
{
    forn (c, maxc)
        t[blank].to[c] = root;
    t[root].par = t[root].link = t[blank].link = blank;
}

bool canGo(int c)
{
    if (pos == t[cur].r)
        return t[cur].to[c];
    return charAt(pos) == c;
}

void goDown(int l, int r)
{
    while (l < r)
    {
        int delta = min(r - l, t[cur].r - pos);
        pos += delta;
        l += delta;
        if (l >= r)
            break;
        assert(canGo(charAt(l)));
        cur = t[cur].to[charAt(l)];
        pos = min(t[cur].l + 1, t[cur].r);
        ++l;
    }
}

void goUp()
{
    if (pos == t[cur].r && t[cur].link)
    {
        cur = t[cur].link;
        pos = t[cur].r;
        return;
    }
    int l = t[cur].l;
    int r = pos;
    cur = t[t[cur].par].link;
    pos = t[cur].r;
    goDown(l, r);
}

void splitNode()
{
    assert(pos != t[cur].r);
    Link middle = newNode(t[cur].l, pos);
    t[cur].l = pos;
    setParent(middle, t[cur].par);
    setParent(cur, middle);
    cur = middle;
}

void addLeaf(int l)
{
    Link leaf = newNode(l, INF);
    setParent(leaf, cur);
}

void fixLink(Link bad)
{
    if (bad)
        t[bad].link = cur;
}

void addChar(int len)
{
    int c = charAt(len);
    Link badNode = 0;
    while (!canGo(c))
    {
        if (pos != t[cur].r)
        {
            splitNode();
            fixLink(badNode);
            badNode = cur;
        }
        else
        {
            fixLink(badNode);
            badNode = 0;
        }
        addLeaf(len);
        goUp();
    }
    fixLink(badNode);
    goDown(len, len + 1);
}

int main()
{
    init();
    s = "qweqhtkijaeidfhjasdfasdfasdflkjlkjaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaababababababcdcdcdcdabcaac";
    forn (i, sz(s))
        addChar(i);
    return 0;
}
