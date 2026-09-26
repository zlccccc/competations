#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#define REP(I,S,N) for (I=S;I<N;I++)
#define rREP(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
const int maxn=1e6+7;
const int INF=0x3f3f3f3f;
using namespace std;
typedef long long LL;

int n,m,k,t;
int u,v;
int d[maxn];
double ans;
int main(){
    int T,n,m,k,i,j;
    while (~scanf("%d%d%d",&n,&m,&k)){
        FOR(i,0,n-1) d[i]=0;ans=0;
        FOR(i,1,m) scanf("%d%d",&u,&v),d[u]++,d[v]++;
        FOR(i,1,k) scanf("%d",&t),ans+=(d[t]+1.0)/(m*2+n);
        printf("%.5lf\n",ans);
    }
}
