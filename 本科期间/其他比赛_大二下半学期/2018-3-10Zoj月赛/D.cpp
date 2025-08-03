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
const LL M=998244353;
const LL maxn=200000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int a[maxn];
vector<int> edge[maxn];
int F[maxn][2];
void dfs(int x,int fa){
    F[x][0]=F[x][1]=0;
    for (int v:edge[x]) if (fa!=v){
        dfs(v,x);
        F[x][0]+=min(F[v][0],F[v][1]+1);
        F[x][1]+=min(F[v][1],F[v][0]+1);
    }
    if (a[x]==1) F[x][0]=INF;
    if (a[x]==0) F[x][1]=INF;
}
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        int n,i;scanf("%d",&n);
        FOR(i,1,n) scanf("%d",&a[i]);
        FOR(i,1,n-1){
            int u,v;
            scanf("%d%d",&u,&v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }dfs(1,0);
        FOR(i,1,n) edge[i].clear();
        printf("%d\n",min(F[1][0],F[1][1]));
    }
}
/*
*/
