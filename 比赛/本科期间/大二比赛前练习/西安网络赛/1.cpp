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
typedef unsigned long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=19260817;
const LL maxn=3007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

inline LL poww(LL a,LL b){
	LL ret=1;
	for (;b;b>>=1,a=a*a%M)
		if (b&1) ret=ret*a%M;
	return ret;
}
struct node{
	ULL A[70];
	node(){
		int i;
		FOR(i,1,64) A[i]=1ull<<i;
	}
}up[maxn][21],dn[maxn][21],val[maxn];
node mul(node x,node y){
	int i,j,k;
	node ret;
	FOR(i,1,64) ret.A[i]=0;
	FOR(k,1,64){
		FOR(i,1,64) if ((x.A[i]>>k)&1){
			ret.A[i]^=y.A[k];
//			FOR(j,1,64) if ((y.A[k]>>j)&1){
//				1ull<<j;
//				ret.A[i]^=(((x.A[i]>>k)&1)&((y.A[k]>>j)&1))<<j;
//				ret.A[i][j]^=x.A[i][k]&y.A[k][j];
//			}
		}
	}
	return ret;
}
vector<int> edge[maxn];
int dep[maxn],fa[maxn][21];
void dfs(int x,int depth){
	dep[x]=depth;
	int i;
	rep(i,1,20){
		fa[x][i]=fa[fa[x][i-1]][i-1];
		up[x][i]=mul(up[x][i-1],up[fa[x][i-1]][i-1]);
		dn[x][i]=mul(dn[fa[x][i-1]][i-1],dn[x][i-1]);
	}
	for (int v:edge[x]){
		if (v==fa[x][0]) continue;
		fa[v][0]=x;
		up[v][0]=dn[v][0]=val[v];
		dfs(v,depth+1);
	}
}
int lca(int x,int y){
	int i;
	if (dep[x]<dep[y]) swap(x,y);
	rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
	if (x==y) return x;
	rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
ULL seed;
LL POW19[70],POW26[70];
int main(){
	int n,Q;
	LL i;
	FOR(i,1,64) POW19[i]=poww(19ull,i),POW26[i]=poww(26ull,i);
	while (~scanf("%d%d",&n,&Q)){
		int i;
		REP(i,n-1){
			int u,v;
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		seed=0;
		scanf("%llu",&seed);
		int p,q;
		FOR(i,1,n){
			FOR(p,1,64){
				val[i].A[p]=0;
				seed^=seed*seed+15;
				FOR(q,1,64){
					val[i].A[p]^=((seed>>(q-1))&1ull)<<q;
				}
			}
		}
		dfs(1,1);
		REP(i,Q){
			int u,v;
			scanf("%d%d",&u,&v);
			int f=lca(u,v);
			int i,j;
			node UP,DN;
			int len;
			len=dep[u]-dep[f];
			if (len>0) {REP(i,20) if (len&(1<<i)) UP=mul(UP,up[u][i]),u=fa[u][i];}
			len=dep[v]-dep[f];
			if (len>0) {REP(i,20) if (len&(1<<i)) DN=mul(dn[v][i],DN),v=fa[v][i];}
			UP=mul(UP,val[f]);
			node ans=mul(UP,DN);
			LL ANS=0;
			FOR(i,1,64)
				FOR(j,1,64)
					ANS=(ANS+((ans.A[i]>>j)&1)*POW19[i]*POW26[j])%M;
//					ANS=(ANS+ans.A[i][j]*poww(19,i)*poww(26,j))%M;
			printf("%llu\n",ANS);
		}
		FOR(i,1,n) edge[i].clear();
	}
}
/*
*/
