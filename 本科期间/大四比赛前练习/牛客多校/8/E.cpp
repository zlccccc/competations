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
const LL maxn=1e7+107;
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
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

vector<int> V;
inline int getid(int x) {
	return lower_bound(V.begin(),V.end(),x)-V.begin();
}
struct node{
	int l,r,u,v;
};
int fa[maxn];
vector<node> edge[27];
vector<pair<int,int> > nodes[27];//changed
inline int getfa(int x,int depth) {
	if (fa[x]==x) return fa[x];
	int y=getfa(fa[x],depth);
	nodes[depth].push_back(make_pair(x,fa[x]));
	if (fa[x]!=y) fa[x]=y;
	return fa[x];
}
int n,ans;
void solve(int dep,int l,int r) {
	// int i;
	// FOR(i,1,n) printf("%d ",getfa(i,dep)); printf(" pos=init=%d-%d\n",l,r);
	for (auto e:edge[dep]) {
		if (e.l<=l&&r<=e.r) {
			// printf("update: %d-%d : %d-%d\n",l,r,e.l,e.r);
			int x=getfa(e.u,dep),y=getfa(e.v,dep);
			if (x!=y) {
				nodes[dep].push_back(make_pair(x,x));
				fa[x]=y;
			}
		}
	}
	if (l==r) {
		// FOR(i,1,n) printf("%d ",getfa(i,dep)); printf(" pos=ok=%d-%d\n",l,r);
		if (getfa(1,dep)==getfa(n,dep)) {
			// printf(" OK : (%d,%d); %d->%d: ok\n",l,r,V[l],V[l+1]);
			ans+=V[l+1]-V[l];
		}
	} else {
		for (auto e:edge[dep]) {//save_position
			getfa(e.u,dep); getfa(e.v,dep);
		}
		// for (int x:nodes[dep]) printf("x=%d ",x);
		int mid=(l+r)/2;
		edge[dep+1].clear();
		nodes[dep+1].clear();
		for (auto e:edge[dep]) {
			if (e.l<=l&&r<=e.r) continue;
			if (e.l<=mid) edge[dep+1].push_back(e);
		}
		solve(dep+1,l,mid);
		edge[dep+1].clear();
		nodes[dep+1].clear();
		for (auto e:edge[dep]) {
			if (e.l<=l&&r<=e.r) continue;
			if (mid<e.r) edge[dep+1].push_back(e);
		}
		solve(dep+1,mid+1,r);
	}
	reverse(nodes[dep].begin(), nodes[dep].end());
	for (auto x:nodes[dep]) fa[x.first]=x.second;
	// FOR(i,1,n) printf("%d ",getfa(i,dep)); printf(" pos=back=%d-%d\n",l,r);
}
int main() {
	int m,i,j;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) fa[i]=i;
	FOR(i,1,m) {
		int l,r,u,v;
		scanf("%d%d%d%d",&u,&v,&l,&r);
		edge[1].push_back(node{l,r+1,u,v});
		V.push_back(l); V.push_back(r+1);
	} sort(V.begin(), V.end());
	V.erase(unique(V.begin(), V.end()),V.end());
	for (auto &e:edge[1]) {
		// printf("%d-%d : %d-%d\n",e.l,e.r,getid(e.l),getid(e.r)-1);
		e.l=getid(e.l); e.r=getid(e.r)-1;
	}
	solve(1,0,V.size()-1);
	printf("%d\n",ans);
}
/*
*/