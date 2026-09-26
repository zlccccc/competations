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
const LL M=998244353;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
double f[600][64];
bool mark[600][64];
double a[17][600];
double ans;
int u,v,w;
double dfs(int t,int used){//time,used_things
    if (mark[t][used]) return f[t][used];
    int i,j;
    REP(i,n) if (!((used>>i)&1)){
        double now=0;
        FOR(j,1,m)
            if (t+j<=m)
                now+=a[i][j]*(dfs(t+j,used|(1<<i))+1);
        f[t][used]=max(f[t][used],now);
    }mark[t][used]=1;
    return f[t][used];
}
int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    REP(i,n)
        FOR(j,1,m)
            scanf("%lf",&a[i][j]);
    printf("%.5lf",dfs(0,0));
}
/*
1 5
0.2 0.2 0.2 0.2 0.2

3 5
0.5 0.5 0 0 0
0.5 0.5 0 0 0
0 0 0.5 0.5 0
*/
