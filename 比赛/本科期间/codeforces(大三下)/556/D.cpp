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
const LL maxn=1e5+107;
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

vector<pair<int,int> > edge[107];
//直接限制某些点不能走...
int fa[107],sz[107];
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
ll val[1<<17][71];
int label[107],id[107];
priority_queue<pair<ll,pair<int,int> > > Q;
int main() {
	int n,m,i,k; ll a,b;
	scanf("%d%d%lld%lld",&n,&m,&a,&b);
	FOR(i,1,n) fa[i]=i,sz[i]=1;
	FOR(i,1,m) {
		int u,v; ll c;
		scanf("%d%d%lld",&u,&v,&c);
		edge[u].push_back(make_pair(v,c));
		edge[v].push_back(make_pair(u,c));
		if (c==a) {
			int x=getfa(u),y=getfa(v);
			if (x==y) continue;
			else fa[x]=y,sz[y]+=sz[x];
		}
	} int N=0;
	FOR(i,1,n) if (getfa(i)==i&&sz[i]>=4) label[i]=N++;
	FOR(i,1,n) if (sz[getfa(i)]>=4) id[i]=1<<label[getfa(i)];
	memset(val,0x3f,sizeof(val));
	val[id[1]][1]=0;
	Q.push(make_pair(0,make_pair(id[1],1)));
	while (Q.size()) {
		pair<ll,pair<int,int> > now=Q.top(); Q.pop();
		ll len=-now.first;
		int sta=now.second.first,x=now.second.second;
		// pr2(sta,N); printf("%d : %lld\n",x,len);
		if (val[sta][x]!=len) continue;
		for (pair<int,int> e:edge[x]) {
			int l=e.second,v=e.first;
			if (l==b&&((sta&id[v])||(getfa(x)==getfa(v)))) continue;
			if (val[sta|id[v]][v]>l+len) {
				val[sta|id[v]][v]=l+len;
				Q.push(make_pair(-l-len,make_pair(sta|id[v],v)));
			}
		}
	}
	FOR(i,1,n) {
		ll ans=INFF;
		REP(k,1<<N) ans=min(ans,val[k][i]);
		printf("%lld ",ans);
	}
 }
/*
*/