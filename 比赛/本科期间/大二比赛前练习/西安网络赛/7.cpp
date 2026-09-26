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
const LL maxn=5e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

vector<int> edge[maxn];
int dep[maxn],fa[maxn][20];
int val[maxn][207];//œÚ…œ
int kthfa(int x,int len){
	int i;
	REP(i,20) if (len&(1<<i)) x=fa[x][i];
	return x;
}
void dfs(int x,int depth){
	dep[x]=depth;
	int i,k;
	rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
	rep(k,1,200) val[x][k]=val[x][0]^val[kthfa(x,k)][k];
	for (int v:edge[x]){
		if (v==fa[x][0]) continue;
		fa[v][0]=x;
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
int main(){
	int n,q;
	while (~scanf("%d%d",&n,&q)){
		int i;
		REP(i,n-1){
			int u,v,l;
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		FOR(i,1,n) scanf("%d",&val[i][0]);
		dfs(1,1);
		REP(i,q){
			int u,v,k;
			scanf("%d%d%d",&u,&v,&k);
			int f=lca(u,v),ans=0;
//			printf("u,v,f=%d %d %d\n",u,v,f);
			int nowlen=dep[u]+dep[v]-2*dep[f],Ulen=0,Vlen=0;
			v=kthfa(v,nowlen-nowlen/k*k);
//			printf("->u,v,f=%d %d %d\n",u,v,f);
			if (k<200){
				if (dep[u]>=dep[f]){
					Ulen=(dep[u]-dep[f]+k)/k*k;
					ans^=val[u][k]^val[kthfa(u,Ulen)][k];
				}if (dep[v]>dep[f]){
					Vlen=(dep[v]-dep[f]+k-1)/k*k;
					ans^=val[v][k]^val[kthfa(v,Vlen)][k];
				}
//				printf("U,V len=%d : %d\n",Ulen,Vlen);
			}else{
				while (dep[u]>=dep[f]) ans^=val[u][0],u=kthfa(u,k),Ulen+=k;
				while (dep[v]>dep[f]) ans^=val[v][0],v=kthfa(v,k),Vlen+=k;
			}
			printf("%d\n",ans);
		}
		FOR(i,1,n) edge[i].clear();
	}
}
/*
5 6
1 5
4 1
2 1
3 2
19
26
0
8
17
5 5 1
1 3 2
3 2 1
5 4 2
3 4 4
1 4 5

6 6
1 2
1 3
3 4
3 5
3 6
1 2 3 4 5 6
2 4 2
2 5 2
2 6 2
4 2 2
5 2 2
6 2 2
*/
