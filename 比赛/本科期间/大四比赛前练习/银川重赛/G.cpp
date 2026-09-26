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
const LL M=1e9+7;
const LL maxn=1e6+107;
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

vector<int> edge[maxn];
vector<int> ids[maxn];//depth
int dep[maxn],in[maxn],out[maxn],tot;
void dfs(int x,int fa) {
	dep[x]=dep[fa]+1; in[x]=++tot;
	ids[dep[x]].push_back(x);
	for (int v:edge[x]) if (v!=fa) {
		dfs(v,x);
	} out[x]=tot;
}
ll lzk[maxn],lzb[maxn];//y=sum{kx+b}
inline void update(int x,int l,int r,int k,int b,int L,int R) {
	if (l<=L&&R<=r) {
		// printf("  update %d (%d->%d %d-%d): %d %d\n",x,L,R,l,r,k,b);
		lzk[x]+=k; lzb[x]+=b;
		return;
	} int mid=(L+R)/2;
	if (l<=mid) update(x<<1,l,r,k,b,L,mid);
	if (mid<r) update(x<<1|1,l,r,k,b,mid+1,R);
}
ll sumk=0,sumb=0;
inline void query(int x,int pos,int L,int R) {
	sumk+=lzk[x]; sumb+=lzb[x];
	if (L==R) return;
	int mid=(L+R)/2;
	if (pos<=mid) query(x<<1,pos,L,mid);
	else query(x<<1|1,pos,mid+1,R);
}
int ans[maxn];
vector<pair<pii,pii> > changes[maxn*2];
int main() {
	int n,i;
	scanf("%d",&n);
	FOR(i,1,n-1) {
		int u,v; scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} dfs(1,0);
	int q; scanf("%d",&q);
	FOR(i,1,q) {
		int p,d,x;
		scanf("%d%d%d",&p,&d,&x);
		d=min(d,x); d=min(d,n);
		// d+dep[p]-dep[query]
		changes[dep[p]].push_back(make_pair(make_pair(in[p],out[p]),make_pair(-1,x+dep[p])));
		changes[dep[p]+d+1].push_back(make_pair(make_pair(in[p],out[p]),make_pair(1,-x-dep[p])));
	}
	FOR(i,1,n) {
		for (auto now:changes[i]) {
			int l=now.first.first,r=now.first.second;
			int k=now.second.first,b=now.second.second;
			update(1,l,r,k,b,1,n);
			// printf("dep=%d; update:%d %d %d %d\n",i,l,r,k,b);
		}
		for (auto x:ids[i]) {
			sumk=0; sumb=0;
			query(1,in[x],1,n);
			ans[x]=sumk*dep[x]+sumb;
			// printf("dep=%d; query:%d(%d); sumk=%lld; sumb=%lld\n",i,x,in[x],sumk,sumb);
		}
	}
	FOR(i,1,n) printf("%d\n",ans[i]);
}
/*
6
1 2
2 3
4 6
3 4
4 5
4
1 0 10
2 2 10
5 5 10
1 3 2
*/