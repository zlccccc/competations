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
const LL maxn=3e5+107;
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
int id[maxn],out[maxn],pid[maxn],tot;
void dfs(int u,int fa) {
	id[u]=++tot; pid[tot]=u;
	for (int v:edge[u]) if (v!=fa) dfs(v,u);
	out[u]=tot;
}
ll lz[maxn*4],sum[maxn*4];
ll query(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) return sum[x];
	int mid=(L+R)/2; ll ret=lz[x]*(min(R,r)-max(l,L)+1);
	if (l<=mid) ret+=query(x<<1,l,r,L,mid);
	if (mid<r) ret+=query(x<<1|1,l,r,mid+1,R);
	return ret;
}
void update(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) {
		lz[x]++; sum[x]+=R-L+1;
		return;
	} int mid=(L+R)/2;
	if (l<=mid) update(x<<1,l,r,L,mid);
	if (mid<r) update(x<<1|1,l,r,mid+1,R);
	sum[x]=lz[x]*(R-L+1)+sum[x<<1]+sum[x<<1|1];
}
vector<pair<pair<int,int>,int> > queries[maxn];
ll ans[maxn];
int fa[maxn],L[maxn],R[maxn];
int main() {
	int n,m,q,i;
	scanf("%d%d",&n,&m);
	FOR(i,1,m) {
		int f,v,l,r;
		scanf("%d%d%d%d",&f,&v,&l,&r);
		fa[v]=f; L[v]=l; R[v]=r;
		edge[f].push_back(v);
	}
	FOR(i,1,m+1) if (!fa[i]) dfs(i,0);
	// FOR(i,1,n) printf("%d ",id[i]); puts("id");
	scanf("%d",&q);
	FOR(i,1,q) {
		int x,l,r;
		scanf("%d%d%d",&x,&l,&r);
		queries[id[x]-1].push_back(make_pair(make_pair(l,r),-i));
		queries[out[x]].push_back(make_pair(make_pair(l,r),i));
	} L[1]=1; R[1]=n;
	FOR(i,1,m+1) {
		update(1,L[pid[i]],R[pid[i]],1,n);
		// printf("upd: %d %d\n",L[pid[i]],R[pid[i]]);
		for (auto now:queries[i]) {
			ll nowans=query(1,now.first.first,now.first.second,1,n);
			if (now.second<0) ans[-now.second]-=nowans;
			else ans[now.second]+=nowans;
		}
	}
	FOR(i,1,q) printf("%lld\n",ans[i]);
}
/*
*/