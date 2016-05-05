#pragma comment (linker, "/STACK:32111111")
#define _CRT_SECURE_NO_DEPRECATE
#include <map>
#include <cassert>
#include <vector>
#include <complex>
#include <deque>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

typedef vector<int> vi;
typedef long long i64;
typedef i64 ll;

#define sz(a) ((int)(a).size())

const double PI = acos(-1.0);

template<typename T> struct TPoint2D {
    T X, Y;
    TPoint2D() : X(), Y() {}
    TPoint2D(const T& x, const T& y) : X(x), Y(y) {}
    TPoint2D(const TPoint2D<T>& p) : X(p.X), Y(p.Y) {}
    TPoint2D& operator=(const TPoint2D<T>& p) { X = p.X; Y = p.Y; return *this; }
    T operator&(const TPoint2D<T>& p) const { return X * p.X + Y * p.Y; }
    T operator^(const TPoint2D<T>& p) const { return X * p.Y - Y * p.X; }
    TPoint2D conj() const { return TPoint2D(X, -Y); }
    TPoint2D<T> operator*(const TPoint2D<T>& p) const { return TPoint2D<T>(*this & p.conj(), -*this ^ p.conj()); }
    TPoint2D<T> operator*(const T& p) const { return TPoint2D<T>(p * X, p * Y); }
    TPoint2D<T> operator-(void) const { return TPoint2D(-X, -Y); }
    TPoint2D<T> operator+(const TPoint2D<T>& p) const { return TPoint2D(X + p.X, Y + p.Y); }
    TPoint2D<T> operator-(const TPoint2D<T>& p) const { return *this + (-p); }
    T norm() const { return X * X + Y * Y; }
};

typedef TPoint2D<double> base;

template<typename T> TPoint2D<T> operator*(const T& p1, const TPoint2D<T>& p2) { return p2 * p1; }

bool inside_simple_polygon(ll x0, ll y0, const vl &x, const vl &y) {
  int cnt = 0;
  int n = x.size();
  for (int j = 0; j < x.size(); ++j) {
    ll x1 = x[j], x2 = x[(j+1)%n], y1 = y[j], y2 = y[(j+1)%n];
    if (y1 > y2) {
      swap(x1, x2);
      swap(y1, y2);
    }
    if (y1 == y0 && y2 > y0 && x1 >= x0) ++cnt;
    if (y1 >= y0 || y2 <= y0) {
      continue;
    }
    if ((x0 - x1) * (y2 - y1) < (y0 - y1) * (x2 - x1)) ++cnt;
  }
  return (cnt % 2);
}

// superfast next permutation for bit masks

int next_perm(int prev_combo) {
    int lowest_1_bit = prev_combo & -prev_combo;
    int tmp = prev_combo + lowest_1_bit;
    return (((prev_combo ^ tmp) >> 2) / lowest_1_bit) | tmp;
}

//////////////
/// ìàñêè ñ ïîäìàñêàìè

void maskiter(int n) {
    for (int m=0; m<(1<<n); ++m)
        for (int s=m; s; s=(s-1)&m)
            ;//... èñïîëüçîâàíèå s è m ...
}


///////////////////////////
// fast Fourier transform

void fft (vector<base>& a, bool invert) {
    int n = (int) a.size();
    for (int i=1, j=0; i<n; ++i) {
        int bit = n >> 1;
        for (; j>=bit; bit>>=1)
            j -= bit;
        j += bit;
        if (i < j)
            swap (a[i], a[j]);
    }
    for (int len=2; len<=n; len<<=1) {
        double ang = 2*PI/len * (invert ? -1 : 1);
        base wlen (cosl(ang), sinl(ang));
        for (int i=0; i<n; i+=len) {
            base w (1, 0);
            for (int j=0; j<len/2; ++j) {
                base u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
		if (j % 64 == 0) w = base(cosl(ang*j), sinl(ang*j));
                w = w*wlen;
            }
        }
    }
    if (invert)
        for (int i=0; i<n; ++i)
            a[i] = a[i] * (1.0 / n);
}
vi mul(const vi & a, const vi & b) {
    int n = 1;
    while (n < a.size() + b.size()) n *= 2;
    vector<base> x(n), y(n);
    for (int i = 0; i < a.size(); ++i) x[i] = base(a[i], 0);
    for (int i = 0; i < b.size(); ++i) y[i] = base(b[i], 0);
    fft(x, 0);
    fft(y, 0);
    for (int i = 0; i < x.size(); ++i) x[i] = x[i] * y[i];
    fft(x, 1);
    vi res(a.size()+b.size());
    for (int i = 0; i < res.size(); ++i) res[i] = round(x[i].X);
    return res;
}

