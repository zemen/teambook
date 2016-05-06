#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

//BEGIN ALGO

int p;
string s;

int readNum() {
    int res = 0;
    while (isdigit(s[p])) {
        res = res * 10 + s[p] - '0';
        p++;
    }
    return res;
}

int calcExpr();

int calcMul() {
    int res;
    if (s[p] == '(') {
        p++;
        res = calcExpr();
        p++;
    } else if (s[p] == '-') {
        p++;
        res = -readNum();
    } else {
        res = readNum();
    }
    return res;
}

int calcAdd() {
    int res = calcMul();
    while (s[p] == '*' || s[p] == '/') {
        char op = s[p];
        p++;
        int t = calcMul();
        if (op == '*') {
            res *= t;
        } else {
            res /= t;
        }
    }
    return res;
}

int calcExpr() {
    int res = calcAdd();
    while (s[p] == '+' || s[p] == '-') {
        char op = s[p];
        p++;
        int t = calcAdd();
        if (op == '+') {
            res += t;
        } else {
            res -= t;
        }
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s;
        p = 0;
        cout << calcExpr() << endl;
    }
    return 0;
}

//END ALGO
