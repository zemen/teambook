//BEGIN ALGO
struct Fenwick {
    int *t;
    int n;

    Fenwick(int *a, int len): n(len) {
        t = new int[n];
        memset(t, 0, sizeof(int) * n);
        for (int i = 0; i < n; ++i) {
            inc(i, a[i]);
        }
    }

    ~Fenwick() {
        delete[] t;
    }

    void inc(int l, int delta) {
        for (int i = l; i < n; i = (i | (i + 1))) {
            t[i] += delta;
        }
    }

    int sum(int r) {
        int result = 0;
        for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
            result += t[i];
        }
        return result;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

//END ALGO
