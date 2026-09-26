#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <bitset>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,q;
bitset<maxn> T[26],now;
char a[maxn],b[maxn];
int i;
int main(){
    scanf("%s",a);
    n=strlen(a);
    REP(i,n) T[a[i]-'a'].set(i);
    scanf("%d",&q);
    while (q--){
        int op;
        scanf("%d",&op);
        if (op==1){
            int pos;char c;
            scanf("%d%*c%c",&pos,&c);pos--;
            T[a[pos]-'a'][pos]=0;
            a[pos]=c;
            T[a[pos]-'a'][pos]=1;
        }else{
            int l,r;
            scanf("%d%d%s",&l,&r,b);
            int len=strlen(b);
            if (len>r-l+1) puts("0");
            else {
                now.set();
                now=(now>>(l-1))<<(l-1);
                now=(now<<(maxn-(r-len+1)))>>(maxn-(r-len+1));
//                REP(i,10) printf("%d",(int)now[i]);puts("");
//                REP(i,10) printf("%d",(int)T[0][i]);puts("");
//                REP(i,10) printf("%d",(int)T[1][i]);puts("");
                REP(i,len) now&=(T[b[i]-'a']>>i);
                printf("%d\n",(int)now.count());
            }
        }
    }
}
/*
ababababa
3
2 1 7 aba
1 5 c
2 1 7 aba

*/
