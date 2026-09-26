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
#include <utility>
#include <cassert>
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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

char a[maxn];
inline LL get(int now){
    int F=0,i;
    rep(i,1,10) if ((now>>i)&1) F=F*10+i;
    return F;
}bool check(int len,int now,int val,int n,int cnt,bool OK){
    now^=1<<val;int i,j;
    LL k=0;
    j=0;REP(i,10) if ((now>>i)&1) j++;
    if (n-len<j) return 0;
    LL F,G;F=G=0;F=get(now);
    int last=n-1;LL K=1;
    for (;last>len&&n-last<15;) {G+=(a[last]-'0')*K,K*=10;if (a[last]!='0') cnt--;last--;}
    if (!OK&&!cnt&&F>=G) return 0;
//    printf("%d->%d:%lld %lld(%lld); now=%d;  cnt=%d\n",len,last,K,G,F,now,cnt);
    return 1;
}
int T;
int n,m;
int i,j,k;
int ans;
int now,noww;
int L,len;
int main(){
    scanf("%d",&T);
    while (T--){
        scanf("%s",a);
        n=strlen(a);
        bool mark=0;int cnt=0;//9
        REP(i,n) if (a[i]!='0') cnt++;
        REP(len,n){
            if (a[len]!='0') cnt--;
            if (!check(len,now,a[len]-'0',n,cnt,mark)){
//                    printf("NO %d(%c)\n",len,a[len]);
                a[len]--;
                if (!mark) rep(i,len+1,n) a[i]='9';mark=1;
                while (!check(len,now,a[len]-'0',n,cnt,mark)) a[len]--;
            }now^=1<<(a[len]-'0');
        }if (a[0]=='0'){
            REP(i,len-2) putchar('9');puts("");
        }else printf("%s\n",a);
    }
}
/*
*/