int g;
int root = 1;
int root_1 = inv(root);
int root_pw = 0;
const int max_root_pw = 0;
int W[2][max_root_pw];
void precalcw() {
    for (g = 2; g < mod - 1; ++g) {
        if (mpow(g, (mod - 1) / 25) != 1 && mpow(g, (mod - 1) / 2) != 1) {
            break;
        }
    }
    root = mpow(g, (mod - 1) / root_pw);
    root_1 = inv(root);
    unsigned long long r[2] = {root, root_1};
    for (int t = 0; t < 2; ++t) {
        W[t][0] = 1;
        for (int i = 1; i < root_pw; ++i) {
            W[t][i] = W[t][i-1] * r[t] % mod;
        }
    }
}
void fft (vector<int> & a, int invert) {
	int n = (int) a.size();
    if (n != root_pw) {
        root_pw = n;
        precalcw();
    }
    for (int i = 0; i < n; ++i) if (a[i] < 0) a[i] += mod;
 
	for (int i=1, j=0; i<n; ++i) {
		int bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}
 
	for (int len=2, t = n/len; len<=n; len<<=1, t/=2) {
		for (int i=0; i<n; i+=len) {
			for (int j=0, pw = 0; j<len/2; ++j, pw += t) {
				int u = a[i+j];
                int v = a[i+j+len/2] * (unsigned long long)W[invert][pw] % mod;
				a[i+j] = dw(u+v, mod);
				a[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
			}
		}
	}
	if (invert) {
		unsigned long long nrev = inv(n);
		for (int i=0; i<n; ++i)
			a[i] = a[i] * nrev % mod;
	}
}


//////////////////////
/// basic string algorithms

vi prefixFunction(string s) {
    vi res(sz(s), 0);
    for (int i = 1; i < sz(s); ++i) {
        int cur = res[i-1];
        while (cur && s[cur] != s[i])
            cur = res[cur];
        if (s[cur] == s[i])
            ++cur;
        res[i] = cur - 1;
    }
    return res;
}

vi zfunc(string s) {
    vi res(sz(s), 0);
    int l = 0, r = 0;
    for (int i = 1; i < sz(s); ++i) {
        if (i + res[i - l] <= r)
            res[i] = res[i-l];
        else {
            l = i;
            r = max(r, i);
            while (r < sz(s)) {
                if (s[r] != s[r-l]) break;
                ++r;
            }
            res[i] = r - l;
            --r;
        }
    }
    return res;
}



////////////////////////
//// Suffix array O(N * log N)

void sufarray() { // cyclic suffix sort
    char *s = "aaabaababa"; // âõîäíàÿ ñòðîêà
    int n = (int)strlen(s); // äëèíà ñòðîêè
 
    // êîíñòàíòû
    const int maxlen = int(1e5); // ìàêñèìàëüíàÿ äëèíà ñòðîêè
    const int alphabet = 256; // ðàçìåð àëôàâèòà, <= maxlen
    int p[maxlen], cnt[maxlen], c[maxlen];
    memset (cnt, 0, alphabet * sizeof(int));
    for (int i=0; i<n; ++i)
        ++cnt[s[i]];
    for (int i=1; i<alphabet; ++i)
        cnt[i] += cnt[i-1];
    for (int i=0; i<n; ++i)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i=1; i<n; ++i) {
        if (s[p[i]] != s[p[i-1]])  ++classes;
        c[p[i]] = classes-1;
    }

    int pn[maxlen], cn[maxlen];
    /* // This is used for LCP without additional memory
     * int lcp[maxlen], lcpn[maxlen], lpos[maxlen], rpos[maxlen];
     * memset (lcp, 0, sizeof lcp);
     */
    for (int h=0; (1<<h)<n; ++h) {
        /*
         * for (int i=0; i<n; ++i)
         * rpos[c[p[i]]] = i;
         * for (int i=n-1; i>=0; --i)
         *     lpos[c[p[i]]] = i;
         */
        for (int i=0; i<n; ++i) {
            pn[i] = p[i] - (1<<h);
            if (pn[i] < 0)  pn[i] += n;
        }
        memset (cnt, 0, classes * sizeof(int));
        for (int i=0; i<n; ++i)
            ++cnt[c[pn[i]]];
        for (int i=1; i<classes; ++i)
            cnt[i] += cnt[i-1];
        for (int i=n-1; i>=0; --i)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i=1; i<n; ++i) {
            int mid1 = (p[i] + (1<<h)) % n,  mid2 = (p[i-1] + (1<<h)) % n;
            if (c[p[i]] != c[p[i-1]] || c[mid1] != c[mid2])
                ++classes;
            cn[p[i]] = classes-1;
        }
        /*
         * rmq_build (lcp, n-1);
         * for (int i=0; i<n-1; ++i) {
         *     int a = p[i],  b = p[i+1];
         *     if (c[a] != c[b])
         *         lcpn[i] = lcp[rpos[c[a]]];
         *     else {
         *         int aa = (a + (1<<h)) % n,  bb = (b + (1<<h)) % n;
         *         lcpn[i] = (1<<h) + rmq (lpos[c[aa]], rpos[c[bb]]-1);
         *         lcpn[i] = min (n, lcpn[i]);
         *     }
         * }
         * memcpy (lcp, lcpn, (n-1) * sizeof(int));
         */
        memcpy (c, cn, n * sizeof(int));
    }

    /* lcp with additional memory:
    int lcp (int i, int j) {
        int ans = 0;
        for (int k=log_n; k>=0; --k)
            if (c[k][i] == c[k][j]) {
                ans += 1<<k;
                i += 1<<k;
                j += 1<<k;
            }
        return ans;
    }
    */
}




/////////////////////
/// Suffix automata construction (O(N))

namespace SufAutomataBuilder {
    static const int MAXLEN = 100000; // ìàêñèìàëüíàÿ äëèíà ñòðîêè
    static const int K = 26; // ðàçìåð àëôàâèòà

    struct state {
        int length, link;
        int next[K];
        bool termimal;
    };

    state st[MAXLEN*2-1];
    int sz, last;

    void init() {
        /*
        // ýòè äåéñòâèÿ íóæíû, åñëè àâòîìàò ñòðîèòñÿ íåñêîëüêî ðàç äëÿ ðàçíûõ ñòðîê:
        sz = last = 0;
        for (int i=0; i<MAXLEN*2-1; ++i)
        st[i].terminal = false;
        st[0].length = 0;
        */
        st[0].link = -1;
        memset (st[0].next, -1, sizeof st[0].next);
        ++sz;
    }

    void sa_extend (char c) {
        int nlast = sz++;
        st[nlast].length = st[last].length + 1;
        memset (st[nlast].next, -1, sizeof st[nlast].next);
        int p;
        for (p=last; p!=-1 && st[p].next[c]==-1; p=st[p].link)
            st[p].next[c] = nlast;
        if (p == -1)
            st[nlast].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].length + 1 == st[q].length)
                st[nlast].link = q;
            else {
                int clone = sz++;
                st[clone].length = st[p].length + 1;
                memcpy (st[clone].next, st[q].next, sizeof st[clone].next);
                st[clone].link = st[q].link;
                for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
                    st[p].next[c] = clone;
                st[q].link = st[nlast].link = clone;
            }
        }
        last = nlast;
    }

    void mark_terminal() {
        for (int p=last; p!=-1; p=st[p].link)
            st[p].termimal = true;
    }
};

