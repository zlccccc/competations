#include <iostream>
#include <string>
using namespace std;
int main() {
    int n;
    string s;
    cin>>s;
    int cnt=0;
    for (char c:s) {
        if (c=='1') cnt++;
        else cnt=0;
        if (cnt>=6) return 0*puts("NO");
    }
    puts("YES");
    return 0;
}
/*
3 2
3 3
12 34
20 231104

36
168
539029838
966200489
*/