#include <iostream>
#include <ctime>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define pb push_back
#define fi first
#define se second
#define mp make_pair
typedef pair<int, int> pii;
const int maxn = 100500;
const int maxt = maxn*95/10;
typedef long long i64;

int n;
int x[maxn], y[maxn];
int order[maxn];
int ntr = 0;
int p1[maxt], p2[maxt], p3[maxt];
char del[maxt];
int ch[(int)(maxt*1.7)], nxt[(int)(maxt*1.7)], start[maxt];
int listpos = 1;
void append(int t, int val)
{
    ch[listpos] = val;
    nxt[listpos] = start[t];
    start[t] = listpos++;
}

int root;

int d2(int k) {return x[k]*x[k]+y[k]*y[k];}
int d2(int i, int j) {return (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);}
i64 det2(i64 a, i64 b, i64 c, i64 d) {return a*d-b*c;}
i64 det3(i64 a, i64 b, i64 c, i64 d, i64 e, i64 f, i64 g, i64 h, i64 i) {
    return a*det2(e, f, h, i) + b*det2(f, d, i, g) + c*det2(d, e, g, h);
}
i64 crossprod(int i, int j, int k) {return det2(x[j]-x[i], y[j]-y[i], x[k]-x[i], y[k]-y[i]);}
void normalizeTr(int t) {if (crossprod(p1[t], p2[t], p3[t]) < 0) swap(p1[t], p2[t]);}
void rotateTr(int t) {int p = p1[t]; p1[t]=p2[t]; p2[t]=p3[t]; p3[t]=p;}

const int htsize = maxn*8+13;
int ht1[htsize], ht2[htsize], htval[htsize];
void initht() {forn(i, htsize) ht1[i] = -1;}
int geth(int a, int b) {return abs(a*23427 + b*17263245);}
int& getht(int a, int b)
{
    //cerr << a << " " << b << endl;
    if (a > b) swap(a, b);
    int i = geth(a, b)%htsize;
    while ( !(ht1[i] == -1 || (ht1[i] == a && ht2[i] == b)) )
        i = (i+1)%htsize;
    ht1[i] = a;
    ht2[i] = b;
    //cerr << i << endl;
    return htval[i];
}

void xorIncident(int p1, int p2, int x)
{
    getht(p1, p2) ^= x;
}
int getAnotherTr(int p1, int p2, int t)
{
    return getht(p1, p2) ^ t;
}
int getAnotherPt(int a, int b, int x)
{
    int t = getAnotherTr(a, b, x);
    return (a^b^p1[t]^p2[t]^p3[t]);
}
bool insideCC(int a, int b, int c, int d)
{
    i64 t = det3(x[a]-x[d], y[a]-y[d], d2(a)-d2(d),
                 x[b]-x[d], y[b]-y[d], d2(b)-d2(d),
                 x[c]-x[d], y[c]-y[d], d2(c)-d2(d));    
    return t > 0;
}
bool insideCC(int t, int k) {return insideCC(p1[t], p2[t], p3[t], k);}
bool inside(int t, int k)
{
    return crossprod(p1[t], p2[t], k) >= 0 &&
           crossprod(p2[t], p3[t], k) >= 0 &&
           crossprod(p3[t], p1[t], k) >= 0;
    
}

int localize(int k)
{
    int t = root;
    
    while (start[t])
    {   
        for (int i = start[t]; i; i = nxt[i])
        {
            if (inside(ch[i], k))
            {
                t = ch[i];
                break;
            }
        }
    }
    return t;
}
bool relax(int t)
{
    if (del[t])
        return false;
    forn(i, 3)
    {
        if (p1[t] < n || p2[t] < n)
        {
            int revt = getAnotherTr(p1[t], p2[t], t);
            int revp = getAnotherPt(p1[t], p2[t], t);
            bool statement;
            if (crossprod(p1[t], p2[t], p3[t]) == 0)
                statement = d2(p1[t], p2[t]) > max(d2(p1[t], p3[t]), d2(p2[t], p3[t]));
            else
                statement = insideCC(t, revp);
            if (statement)
            {
                int ntr1 = ntr++, ntr2 = ntr++;
                
                xorIncident(p1[t], p3[t], t^ntr1);
                xorIncident(p1[t], revp, revt^ntr1);
                xorIncident(p3[t], p2[t], t^ntr2);
                xorIncident(p2[t], revp, revt^ntr2);
                xorIncident(p3[t], revp, ntr1^ntr2);
                
                p1[ntr1] = p1[t]; p2[ntr1] = revp; p3[ntr1] = p3[t]; normalizeTr(ntr1);
                p1[ntr2] = p2[t]; p2[ntr2] = revp; p3[ntr2] = p3[t]; normalizeTr(ntr2);
                
                del[t] = del[revt] = 1;
                append(t, ntr1); append(t, ntr2);
                append(revt, ntr1); append(revt, ntr2);
                
                relax(ntr1);
                relax(ntr2);
                
                return true;
            }
        }
        rotateTr(t);
    }
    return false;
}
void insert(int t, int k)
{
    int n1 = ntr++, n2 = ntr++, n3 = ntr++;
    xorIncident(p1[t], p2[t], t^n1); p1[n1] = p1[t]; p2[n1] = p2[t]; p3[n1] = k; append(t, n1); normalizeTr(n1);
    xorIncident(p1[t], p3[t], t^n2); p1[n2] = p1[t]; p2[n2] = p3[t]; p3[n2] = k; append(t, n2); normalizeTr(n2);
    xorIncident(p2[t], p3[t], t^n3); p1[n3] = p2[t]; p2[n3] = p3[t]; p3[n3] = k; append(t, n3); normalizeTr(n3);
    assert(getAnotherTr(p1[t], k, 0) == 0);
    assert(getAnotherTr(p2[t], k, 0) == 0);
    assert(getAnotherTr(p3[t], k, 0) == 0);
    xorIncident(p1[t], k, n1^n2);
    xorIncident(p2[t], k, n1^n3);
    xorIncident(p3[t], k, n2^n3);
    del[t] = 1;
    relax(n1); relax(n2); relax(n3);
}