vi euler(const vii & edges, int n) {
    vector < vector<int> > gr (n);
    vector < vector<int> > gre (n);
    for (int i = 0; i < edges.size(); ++i) {
        int a = edges[i].first, b = edges[i].second;
        gr[a].push_back(b);
        gr[b].push_back(a);
        gre[a].push_back(i);
        gre[b].push_back(i);
    }
    vi res;
    vi used(edges.size());
    vi it(n);
    int first = 0;
    stack<int> st;
    st.push (first);
    while (!st.empty())
    {
        int v = st.top();
        for (; it[v] < gr[v].size(); ++it[v])
            if (used[gre[v][it[v]]] == 0)
                break;
        if (it[v] == gr[v].size())
        {
            res.push_back (v);
            st.pop();
        }
        else
        {
            used[gre[v][it[v]]] = 1;
            st.push (gr[v][it[v]]);
        }
    }
    return res;
}

//centroid
vi far(int v0) {
    vi q(1, v0);
    unordered_map<int, int> pr; // careful
    pr[v0] = -1;
    for (int it = 0; it < q.size(); ++it) {
        int v = q[it];
        for (int i = 0; i < gr[v].size(); ++i) {
            int nv = gr[v][i];
            if (pr.count(nv)) continue;
            pr[nv] = v;
            q.push_back(nv);
        }
    }
    vi res;
    int cur = q.back();
    while (cur >= 0) {
        res.push_back(cur);
        cur = pr[cur];
    }
    return res;
}
int center(int v) {
    vi p1 = far(v);
    vi p2 = far(p1[0]);
    return p2[p2.size() / 2];
}

///////////////////////////
//// Sat-2 full

namespace SAT2 {
    int n;
    vector < vector<int> > g, gt;
    vector<bool> used;
    vector<int> order, comp;

    void dfs1 (int v) {
        used[v] = true;
        for (size_t i=0; i<g[v].size(); ++i) {
            int to = g[v][i];
            if (!used[to])
                dfs1 (to);
        }
        order.push_back (v);
    }

    void dfs2 (int v, int cl) {
        comp[v] = cl;
        for (size_t i=0; i<gt[v].size(); ++i) {
            int to = gt[v][i];
            if (comp[to] == -1)
                dfs2 (to, cl);
        }
    }

    int solve() {
        // ÷òåíèå n, ãðàôà g, ïîñòðîåíèå ãðàôà gt ...

        used.assign (n, false);
        for (int i=0; i<n; ++i)
            if (!used[i])
                dfs1 (i);

        comp.assign (n, -1);
        for (int i=0, j=0; i<n; ++i) {
            int v = order[n-i-1];
            if (comp[v] == -1)
                dfs2 (v, j++);
        }

        for (int i=0; i<n; ++i)
            if (comp[i] == comp[i^1]) {
                puts ("NO SOLUTION");
                return 0;
            }
        for (int i=0; i<n; ++i) {
            int ans = comp[i] > comp[i^1] ? i : i^1;
            printf ("%d ", ans);
        }
        return 0;
    }
}


/////////////////////
// íåÿâíîå äåêàðòîâî äåðåâî ñ äîñòóïîì ïî íîìåðó è ìóëüòèîïåðàöèÿìè (çäåñü - reverse)

typedef struct item * pitem;
struct item {
    int prior, value, cnt;
    bool rev;
    pitem l, r;
};

int cnt (pitem it) {
    return it ? it->cnt : 0;
}

void upd_cnt (pitem it) {
    if (it)
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void push (pitem it) {
    if (it && it->rev) {
        it->rev = false;
        swap (it->l, it->r);
        if (it->l)  it->l->rev ^= true;
        if (it->r)  it->r->rev ^= true;
    }
}

void merge (pitem & t, pitem l, pitem r) {
    push (l);
    push (r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd_cnt (t);
}

void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t)
        return void( l = r = 0 );
    push (t);
    int cur_key = add + cnt(t->l);
    if (key <= cur_key)
        split (t->l, l, t->l, key, add),  r = t;
    else
        split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    upd_cnt (t);
}

void reverse (pitem t, int l, int r) {
    pitem t1, t2, t3;
    split (t, t1, t2, l);
    split (t2, t2, t3, r-l+1);
    t2->rev ^= true;
    merge (t, t1, t2);
    merge (t, t, t3);
}

void output (pitem t) {
    if (!t)  return;
    push (t);
    output (t->l);
    printf ("%d ", t->value);
    output (t->r);
}


namespace CPPBigInt {

    const int BASE = (int)1e9;

    vi sum(const vi &x, const vi &y) {
        vi res;
        int b = 0;
        for (size_t i = 0; i < max(x.size(), y.size()); ++i) {
            if (i < x.size()) b += x[i];
            if (i < y.size()) b += y[i];
            res.push_back(b % BASE);
            b /= BASE;
        }
        if (b > 0) res.push_back(b);
        return res;
    }

    vi mul (const vi &x, const vi &y) {
        vi res(x.size() + y.size() - 1);
        long long b = 0;
        for (size_t i = 0; i < res.size(); ++i) {
            res[i] = (int) b;
            for (int j = max<int>(0, i - (int)y.size() + 1); j <= min<int>(i, (int)x.size() - 1); ++j) {
                res[i] += x[j] * y[i - j];
            }
            b = res[i] / BASE;
            res[i] = res[i] % BASE;
        }
        if (b)
            res.push_back((int)b);
        return res;
    }

    bool less(vi & x, vi & y) //or equal
    {
        while (!x.empty() && x.back() == 0)
            x.pop_back();
        while (!y.empty() && y.back() == 0)
            y.pop_back();
        if (x.size() < y.size())
            return true;
        if (x.size() > y.size())
            return false;
        for (int i = x.size() - 1; i >= 0; --i) {
            if (x[i] < y[i])
                return true;
            if (x[i] > y[i])
                return false;
        }
        return true;
    }

