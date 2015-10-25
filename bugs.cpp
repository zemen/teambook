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
-		int id = 0;
+		int id = cnt(t->l);
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
-			ans[i] = -1;
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
