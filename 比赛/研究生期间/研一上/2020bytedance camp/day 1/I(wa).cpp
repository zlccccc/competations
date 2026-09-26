#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using LL=long long;

int x, y, z;
char a, b;
string s, o = "0123456789+-*/";

double calc(double a, double b, char c) {
    switch (c) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            return -1;
    }
}

bool judge(string s, bool fromM) {
    stringstream ss;
    ss << s;
    ss >> x >> a >> y >> b >> z;
    if (ss.fail() || a != '+' && a != '-' && a != '*' && a != '/' || b != '=' || x <= 0 || x > 1E9 || y <= 0 ||
        y > 1E9 || z <= 0 || z > 1E9) {
        if (!fromM)
            return false;
        cout << "Format Error" << endl;
        exit(0);
    }
    ss.clear();
    string t;
    ss << x << a << y << b << z;
    ss >> t;
    if (t != s) {
        if (!fromM)
            return false;
        cout << "Format Error" << endl;
        exit(0);
    }
    if (calc(x, y, a) == z) {
        if (!fromM)
            return true;
        cout << "Correct" << endl;
        exit(0);
    }
    return false;
}

void dfs(int x, string ns) {
    if (x > 2) {
        if (judge(ns, false)) {
            cout << "Typo: " << s << " instead of " << ns << endl;
            exit(0);
        }
        return;
    }
    for (int i = 0; i < ns.size(); i++)
        for (char r:o) {
            string t = ns;
            t[i] = r;
            dfs(x + 1, t);
        }
}

int main() {
    cin >> s;
    judge(s, true);
    dfs(1, s);
    cout << "Math Error" << endl;
    return 0;
}
