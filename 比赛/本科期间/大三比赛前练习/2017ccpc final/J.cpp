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
typedef pair<int,ll> pii;
const ll INF=0x3f3f3f3f3f3f3f3fll;
const int maxn=4000+5;
#define pb push_back
#define mp make_pair
typedef long long ll;
void max_(int &A,int B) {(A<B) &&(A=B);}
vector<pii> edge[maxn];
void addedge(int x,int y,ll c) {
	// printf("%d -> %d  : %d\n",x,y,c);
	edge[x].push_back(make_pair(y,c));
} ll dis[maxn];
int vis[maxn],c[maxn];
int n;
bool solve() {
	queue<int> Q; int i;
	FOR(i,1,n) dis[i]=INF,c[i]=0; dis[0]=0;
	FOR(i,1,n) addedge(0,i,0);
	Q.push(0);
	while (Q.size()) {
		int u=Q.front(); Q.pop(); vis[u]=0;
		for (auto e:edge[u]) {
			int v=e.first,l=e.second;
			if (dis[u]+l<dis[v]) {
				dis[v]=dis[u]+l;
				if (!vis[v]) {
					vis[v]=1; Q.push(v);
					if (++c[v]>n) return 0;
				}
			}
		}
	} return 1;
}
int main() {
	int _t,T; scanf("%d",&T);
	FOR(_t,1,T) {
		int i,m,x;
		scanf("%d%d%d",&n,&m,&x);
		FOR(i,1,n) edge[i].clear();
		FOR(i,1,m) {
			int A,B,C,D;
			scanf("%d%d%d%d",&A,&B,&C,&D);
			addedge(B,C,x-((A!=B)||(C!=D)));
			addedge(D,A,-x-((A!=B)||(C!=D)));
		} FOR(i,2,n) addedge(i,i-1,-1);
		if (!solve()) printf("Case #%d: IMPOSSIBLE\n",_t);
		else {
			printf("Case #%d: ",_t);
			FOR(i,2,n) printf("%I64d%c",dis[i]-dis[i-1]," \n"[i==n]);
		}
	}
}
/*
*/
