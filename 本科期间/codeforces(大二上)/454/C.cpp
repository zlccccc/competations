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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,q;
int f[27][27];
int g[27],ans[27],Ans;
void dfs(int i,int cnt){
    bool mark=1;int j;
    if (cnt==Ans) return;
    REP(j,n) if (f[cnt][j]!=(1<<n)-1) mark=0;
    if (mark){
        Ans=cnt;
        REP(j,cnt) ans[j]=g[j]+1;
        return;
    }for(;i<n;i++){
        g[cnt]=i;
        REP(j,n)
            if (1&(f[cnt][i]>>j)) f[cnt+1][j]=f[cnt][j]|f[cnt][i];
            else f[cnt+1][j]=f[cnt][j];
        dfs(i+1,cnt+1);
    }
}
int i,j,k;
int main(){
    scanf("%d%d",&n,&m);
    REP(i,n) f[0][i]|=1<<i;
    REP(i,m){
        int u,v;
        scanf("%d%d",&u,&v);u--;v--;
        f[0][u]|=1<<v;
        f[0][v]|=1<<u;
    }Ans=n+1;
    dfs(0,0);
    printf("%d\n",Ans);
    REP(i,Ans) printf("%d ",ans[i]);
}
/*
*/