    void out (vi &x) {
        while (!x.empty() && x.back() == 0)
            x.pop_back();
        if (x.empty())
            printf("0");
        for (size_t i = 0; i < x.size(); ++i)
            printf("%09d", x[x.size() - 1 - i]);
        printf("\n");
    }

    vi tovi(long long n) {
        vi res;
        while(n) {
            res.push_back(n % BASE);
            n /= BASE;
        }
        return res;
    }
}


void eratosphen1(int N) {
    vector<char> erat(N, true);
    erat[0] = erat[1] = false;
    for (int i = 2; i * i < N; ++i) if (erat[i]) {
        for (int j = 2 * i; j < N; j += i)
            erat[j] = false;
    }
    vector<int> primes;
    for (int i = 0; i < N; ++i) if (erat[i])
        primes.push_back(i);
}
        

void eratosphen2(int N) {
    vector<int> erat(N, 0);
    erat[0] = erat[1] = 1;
    vector<int> primes;
    for (size_t i = 2; i < erat.size(); ++i) {
        if (!erat[i]) {
            primes.push_back(i);
            erat[i] = i;
        }
        for (size_t it = 0; it < primes.size() && primes[it] <= erat[i]; ++it) {
            ll next = primes[it] * (ll)i;
            if (next > erat.size()) {
                break;
            } else erat[next] = primes[it];
        }
    }
}

vl GetFactors (const vii & primeFactors, const vl & maxPows) {
	// in primeFactors: (p_i, k_i), in maxPows: p_i^{k_i}
	int m = primeFactors.size();
	vi curPows(m);
	ll curFactor = 1;
	vl factors;
	while (true) {
		factors.push_back(curFactor);
		int i;
		for (i = 0; i < m && curPows[i] == primeFactors[i].second; i++) {
			curFactor /= maxPows[i];
			curPows[i] = 0;
		}
		if (i == m)
			break;
		curFactor *= primeFactors[i].first;
		++curPows[i];
	}
	sort(factors.begin(), factors.end());
	return factors;
}


/// Generation of pifagorian triples less than N
void pifGen(int N) {
    for (int u = 1; u * u * 2 < N; ++u) {
        for (int v = u + 1; v * v <= N - u * u; v += 2) if (gcd(u, v) == 1) {
            for (int k = 1; k <= N / (v * v + u * u); ++k) {
                //do smthg with: k * (v * v - u * u),  k * 2 * v * u,  k * (v * v + u * u)
            }
        }
    }
}

int mpow (long long x, long long n, int mod) {
    long long res = 1;
    while (n) {
        if (n % 2)
            res = (res * x) % mod;
        n /= 2;
        x = (x * x) % mod;
    }
    return (int)res;
}

int TonShanks (int rem, int p) {
    if (p % 4 == 3)
        return mpow(rem, (p + 1) / 4, p);
    int s = 0;
    int Q = p - 1;
    while (!(Q % 2)) {
        ++s;
        Q /= 2;
    }
    long long z = 2;
    while (mpow(z, (p - 1) / 2, p) == 1)
        ++z;
    long long c = mpow(z, Q, p);
    long long R = mpow(rem, (Q + 1) / 2, p);
    long long t = mpow(rem, Q, p);
    int M = s;
    while (t != 1) {
        long long i = 0, T = t;
        while (T != 1) {
            ++i;
            T = (T * T) % p;
        }
        long long b = mpow(c, 1 << (M - i - 1), p);
        R = (R * b) % p;
        c = (b * b) % p;
        t = (c * t) % p;
        M = (int)i;
    }
    return (int)R;
}

ll up (ll x, ll m) {
    if (x >= 0)
    return x;
    else return x + m;
}


void SolveDiophantEquation (ll a, ll b, ll c, ll MAX = 1e18L) {
    ll a1 = abs(a), b1 = abs(b);
    if (a == 0 && b == 0) {
        //        SOLUTION: printf("0 0\n");
        return;
    }
    ll xa=1,ya=0,xb=0,yb=1;
    while (b1) {
        ll t = a1 / b1;
        a1 -= t * b1;
        xa -= t * ya;
        xb -= t * yb;
        swap(a1, b1);
        swap(xa, ya);
        swap(xb, yb);
    }
    if (c % a1) {;
    //           NO SOLUTION!
    } else {
        c /= a1;
        a /= a1;
        b /= a1;
        xa *= c;
        if (a < 0)
            xa *= -1;
        xb *= c;
        if (b < 0)
            xb *= -1;
        int zn = -1;
        if (abs(xa) > MAX) {
            if (xa < 0)
                zn *= -1;
            ll t = (abs(xa) + abs(b) - MAX) / b;
            xa += zn * t * b;
            xb -= zn * t * a;
        }
        zn = -1;
        if (abs(xb) > MAX) {
            if (xb < 0)
                zn *= -1;
            ll t = (abs(xb) + abs(a) - MAX) / a;
            xb += zn * t * a;
            xa -= zn * t * b;
        }
        //        SOLUTION: printf("%d %d\n", (int)xa, (int)xb);
    }
}

long long mul(long long a, long long b, long long m ) {
  long long q = (long long)((long double)a * (long double)b / (long double)m);
  long long r = a * b - q * m;
  return (r + 5 * m) % m;
}

bool RabinMillerCheck(long long x, long long m, long long p) {
    if (p % x == 0)
        return false;
    long long res = mpow(x, m, p);
    if ((res - 1) % p == 0)
        return true;
    while (m < p - 1) {
        if ((res + 1) % p == 0)
            return true;
        res = (res * res) % p;
        m *= 2;
    }
    return false;
} 

/// primes -- array of primes
bool isPrime (int a, const vi & primes) {
    bool prime = true;
    int m = a - 1;
    while (m % 2 == 0)
        m /= 2;
    for (int i = 0; i < 25; ++i) {
	if (a == primes[i]) return true;
        if (!RabinMillerCheck(primes[i], m, a)) {
            return false;
        }
    }
    return prime;
}

