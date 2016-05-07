#include <bits/stdc++.h>
using namespace std;
#define forn(i,n) for (int i = 0; i < int(n); ++i)

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

int main() {
    cout << duval("ababcabab") << '\n'; // 5
}