void triangulate()
{
    initht();
    forn(i, n) order[i] = i;
    random_shuffle(order, order+n);
    
    int mx = 0;
    forn(i, n) mx = max(mx, max(x[i], y[i]));
    x[n] = y[n] = y[n+1] = x[n+2] = -1;
    x[n+1] = y[n+2] = mx*2+5;
    
    ntr = 1;
    listpos = 1;
    forn(i, maxt) start[i] = del[i] = p1[i] = p2[i] = p3[i] = 0;
    p1[0] = n; p2[0] = n+1; p3[0] = n+2;
    
    forn(i, n)
        insert(localize(order[i]), order[i]);
}
int p[maxn];
void init() {forn(i, maxn) p[i] = i;}
int get(int x) {return x == p[x] ? x : (p[x] = get(p[x]));}
bool unite(int x, int y)
{
    x = get(x), y = get(y);
    if (x == y) return false;
    p[x] = y;
    return true;
}

vector<pii> e[maxn];
int pd[maxn][18];
int mxd[maxn][18];
int h[maxn];
int m;
int u[maxn], v[maxn];

void dfs(int v, int anc)
{
    forn(i, e[v].size())
    {
        int to = e[v][i].fi;
        if (to != anc)
        {
            h[to] = h[v] + 1;
            pd[to][0] = v;
            mxd[to][0] = e[v][i].se;
            dfs(to, v);
        }
    }
}

int query(int u, int v)
{
    int mx = 0;
    for (int k = 17; k >= 0; --k)
    {
        if (h[pd[u][k]] >= h[v])
            mx = max(mx, mxd[u][k]), u = pd[u][k];
        if (h[pd[v][k]] >= h[u])
            mx = max(mx, mxd[v][k]), v = pd[v][k];
    }
    if (u == v)
        return mx;
    for (int k = 17; k >= 0; --k)
        if (pd[u][k] != pd[v][k])
        {
            mx = max(mx, max(mxd[u][k], mxd[v][k]));
            u = pd[u][k];
            v = pd[v][k];
        }
    return max(mx, max(mxd[u][0], mxd[v][0]));
}

void buildGraph()
{
    vector<pair<int, pii> > a;
    forn(i, ntr) if (!del[i])
    {
        a.pb(mp(d2(p1[i], p2[i]), mp(p1[i], p2[i])));
        a.pb(mp(d2(p1[i], p3[i]), mp(p1[i], p3[i])));
        a.pb(mp(d2(p3[i], p2[i]), mp(p3[i], p2[i])));
    }
    sort(a.begin(), a.end());
    init();
    forn(i, a.size())
    {
        int u = a[i].se.fi, v = a[i].se.se, w = a[i].fi;
        if (u < n && v < n && unite(u, v))
        {
            e[u].pb(mp(v, w));
            e[v].pb(mp(u, w));
        }
    }
}

void initLCA()
{
    forn(k, 18) if (k)
        forn(i, n)
        {
            pd[i][k] = pd[pd[i][k-1]][k-1];
            mxd[i][k] = max(mxd[i][k-1], mxd[pd[i][k-1]][k-1]);
        }
}

void solve()
{
    triangulate();
    cerr << "time = " << clock() << " ms" << endl;
    buildGraph();
    dfs(0, -1);
    initLCA();
    
    forn(i, m)
        printf("%.10lf\n", sqrt((double)query(u[i], v[i])));
        
    cerr << "time = " << clock() << " ms" << endl;
}

void gen()
{
    fstream cout("input.txt", ios::out);
    int n = 100000, q = 100000, maxc = 10000;
    vector<pii> a;
    forn(i, n)
        a.pb(mp(rand()%maxc, rand()%maxc));
    sort(a.begin(), a.end());
    a.resize(unique(a.begin(), a.end()) - a.begin());
    n = a.size();
    cout << a.size() << endl;
    forn(i, a.size())
        cout << a[i].fi << " " << a[i].se << endl;
    cout << q << endl;
    forn(i, q)
        cout << rand()%n+1 << " " << rand()%n+1 << endl;
}

void scan()
{
    scanf("%d", &n);
    forn(i, n)
        scanf("%d%d", &x[i], &y[i]);
    scanf("%d", &m);
    forn(i, m)
        scanf("%d%d", &u[i], &v[i]), --u[i], --v[i];
}

int main()
{
    //gen(); 
    
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    freopen("caravans.in", "r", stdin);
    freopen("caravans.out", "w", stdout);
    
    scan();
    solve();

    return 0;
}