/// Baby-step-Giant-step

ll inv (ll a, ll b) {
    ll b1 = b;
    ll xa = 1, xb = 0, ya = 0, yb = 1;
    while (a % b != 0) {
        ll t = a / b;
        a -= t * b;
        xa -= t * ya;
        xb -= t * yb;
        swap(a, b);
        swap(xa, ya);
        swap(xb, yb);
    }
    return up(ya%b1, b1);
}

int pervoobr (int p) {
    vi primes;
    int m = p - 1;
    for (int i = 2; i * i <= m; ++i) {
        if (m % i == 0) {
            primes.push_back(i);
            while (m % i == 0)
                m /= i;
        }
    }
    if (m > 1) primes.push_back(m);
    for (int i = 1; i < p; ++i) {
        bool tr = true;
        for (size_t it = 0; it < primes.size(); ++it) {
            if (mpow(i, (p - 1) / primes[it], p) == 1) {
                tr = false;
                break;
            }
        }
        if (tr)
            return i;
    }
    assert(false);
    return -1;
}

int diskrlog (int a, int g, map<int, int> & brem, int m, int p) {
    long long invg = inv(g, p);
    int cur = a;
    for (int i = 0; i < m; ++i) {
        if (brem.count(cur)) {
//            cout << brem[cur] << " " << i << endl;
            return (brem[cur] * m + i) % (p - 1);
        }
        cur = (cur * invg) % p;
    }
    assert(false);
    return -1;
}

int sqrt(int a, int s, int p) {
    int g = pervoobr(p);
    int m = (int)sqrt((double)(p - 1)) + 3;
    map<int, int> brem; // may be array if p small
    int cur = 1;
    long long bstep = mpow(g, m, p);
    for (int i = 0; i * m < p; ++i) {
        brem[cur] = i;
        cur = (cur * bstep) % p;
    }
    if (a == 0) {
        return 0;
    }
    long long k = diskrlog(a, g, brem, m, p);
    int d = __gcd(p - 1, s);
//    cout << g << " " << inv(g, p) << " " << k << " " << d << endl;
    if (k % d != 0 || k == -1)
        return -1;
    k /= d;
    k *= inv(s / d, (p - 1) / d);
    k = (k % (p - 1) + p - 1) % (p - 1);
    return (int)mpow(g, k, p);
}

ll KTO(vl r, vl m, ll M) {
    ll res = 0;
    for (int i = 0; i < r.size(); ++i) {
        ll M1 = M / m[i];
        res = (res + r[i] * inv(M1, m[i]) % m[i] * M1) % M;
    }
    return res;
}
/// KTO (java):
/* /// n - r.length(), r - îñòàòêè, m - ìîäóëè
    public static BigInteger KTO(int n, BigInteger[] r, BigInteger[] m) {
        BigInteger M = BigInteger.ONE;
        for (int i = 0; i < n; ++i) {
            M = M.multiply(m[i]);
        }
        BigInteger res = BigInteger.ZERO;
        for (int i = 0; i < n; ++i) {
            BigInteger Mmi = M.divide(m[i]); 
            BigInteger invAdd = Mmi.multiply(Mmi.modInverse(m[i]));
            res = res.add(r[i].multiply(invAdd));
        }
        return res.mod(M);
    }
 */


// max-Increasing Sequence

template <class T> vi incSeq(vector<T> a, bool strict = true)
{
    vi res;
    int n = a.size();
    if (n == 0) 
        return res;
    vector<pair<T, int> > L(n);
    vi P(n, -1);
    int c = 1;
    L[0] = make_pair(a[0], 0);
    for (int i = 1; i < n; ++i) {
        pair<T, int> cur = make_pair(a[i], i);
        int ps = upper_bound(L.begin(), L.begin() + c, cur) - L.begin();
        if (strict && (ps > 0 && L[ps - 1].first == a[i])) 
            continue;
        if (ps > 0) 
            P[i] = L[ps - 1].second;
        L[ps] = cur;
        if (ps == c) 
            ++c;
    }
    for (int l = L[c - 1].second; l >= 0; l = P[l]) 
        res.push_back(l);
    reverse(res.begin(), res.end());
    return res;
}


/// time&date
int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool leap(int year) {
    if (year % 100 == 0)
        return year % 400 == 0;
    return year % 4 == 0;
}

int days_in_month(int month, int year) {
    if (month == 2)
        return 28 + leap(year);
    return days[month];
}

int days_before_year(int year) {
    --year;
    int leap_amount = year / 4 - (year / 100 - year / 400);
    return leap_amount * 366 + (year - leap_amount) * 365;
}

int number_by_date(int day, int month, int year) {
    int ans = days_before_year(year);
    for (int i = 1; i < month; ++i)
        ans += days_in_month(i, year);
    ans += day - 1;
    return ans;
}

void date_by_number(int number, int &day, int &month, int &year) {
    static int days400 = days_before_year(401);
    year = (number / days400) * 400 + (number % days400) / 365 + 1;
    while (days_before_year(year) > number) 
        --year;
    number -= days_before_year(year);
    month = 1;
    int sum = 0;
    for (sum = 0; sum <= number; month++) sum += days_in_month(month, year);
    --month;
    sum -= days_in_month(month, year);
    day = number - sum + 1;
}

/// DSU

namespace DSU {
    vector<int> p, rank;

    void init(int n) {
        p.resize(n);
        for (int i = 0; i < n; ++i)
            p[i] = i;
        rank.assign(n, 0);
    }

    int getp(int x) {
        if (x == p[x])
            return x;
        return p[x] = getp(p[x]);
    }

    void join(int x, int y) {
        x = getp(x);
        y = getp(y);
        if (rank[x] > rank[y]) {
            p[y] = x;
        } else {
            p[x] = y;
            if (rank[x] == rank[y])
                ++rank[y];
        }
    }
}

