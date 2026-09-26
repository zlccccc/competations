#include <bits/stdc++.h>
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
using namespace std;
const int maxn=2e5+7;
char str[maxn];
int main(){
    int t,n,i;
    scanf("%d",&t);
    while(t--){
        scanf("%d%s",&n,str+1);
        int ans=0,mask=0;
        FOR(i,3,n+1){
            if (str[i-3]=='C'&&str[i-2]=='C'&&str[i-1]=='P'&&str[i]=='C') ans++;
            if (str[i-3]!='C'&&str[i-2]=='C'&&str[i-1]=='P'&&str[i]=='C') mask=1;
            if (str[i-3]=='C'&&str[i-2]=='C'&&str[i-1]=='P'&&str[i]!='C') mask=1;
            if (str[i-3]=='C'&&str[i-2]=='C'&&str[i-1]=='C'&&str[i]!='P') mask=1;
        } printf("%d\n",ans+mask);
    }
}
/*
3
3
CCC
5
CCCCP
4
CPCP
*/
