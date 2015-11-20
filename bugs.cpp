//IOI 2015 scales
-   bool ok = false;
+   bool ok = true;
    forn (q, 3)
        if (!calc(b[sizes[q].second], bound - 1))
        {
            ok = false;
            break;
        }


//CF 315C
-   dfs1(i);
+   forn (i, N)
+       if (!used[i])
+           dfs1(i);


//CF 315C
-   forn (i, N)
+   for (int i: ord)
    {   
        ++COL;
        if (!used[i])
        dfs2(i);
    }   


//IOI 2015 horses
    forn (i, n)
        if (x[i] > 1)
-           goodx.insert(x[i]);
+           goodx.insert(i);


//Petrsu summer camp 2015 day1 A

        //Mergeable maps
-       if (sz(a[i]) > sz(a[j]))
-           swap(i, j);
+       bool swapped = false;
+       if (sz(a[i]) > sz(a[j]))
+           swap(i, j), swapped = true;

        for (auto p: a[i].pref)
        {
            int x = p.first + a[i].bal;
            ll cnt = p.second;
            res += cnt * a[j].getsuf(x);
        }
        for (auto p: a[i].suf)
        {
            int x = p.first - a[i].bal;
            ll cnt = p.second;
            res += cnt * a[j].getpref(x);
        }
-       if (s[u] == '(')
-           a[i].open();
-       else
-           a[i].close();
+       if (s[u] == '(')
+           a[swapped ? i : j].open();
+       else
+           a[swapped ? i : j].close();


//Petrsu summer camp 2015 day1 D
    //Segment tree
+   fill(upd, upd + base * 2, 0);


//Petrsu summer camp 2015 day1 J
    ld qwer = (x * cosl(phi) + y * sinl(phi)) / dist;
-   ld dphi = acosl(min(1.0L, max(-1.0L, qwer)));
+   ld dphi = acosl(qwer);


//Petrsu summer camp 2015 day3 G
    int getId(Node *t)
    {
-       int id = 0;
+       int id = cnt(t->l);
        while (t->p)
        {
            if (t->p->r == t)
                id += cnt(t->p->l) + 1;
            t = t->p;
        }
        return id;
    }


//Petrsu summer camp 2015 day4 C
    forn (i, m)
        {
            scanf("%d", c + i + n);
            s.emplace(c[i + n], i + n);
-           ans[i] = -1;
+           ans[i + n] = -1;
        }


//Petrsu summer camp 2015 day5 A
    forn (i, n - 1)
    {
        int p;
        cin >> p;
        g[p].push_back(i + 1);
-       ::p[i][0] = p;
+       ::p[i + 1][0] = p;
    }


//Petrsu summer camp 2015 day5 A
-       ans += min(R + 1, p.second) - max(L, p.first);
+       ans += max(0ll, min(R + 1, p.second) - max(L, p.first));


//Petrsu summer camp 2015 day2 J
    cnt[u] = 1;
    for (int v: g[u])
        if (v != prev)
        {
            dfs(v, u, ch + 1);
+           cnt[u] += cnt[v];
        }


//CF 327C
-   if (res == INF)
+   if (res >= INF / 2)
        res = -1; 


//Opentrains 010026 F
    struct E {
        int v, c, w;
-   } es[maxn];
+   } es[2 * maxn];


//Opentrains 010026 H
        fill(mask, mask + n, 0);
-       fill(init, mask + n, ll(-1));
+       fill(init, init + n, ll(-1));


//Opentrains 010026 H
-       mask[v] |= (init[u] & mask[v]);
+       mask[v] |= (init[v] & mask[u]);


//Opentrains 001367 H
    forn (i, n)
-       forn (j, n)
+       forn (j, i)


//Opencup GP of Yekaterinburg
    edge[e].f++;
-   edge[e ^ 1].f++;
+   edge[e ^ 1].f--;


//Hackerrank testing
//Fenwick tree
-   return get(xr, yr) + get(xl, yl) - get(xr, yl) - get(yr, xl);
+   return get(xr, yr) + get(xl, yl) - get(xr, yl) - get(xl, yr);


//Opencup GP of Siberia 4
+   cout.precision(10);


//Opencup GP of Siberia 3
-   if (mask[u] | (ull(1) << (j - i)))
+   if (mask[u] & (ull(1) << (j - i)))


//Opencup GP of Siberia 6
    return pos.x * cos(ang) + pos.y * -sin(ang)
-          pos.x * sin(ang) + pos.x *  cos(ang);
+          pos.x * sin(ang) + pos.y *  cos(ang);


//MIPT Fall Day1 J
ld d[1 << maxn][maxn]; // some dynamic
...
int dist[maxn][maxn]; // distance matrix
...
    forn (k, n)
        forn (i, n)
            forn (j, n)
-               d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
+               dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);


//Some task on PE
int add(int x, int y) {
  x += y;
  if (x >= mod) {
-   x -= y;
+   x -= mod;
  }
  return x;
}
