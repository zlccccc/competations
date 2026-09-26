#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const double eps=0.000001;

int n,m,T,q;
int i,j;
struct node{
	int u,v,len;
}E[500007];
vector<pair<int,int> > edge[maxn];
int dfs(int x,int fa,int len){
	int ret=1;
	for (pair<int,int> P:edge[x])
		if (P.first!=fa&&P.second<len) ret+=dfs(P.first,x,len);
	return ret;
}
bool cmp(node a,node b){
	return a.len<b.len;
}
int fa[maxn];
int getfather(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfather(fa[x]);
}
LL val[maxn],U[maxn],V[maxn];
LL ans[maxn];
int tot;
int main()
{
	int x=0;
	while (~scanf("%d%d",&n,&m)){
		REP(i,m){
			scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].len);
			E[i].u++;E[i].v++;
		}
		sort(E,E+m,cmp);
		tot=0;
		FOR(i,1,n) fa[i]=i;
		REP(i,m){
			int x=getfather(E[i].u),y=getfather(E[i].v);
			if (x==y) continue;
			else{
				fa[x]=y;
				U[tot]=E[i].u;
				V[tot]=E[i].v;
				val[tot]=E[i].len;
				tot++;
//				printf("%d->%d %d\n",E[i].u,E[i].v,E[i].len);
				edge[E[i].u].push_back(make_pair(E[i].v,E[i].len));
				edge[E[i].v].push_back(make_pair(E[i].u,E[i].len));
			}
		}
		rREP(i,n-1){
			ans[i]=dfs(U[i],0,val[i])*dfs(V[i],0,val[i])*2;
		}
		rREP(i,n-2) ans[i]+=ans[i+1];
//		REP(i,n) printf("%d ",val[i]);puts("");
//		REP(i,n) printf("%d ",ans[i]);puts("");
		scanf("%d",&q);
		while (q--){
			int t;
			scanf("%d",&t);
			printf("%lld\n",ans[lower_bound(val,val+n-1,t)-val]);
		}
		FOR(i,1,n) edge[i].clear();
		REP(i,n) val[i]=ans[i]=0;
	}
    return 0;
}
/*
*/
