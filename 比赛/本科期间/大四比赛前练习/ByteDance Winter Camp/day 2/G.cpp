#include<bits/stdc++.h>
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
using namespace std;
typedef pair<int,int> P;
//=1(1+0): first: xx_down(x)  ; next: from this
//=0(1+1): first: pii_now(u-v); next: from this
const int maxn=10007;
P now[maxn*2007],down[maxn*2007]; int tot;//this,this-down
int n,k;
int sz[maxn];
P dp[maxn][507][3],more[507][3];
vector<int> edge[maxn];
void dfs(int x,int fa) {
	sz[x]=1; int i;
	FOR(i,0,k) dp[x][i][0]=dp[x][i][1]=dp[x][i][2]=P{0,0};
    dp[x][0][1]=P{1,++tot}; now[tot]=P{x,0}; down[tot]=P{0,0};
    dp[x][0][2]=P{1,++tot}; now[tot]=P{x,x}; down[tot]=P{0,0};
	for (int v:edge[x]) if (v!=fa) {
			dfs(v,x); int i,j,a,b;
			FOR(i,0,min(k,sz[x]+sz[v])) FOR(a,0,2) more[i][a]=dp[x][i][a];//not
			FOR(i,0,min(k,sz[x])) {
				FOR(j,0,min(k-i,sz[v])) {
					FOR(a,0,2) FOR(b,0,min(2-a,1)) {
						if (dp[x][i][a].first+dp[v][j][b].first+(!a&&b)>more[i+j][a+b].first) {
							more[i+j][a+b]=P{dp[x][i][a].first+dp[v][j][b].first+(!a&&b),++tot};
							int A=dp[x][i][a].second,B=dp[v][j][b].second;
							if (A&&B) {
								if (a&b) now[tot]=P{now[A].first,now[B].first};
								else if (a==1) now[tot]=P{now[A].first,0};
								else if (b==1) now[tot]=P{now[B].first,0};
								else now[tot]=P{0,0};
								down[tot]=P{A,B};
							} else tot--,more[i+j][a+b].second=A|B;
						}
					}
				}
			} sz[x]+=sz[v];
			FOR(i,0,min(k,sz[x])) FOR(a,0,2) dp[x][i][a]=more[i][a];
		} FOR(i,0,min(k,sz[x])) dp[x][i+1][0]=max(dp[x][i+1][0],dp[x][i][2]);
	// printf("dfs %d : %d\n",x,sz[x]);
	// FOR(i,0,min(k,sz[x])) printf("%d ",dp[x][i][0].first); puts("<-0");
	// FOR(i,0,min(k,sz[x])) printf("%d ",dp[x][i][1].first); puts("<-1");
	// FOR(i,0,min(k,sz[x])) printf("%d ",dp[x][i][2].first); puts("<-2");
} bool mark[maxn*2007];
int main() {
	int i;
	while (~scanf("%d%d",&n,&k)&&(n||k)) {
		k=min(k,n);
		FOR(i,1,n) edge[i].clear();
		FOR(i,1,n-1) {
			int u,v;
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		} tot=0; dfs(1,0);
		FOR(i,1,tot) mark[i]=0;
		mark[dp[1][k][0].second]=1;
		rFOR(i,1,tot) if (mark[i]) mark[down[i].first]=mark[down[i].second]=1;
		printf("%d\n",dp[1][k][0].first);
//        printf("%d\n",dp[1][k][0].second);
		int all=0;
		FOR(i,1,tot) if (mark[i]&&now[i].second) all++;
		assert(tot<=maxn*2000);
		printf("%d\n",all);
		assert(all<=k);

//        FOR(i,1,tot) if (mark[i]) printf("%d ",i); puts("<- activate");
		FOR(i,1,tot) if (mark[i]&&now[i].second) printf("%d %d\n",now[i].first,now[i].second);
		int x;
		FOR(x,1,n) FOR(i,0,k) dp[x][i][0]=dp[x][i][1]=dp[x][i][2]=P{0,0};
		FOR(i,1,tot) now[i]=down[i]=P{0,0},mark[i]=0; tot=0;
	}
	return 0;
}
/*
8 1
1 2
2 3
3 4
4 5
5 6
3 7
4 8

5 2
1 2
1 3
1 4
1 5

3 1
1 2
1 3

0 0
*/