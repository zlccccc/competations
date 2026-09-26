#include <sstream>
#include <fstream>
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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

map<pii,int> MP;
vector<int> id;
int fa[maxn][21],dep[maxn];
ll len[maxn];
bool mark[maxn];
vector<pii> edge[maxn];
void dfs(int x,int father,int depth,ll length){
	fa[x][0]=father; dep[x]=depth; mark[x]=1; len[x]=length;
	int i; rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
	for (auto now:edge[x]){
		int v=now.first,len=now.second;
		if (v==father) continue;
		if (mark[v]){
			id.push_back(v); id.push_back(x);
			pii p=make_pair(x,v);
			if (!MP.count(p)) MP[p]=len;
			else MP[p]=min(MP[p],len);
			p=make_pair(v,x);
			if (!MP.count(p)) MP[p]=len;
			else MP[p]=min(MP[p],len);
			continue;
		} dfs(v,x,depth+1,length+len);
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
ll dis(int x,int y){
	return len[x]+len[y]-2*len[lca(x,y)];
}
ll dist[107][107];
ll disu[47],disv[47];
int main() {
	int i,j,k;
	scanf("%d%d",&n,&m);
	FOR(i,1,m){
		int u,v,len;
		scanf("%d%d%d",&u,&v,&len);
		edge[u].push_back(make_pair(v,len));
		edge[v].push_back(make_pair(u,len));
	} dfs(1,0,0,0);
	sort(id.begin(), id.end());
	id.erase(unique(id.begin(), id.end()), id.end());
	m=id.size();
	REP(i,m) REP(j,m){
		dist[i][j]=dis(id[i],id[j]);
		pii p=make_pair(id[i],id[j]);
		if (MP.count(p)) dist[i][j]=min(dist[i][j],(ll)MP[p]);
	} REP(k,m) REP(i,m) REP(j,m) min_(dist[i][j],dist[i][k]+dist[k][j]);
	scanf("%d",&q);
	while (q--){
		int u,v;
		scanf("%d%d",&u,&v);
		ll ans=dis(u,v);
		REP(i,m) disu[i]=dis(u,id[i]),disv[i]=dis(v,id[i]);
		REP(i,m) REP(j,m) min_(ans,dist[i][j]+disu[i]+disv[j]);
		printf("%lld\n",ans);
	}
}
/*
*/