vvi gr;
vector<int> mt;
vector<char> used; 
bool try_kuhn (int v) {
	if (used[v])  return false;
	used[v] = true;
	for (size_t i=0; i<gr[v].size(); ++i) {
		int to = gr[v][i];
		if (mt[to] == -1 || try_kuhn (mt[to])) {
			mt[to] = v;
			mt[v] = to;
			return true;
		}
	}
	return false;
}
mt.assign (gr.size(), -1);
for (int run = 1; run;) {
    run = 0;
    used.assign(gr.size(), false);
    for (int v=0; v<first_part; ++v) if (mt[v] == -1 && try_kuhn(v)) {
        run = 1;
    }
}

namespace FlowsAndRelatedAlgorithms {
struct TEdge {
    int from, to;
    ll capacity, flow;
    ll cost;
    TEdge* reverse;
};

TEdge edgePool[1000000];
int edgePoolPtr = 0;

typedef vector<TEdge*> ve;
vector< ve > edges; //resize

int SOURCE, TARGET; //assign

TEdge* AddEdge(int from, int to, ll capacity, ll cost = 0) {
    TEdge* e1 = &edgePool[edgePoolPtr++];
    TEdge* e2 = &edgePool[edgePoolPtr++];
    TEdge fw = {from, to, capacity, 0, cost, e2};
    TEdge bw = {to, from, 0, 0, cost, e1};
    *e1 = fw;
    *e2 = bw;
    edges[from].push_back(e1);
    edges[to].push_back(e2);
    return e1;
}

inline ll AvailableCapacity(const TEdge* p) {
    return (p->capacity - p->flow);
}

    namespace FordFulkersonSimple { // simple Ford-Fulkerson, relaxing by one flow per time
        vector<bool> been; // assign

        bool ff_dfs(int p) { 
            if (p == TARGET) return true;
            if (been[p]) return false;
            been[p] = true;
            for (ve::iterator it = edges[p].begin(); it != edges[p].end(); it++) {
                if ((*it)->flow < (*it)->capacity && ff_dfs((*it)->to)) {
                    (*it)->flow++;
                    (*it)->reverse->flow--;
                    return true;
                }
            }
            return false;
        }
    }

    namespace LiftToFront_2_3_2 { // TODO: organize like other algorithms into separate function
        typedef vector<vi> vvi;

        int main() {
            int n, m;
            scanf("%d%d", &n, &m);
            int s = 0;
            int t = n + m + 1;
            int siz = n + m + 2;
            vvi f(siz, vi(siz));
            vvi c(siz, vi(siz));
            vi h(siz);
            vi e(siz);
            h[s] = siz;
            vi has(siz);
            for (int i = 1; i <= n; ++i) {
                int coll = m + i;
                for (int j = 1; j <= m; ++j) {
                    int cap;
                    scanf("%d", &cap);
                    if (i > 1) {
                        if (cap > 1) {
                            c[coll][j] = cap - 1;
                        } else if (cap == 0)
                            c[j][coll] = 1;
                    } else {
                        c[s][j] = cap;
                        f[s][j] = cap;
                        f[j][s] = -cap;
                        e[j] = cap;
                        has[j] = cap;
                    }
                }
            }
            for (int j = 1; j <= m; ++j) {
                c[j][t] = 1;
            }

            while (1) {
                bool some = false;
                for (int i = 0; i < siz; ++i) {
                    if (i == t || i == s)
                        continue;
                    if (e[i] > 0) {
                        for (int j = 0; j < siz && e[i] > 0; ++j) {
                            if (f[i][j] < c[i][j] && h[i] == h[j] + 1) {
                                int dif = min(c[i][j] - f[i][j], e[i]);
                                f[i][j] += dif;
                                f[j][i] -= dif;
                                e[i] -= dif;
                                e[j] += dif;
                                some = true;
                            }
                        }
                        if (e[i] > 0) {
                            int maxh = 10000;
                            for (int j = 0; j < siz; ++j) {
                                if (f[i][j] < c[i][j]) {
                                    maxh = min(maxh, h[j]);
                                }
                            }
                            assert(maxh < 10000);
                            some = true;
                            h[i] = maxh + 1;
                        }
                    }
                }
                if (!some)
                    break;
            }
            printf("%d\n", e[t]);
            return 0;
        }
    }

    class TDinic {
    vector<int> Distances;
    vector<size_t> Ptr;
    int N;
    void BFS() {
        deque<int> q;
        Distances.assign(N, -1);
        Distances[SOURCE] = 0;
        q.push_back(SOURCE);
        while (!q.empty()) {
            int p = q.front();
            q.pop_front();
            for (size_t i = 0; i < edges[p].size(); i++) {
                if (!AvailableCapacity(edges[p][i]))
                    continue;
                int c = edges[p][i]->to;
                if (Distances[c] == -1) {
                    Distances[c] = Distances[p] + 1;
                    q.push_back(c);
                }
            }
        }
    }
    ll DFS(int p, ll fl) {
        if (fl == 0)
            return 0;
        if (p == TARGET)
            return fl;
        ll res = 0;

        for (size_t &i = Ptr[p]; Ptr[p] < edges[p].size() && fl != 0; ++i) {
            if (!AvailableCapacity(edges[p][i])) {
                continue;
            }
            if (Distances[edges[p][i]->from] + 1 != Distances[edges[p][i]->to])
                continue;
            ll pushed = DFS(edges[p][i]->to, min(fl, AvailableCapacity(edges[p][i])));
            fl -= pushed;
            res += pushed;
            edges[p][i]->flow += pushed;
            edges[p][i]->reverse->flow -= pushed;
            if (fl == 0)
                break;
        }
        return res;
    }
    /*void init() {
        SOURCE,TARGET
        edges.clear();
        edgePoolPtr = 0;
        edges.resize();
    }*/
    ll calc_max_flow() {
        N = (int)edges.size();
        ll res = 0;
        while (true) {
            BFS();
            Ptr.assign(N, 0);
            ll p = DFS(SOURCE, LLONG_MAX / 2);
            if (!p)
                break;
            res += p;
        }
        return res;
    }
    };

