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
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const ll INF=0x3f3f3f3f3f3f3f3fll;
const int maxn=4e5+7;
#define pb push_back
#define mp make_pair
typedef long long ll;
void max_(int &A,int B) {(A<B) &&(A=B);}

vector<pair<int,int> > edge[maxn];
int low[maxn],dfn[maxn],vis[maxn],used[maxn],tot;
pii S[maxn]; int top;
set<pii> incir;
void dfs(int x,int fa) {
	low[x]=dfn[x]=++tot; vis[x]=1;
	for (auto e:edge[x]) if (e.first!=fa&&!used[e.second]) {
			int v=e.first; used[e.second]=1;
			S[++top]=make_pair(x,v);
			if (!dfn[v]) {
				dfs(v,x);
				low[x]=min(low[x],low[v]);
				set<pii> S;
				if (dfn[x]<=low[v]) {
					while (1) {
						pii now=::S[top--];
						S.insert(now);
						if (now==make_pair(x,v)) break;
					}
					// printf("S.size=%d\n",(int)S.size());
					// for (auto now:S) printf("S: %d-%d\n",now.first,now.second);
					if (low[v]==dfn[x]) {
						incir.swap(S);
						// for (auto now:S) printf("S: %d-%d\n",now.first,now.second);
					}
				}
			} else if (vis[v]) low[x]=min(low[x],dfn[v]);
		}
}
int _x[maxn],_y[maxn],_z[maxn];
map<pii,int> color;
map<int,int> col[maxn],C;
int main() {
	int _t,T; scanf("%d",&T);
	FOR(_t,1,T) {
		int i,n,m;
		scanf("%d%d",&n,&m);
		FOR(i,1,n) low[i]=dfn[i]=used[i]=0,edge[i].clear(),col[i].clear();
		C.clear(); color.clear(); incir.clear();
		FOR(i,1,n+m) scanf("%d%d%d",&_x[i],&_y[i],&_z[i]);
		FOR(i,1,n) {
			int x=_x[i],y=_y[i];
			edge[x].push_back(make_pair(y,i));
			edge[y].push_back(make_pair(x,i));
		} dfs(1,0);
		int ans=0;//one block
		FOR(i,1,n) col[_x[i]][0]++,col[_y[i]][0]++;
		C[0]+=incir.size();
		printf("Case #%d:\n",_t);
		FOR(i,1,n+m) {
			pii nxt=make_pair(_x[i],_y[i]); int precol=color[nxt];
			pii inv=make_pair(_y[i],_x[i]);
			if (incir.count(nxt)||incir.count(inv)) {
				C[precol]--; if (!C[precol]) C.erase(precol);
			}
			col[_x[i]][precol]--; if (col[_x[i]][precol]) ans++;
			if (col[_x[i]][_z[i]]) ans--; col[_x[i]][_z[i]]++;
			col[_y[i]][precol]--; if (col[_y[i]][precol]) ans++;
			if (col[_y[i]][_z[i]]) ans--; col[_y[i]][_z[i]]++;
			color[nxt]=color[inv]=_z[i];
			if (incir.count(nxt)||incir.count(inv)) C[_z[i]]++;
			if (i>n) {
				if (C.size()==1) printf("%d\n",ans+1);
				else printf("%d\n",ans);
				// printf("ans=%d; incol=%d\n",ans,(int)C.size());
			}
		}
	}
}
/*
*/
