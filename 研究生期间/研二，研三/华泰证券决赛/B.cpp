#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(I,N) for (I=0;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
const int maxn=1e5+7;
char str[maxn];
int main() {
    int n,i; ll k;
    scanf("%s%lld",str,&k);
    n=strlen(str);
    reverse(str,str+n);
    REP(i,n) {
        k+=str[i]-'a';
        str[i]=k%26+'a';
        k/=26;
    }
    if (k) return 0*puts("-1");
    reverse(str,str+n);
    puts(str);
}
/*
abc
30

zzy
3
*/ 