    bool RelaxCycles() {
        int n = (int)edges.size();
        vector< ve::iterator > from(n);
        vector<int> d(n, 0);
        int ch = -1;
        for (int i = 0; i < n; i++) {
            ch = -1;
            for (int j = 0; j < n; j++) {
                for (ve::iterator it = edges[j].begin(); it != edges[j].end(); it++) {
                    if (it->flow < it->cap && d[it->to] > d[j] + it->cost) {
                        d[it->to] = d[j] + it->cost;
                        from[it->to] = it;
                        ch = it->to;
                    }
                }
            }
        }
        if (ch == -1) return false;
        for (int i = 0; i < n; i++) {
            ch = from[ch]->from;
        }
        int x = ch;
        while (true) {
            from[x]->flow += 1;
            edges[ch][from[x]->backInd].flow -= 1;
            x = from[x]->from;
            if (x == ch) break;
        }
        return true;
    }

    void maxFlowMinCost(int so, int ta, int & flow, int & cost) {
        flow = 0;
        cost = 0;
        const int inf = (int)1e+9;
        while (1) {
            vi pvert(edges.size()), pedge(edges.size()), d(edges.size(), inf), id(edges.size());
            deque<int> q;
            q.push_back(so);
            id[so] = 1;
            d[so] = 0;
            while (!q.empty()) {
                int v = q.front();
                q.pop_front();
                id[v] = 2;
                for (size_t i = 0; i < edges[v].size(); ++i) {
                    TEdge & ed = *edges[v][i];
                    if (ed.flow < ed.cap && d[v] + ed.cost < d[ed.to]) {
                        d[ed.to] = d[v] + ed.cost;
                        if (id[ed.to] == 0) {
                            q.push_back(ed.to);
                        } else if (id[ed.to] == 2) {
                            q.push_front(ed.to);
                        }
                        id[ed.to] = 1;
                        pvert[ed.to] = v;
                        pedge[ed.to] = i;
                    }
                }
            }
            if (d[ta] == inf) break;
            int dflow = inf;
            for (int v = ta; v != so; v = pvert[v]) {
                TEdge & ed = *edges[pvert[v]][pedge[v]];
                dflow = min(dflow, ed.cap - ed.flow);
            }
            for (int v = ta; v != so; v = pvert[v]) {
                TEdge & ed = *edges[pvert[v]][pedge[v]];
                TEdge & inved = *edges[ed.to][ed.backInd];
                ed.flow += dflow;
                inved.flow -= dflow;
                cost += ed.cost * dflow;
            }
            flow += dflow;
        }
    }
}

namespace StronglyConnected {
    vector < vector<int> > g, gr;
    vector<char> used;
    vector<int> order, component;

    void dfs1 (int v) {
        used[v] = true;
        for (size_t i=0; i<g[v].size(); ++i)
            if (!used[ g[v][i] ])
                dfs1 (g[v][i]);
        order.push_back (v);
    }

    void dfs2 (int v) {
        used[v] = true;
        component.push_back (v);
        for (size_t i=0; i<gr[v].size(); ++i)
            if (!used[ gr[v][i] ])
                dfs2 (gr[v][i]);
    }

    int main() {
        int n;
        //... ÷òåíèå n ...
        cin >> n;
        g.resize(n); gr.resize(n);
        for (;;) {
            int a, b;
            //... ÷òåíèå î÷åðåäíîãî ðåáðà (a,b) ...
            cin >> a >> b; // --a; --b;
            g[a].push_back (b);
            gr[b].push_back (a);
        }

        used.assign (n, false);
        for (int i=0; i<n; ++i)
            if (!used[i])
                dfs1 (i);
        used.assign (n, false);
        for (int i=0; i<n; ++i) {
            int v = order[n-1-i];

            if (!used[v]) {
                dfs2 (v);
                //... âûâîä î÷åðåäíîé component ...
                component.clear();
            }
        }
    }
}

namespace Bridges {
    vector < vector<int> > g;
    vector<char> used;
    int timer;
    vector<int> tin, fup;

    void IS_BRIDGE(int, int) {}
    void IS_CUTPOINT(int) {}

    void dfs (int v, int p = -1) {
        used[v] = true;
        tin[v] = fup[v] = timer++;
        int children = 0; // <-- don't need this for bridges
        for (size_t i=0; i<g[v].size(); ++i) {
            int to = g[v][i];
            if (to == p)  continue;
            if (used[to])
                fup[v] = min (fup[v], tin[to]);
            else {
                dfs (to, v);
                fup[v] = min (fup[v], fup[to]);
                if (fup[to] > tin[v])
                    IS_BRIDGE(v,to);
                if (fup[to] >= tin[v] && p != -1)
                    IS_CUTPOINT(v);
                ++children;
            }
        }
        if (p == -1 && children > 1)
            IS_CUTPOINT(v);
    }

    int main() {
        int n;
        cin >> n;
        //... ÷òåíèå g ...

        timer = 0;
        used.assign (n, false);
        tin.resize (n);
        fup.resize (n);
        dfs (0);
        return 0;
    }
}

namespace LCA {
    vector<vector<int> > g;
    vector<int> posv, vpos, ord;

    int timecnt = 1;

    void dfs (int v, int p) {
        int tin = ++timecnt;
        vpos[v] = ord.size();
        posv.push_back(v);
        ord.push_back(tin);
        for (size_t i = 0; i < g[v].size(); ++i) {
            int to = g[v][i];
            if (to != p) {
                dfs(to, v);
                posv.push_back(v);
                posv[ord.size()] = v;
                ord.push_back(tin);
            }
        }
    }

