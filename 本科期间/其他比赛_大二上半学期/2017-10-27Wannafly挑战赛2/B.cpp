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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
LL d[maxn],w;
LL e[47][47];
LL dis[47][47];
int p[47];
int pos[maxn];
inline void upd(int x,int y,LL len){
	dis[x][y]=min(dis[x][y],len);
	dis[y][x]=min(dis[y][x],len);
}
inline LL DIS(int x,int y){x--;y--;
	return min(abs(d[x]-d[y]),d[n]-abs(d[x]-d[y]));
}
int main(){
	int i,j,k;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%lld",&d[i]);
	FOR(i,1,n) d[i]+=d[i-1];
//	FOR(i,1,n) FOR(j,1,n) printf("%d-%d;%d\n",i,j,DIS(i,j));
	FOR(i,1,m*2) FOR(j,1,m*2) dis[i][j]=d[n]; 
	FOR(i,1,m){
		scanf("%d%d%lld",&p[i*2-1],&p[i*2],&w);upd(i*2-1,i*2,w); 
		if (pos[p[i*2-1]]) upd(pos[p[i*2-1]],i*2-1,0);pos[p[i*2-1]]=i*2-1;
		if (pos[p[i*2]]) upd(pos[p[i*2]],i*2,0);pos[p[i*2]]=i*2;
	}m*=2;
	FOR(i,1,m) dis[i][i]=0;
	FOR(i,1,m) FOR(j,1,m) upd(i,j,DIS(p[i],p[j]));
	FOR(k,1,m)
		FOR(i,1,m)
			FOR(j,1,m) upd(i,j,dis[i][k]+dis[k][j]);
	int q;
	scanf("%d",&q);
	while (q--){
		int u,v;
		scanf("%d%d",&u,&v);
		LL ans=DIS(u,v);
		FOR(i,1,m) FOR(j,1,m) ans=min(ans,dis[i][j]+DIS(u,p[i])+DIS(p[j],v));
		printf("%lld\n",ans);
	}
}
/*
*/
