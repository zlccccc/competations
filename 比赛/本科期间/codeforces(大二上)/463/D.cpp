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
const LL maxn=4e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

LL n;
LL fa[maxn][27],a[maxn],SUM[maxn],i,j;
LL lastans,h[maxn];
int q,cnt;
int main(){
    scanf("%d",&q);
    cnt=1;h[1]=1;
    FOR(i,2,q+1){
        LL op,R,X;
        scanf("%I64d%I64d%I64d",&op,&R,&X);
        R^=lastans;X^=lastans;
        if (op==1){
//            printf("CALFA   %I64d %I64d\n",R,X);
            rREP(j,20) if (fa[R][j]&&a[fa[R][j]]<X) R=fa[R][j];
//            printf("fa: %d=%I64d\n",cnt,R);
            if (a[R]<X) R=fa[R][0];
            cnt++;h[cnt]=h[R]+1;
            a[cnt]=X;SUM[cnt]=SUM[R]+X;
//            printf("fa: %d=%I64d\n",cnt,R);
            fa[cnt][0]=R;
            rep(j,1,20) fa[cnt][j]=fa[fa[cnt][j-1]][j-1];
        }else{
//            printf("CAL %I64d  %I64d\n",R,X);
            lastans=h[R];
            rREP(j,20) if (SUM[R]-SUM[fa[R][j]]<=X){
                X-=SUM[R]-SUM[fa[R][j]];R=fa[R][j];
            }
            lastans-=h[R];//R是第一个不满足的
//            printf("cal: R=%I64d %I64d\n",R,X);
            printf("%I64d\n",lastans);
//            puts("");
        }
    }
}
/*
6
1 1 1
2 2 0
2 2 1
1 3 0
2 2 0
2 2 2
*/
