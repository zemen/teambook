#include <bits/stdc++.h>
using namespace std;
#define forn(i,n) for (int i = 0; i < int(n); ++i)

typedef vector<int> vi;

// BEGIN_CODE
/*
   Строка простая, если cтрого меньше всех суффиксов <=>
   наименьший циклический сдвиг - первый.
   Декомпозиция Линдона - разбиение s на w1, w2, ... wk -
   простые строки такие, что w1 >= w2 >= ... wk.
*/
int duval(string s) {
    s += s; //remove this to find Lyndon decomposition of s
    int n = s.size();
    int i = 0;
    int ans = 0;
    //while (i < n) { //for Lyndon decomposition
    while (i < n / 2) {
        ans = i;
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j])
                k = i;
            else
                ++k;
            ++j;
        }
        while (i <= k) {
            //s.substr(i, j - k) -
            //next prime string of Lyndon decomposition
            i += j - k;
        }
    }
    return ans;
}

//actual odd length is (odd[i] * 2 - 1)
//actual even length is (even[i] * 2)
void manacher(const string &s, vi &odd, vi &even) {
    int n = s.size();
    odd.resize(n);
    int c = -1, r = -1;
    forn (i, n) {
        int k = (r <= i ? 0 : min(odd[2 * c - i], r - i));
        while (i + k < n && i - k >= 0 && s[i + k] == s[i - k])
            ++k;
        odd[i] = k;
        if (i + k > r)
            r = i + k, c = i;
    }
    c = -1, r = -1;
    even.resize(n - 1);
    forn (i, n - 1) {
        int k = (r <= i ? 0 : min(even[2 * c - i], r - i));
        while (i + k + 1 < n && i - k >= 0 &&
                s[i + k + 1] == s[i - k])
            ++k;
        even[i] = k;
        if (i + k > r)
            c = i, r = i + k;
    }
}

void test() {
    vector<int> odd, even;
    string s = "aaaabbaaaaa";
    manacher(s, odd, even);
    for (int x: even)
        cerr << x << ' ';
    cerr << '\n';
    for (int x: odd)
        cerr << x << ' ';
    cerr << '\n';
    // 1 2 1 0 5 0 1 2 2 1
    // 1 2 2 1 1 1 1 2 3 2 1
}

int main() {
    cout << duval("ababcabab") << '\n'; // 5
    test();
}
// END_CODE