    class Tree {
        vector<int> minpos;
        vector<int> vals;
        int trsize;
    public:
        Tree(const vector<int> & vals_) {
            int size = vals_.size();
            int i;
            for (i = 1; (1 << i) < size; ++i)
                ;
            trsize = (1 << i);
            minpos.resize(trsize * 2);
            vals.resize(trsize, 1000000000);
            copy(vals_.begin(), vals_.end(), vals.begin());
            for (int i = 0; i < trsize; ++i) {
                minpos[i + trsize] = i;
            }
            for (int i = trsize - 1; i >= 1; --i)
                if (vals[minpos[i*2]] < vals[minpos[i*2+1]])
                    minpos[i] = minpos[i*2];
                else
                    minpos[i] = minpos[i*2+1];
        }
        int getminpos(int from, int to) {
            int curpos = from;
            from += trsize;
            to += trsize;
            while (to - from >= 0) {
                if (vals[curpos] > vals[minpos[to]]) {
                    curpos = minpos[to];
                }
                if (vals[curpos] > vals[minpos[from]]) {
                    curpos = minpos[from];
                }
                from = (from + 1) / 2;
                to = (to - 1) / 2;
            }
            return curpos;
        }
    };

    int lca(Tree & t, int a, int b) {
        return posv[t.getminpos(min(vpos[a], vpos[b]), max(vpos[a], vpos[b]))];
    }

    int main() {
        int n;
        cin >> n;
        g.resize(n);
        vpos.resize(n);
        for (int i = 0; i + 1 < n; ++i) {
            int a,b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        dfs(0, -10000);
        Tree t(ord);
        for (int a, b; cin >> a >> b;) {
            cout << lca(t, a, b) << endl;
        }
        return 0;
    }
};
/*
namespace Cnk_fact {
    int n;
    vector<int> a(n);
    vector<int> was(n);

    void gen_Fact_n(int i) {
        if(i==n) {
            // ðàññìàòðèâàåì ïîäìíîæåñòâî, çàäàâàåìîå ìàññèâîì A
        }
        for (j = 0; j < n ; j++)
            if (!was[j]) {
                was[j] = 1;
                a[i] = j; gen_Fact_n(i+1);
                was[j] = 0;
            }
    }


    int m,n;
    int A[M+1] = {0,..};

    // i from 1

    void genCnm(int i) {
        if(i > m) {
            // ðàññìàòðèâàåì ïîäìíîæåñòâî, çàäàâàåìîå ìàññèâîì A
        }
        for(j = A[i-1] + 1; j < n ; j++)
        {
            A[i] = j; genCnm(i+1);
        }
    }
};
*/
namespace Fenwick {
    vector<int> t;
    int n;

    void init (int n) {
        t.assign (n, 0);
    }

    int sum (int r) {
        int result = 0;
        for (; r >= 0; r = (r & (r+1)) - 1)
            result += t[r];
        return result;
    }

    void inc (int i, int delta) {
        for (; i < n; i = (i | (i+1)))
            t[i] += delta;
    }

    int sum (int l, int r) {
        return sum (r) - sum (l-1);
    }

    void init (vector<int> a) {
        init ((int) a.size());
        for (unsigned i = 0; i < a.size(); i++)
            inc (i, a[i]);
    }
};

void conv(vl & x) {
    for (int b = 0; b < n; ++b) {
        int B = 1 << b;
        for (int i = 0; i < x.size(); ++i) if (i & B) {
            x[i] = (x[i] + x[i^B]) % mod1;
        }
    }
}
/*
double closestPair(vector<P> p) {
  sort(p.begin(), p.end(), &cmpX);
  set<P> s;
  int l = 0, r = 0;
  double res = 1e100;
  while (r != n) {
      if (s.count(p[r])) return 0.;
      s.insert(p[r++]);
      while (l < r && abs(p[l].x - p[r-1].x) > res) {
        set<P>::iterator it = s.find(p[l]);
        l++;
        if (it != s.end())
          s.erase(it);
      }
      set<P>::iterator pr = s.find(p[r - 1]), cur, last;
      cur = pr, cur--;
      last = s.begin(), last--;
      while (cur != last && abs(cur->y - p[r-1].y) <
        res) {
          res = min(res, (*cur - p[r - 1]).len());
          cur--;
      }
      cur = pr;
      cur++;
      last = s.end();
      while (cur != last && abs(cur->y - p[r - 1].y) <
        res) {
          res = min(res,(*cur - p[r - 1]).len());
          cur++;
      }
    }
    return res;
}*/

void mul(u32* res, u32* m1, u32* m2) {
	//res.assign(N*N, 0);
	unsigned* ptr = trm2;
	for (int i = 0; i < N; i++) {
		for (int j = 0, jN = 0; j < N; j++, jN += N, ptr++) {
			*ptr = m2[i + jN];
		}
	}
	const unsigned *ptr2, *ptr3;
	ptr = res;
	for (int i = 0, iN = 0; i < N; i++, iN += N) {
		ptr2 = trm2;
		for (int j = 0, jN = 0; j < N; j++, jN += N, ptr++) {
			int cnt = 15;
			unsigned long long balance = 0;
			ptr3 = m1+iN;
			for (int k = 0; k < N; k++, ptr2++, ptr3++) {
				balance += (*ptr3) * (unsigned long long)(*ptr2);
				if (!--cnt) {
					balance %= P;
					cnt = 15;
				}
			}
			*ptr = balance % P;
		}
	}
}

const ll n = 1000000000000LL;
const ll L = 1000000;
int small[L+1];
ll large[L+1];
void calc_pi() {
    for (int i = 1; i <= L; ++i) {
        small[i] = i-1;
        large[i] = n / i - 1;
    }
    for (ll p = 2; p <= L; ++p) {
        if (small[p] == small[p-1]) continue;
        int cntp = small[p-1];
        ll p2 = p*p;
        ll np = n / p;
        for (int i = 1; i <= min(L, n / p2); ++i) {
            ll x = np / i;
            if (x <= L) {
                large[i] -= small[x] - cntp;
            } else {
                large[i] -= large[p*i] - cntp;
            }
        }
        for (int i = L; i >= p2; --i) {
            small[i] -= small[i/p] - cntp;
        }
    }
}

ll pi(ll x) {
    if (x > L) {
        return small[n/x];
    } else {
        return large[x];
    }
}
