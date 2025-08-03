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

vector<pair<int,int> > edge[maxn];
LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m) {
	return fac[n]*inv[m]%M*inv[n-m]%M;
}
int k;
int downval[maxn][15];//k times
int pw[maxn][15];
void dfs(int x,int fa) {
	downval[x][0]=1;
	for (auto e:edge[x]) if (e.first!=fa) {
		int v=e.first,i,id;
		dfs(v,x);
		REP(id,k+1) {
			REP(i,id+1) {
				// printf("add: %d %d(%d this):  %lld\n",id,i,id-i,downval[v][i]*C(id,i)%M*pw[e.second][id-i]%M);
				add_(downval[x][id],downval[v][i]*C(id,i)%M*pw[e.second][id-i]%M);
			}
		}
	}
	// int id;
	// printf("x=%d:\n",x);
	// REP(id,14) printf("%d ",downval[x][id]); puts("");
}
int ans=0;
int upval[maxn][15],pre[maxn][15];//记录pre
void dfs2(int x,int fa) {
	for (auto e:edge[x]) if (e.first!=fa) {
		int v=e.first,i,id;
		REP(id,k+1) {
			pre[v][id]=downval[x][id];
			if (fa) add_(pre[v][id],upval[x][id]);
			REP(i,id+1) add_(pre[v][id],M-downval[v][i]*C(id,i)%M*pw[e.second][id-i]%M);
			REP(i,id+1) add_(upval[v][id],pre[v][i]*C(id,i)%M*pw[e.second][id-i]%M);
		}
		REP(id,k+1) {//least choose one
			REP(i,k-id+1) {
				if (k-id-i==0) continue;//least choose one
				add_(ans,(ll)pre[v][id]*downval[v][i]%M*C(k-1,id)%M*C(k-1-id,i)%M*pw[e.second][k-id-i]%M);
			}
		}
		dfs2(v,x);
	}
	// int id;
	// printf("x=%d: (pre)\n",x);
	// REP(id,14) printf("%d ",pre[x][id]); puts("");
}
int main() {
	int i,n;
	fac[0]=1;
	FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
	FOR(i,1,100000) {
		pw[i][0]=1;
		FOR(k,1,13) pw[i][k]=(ll)pw[i][k-1]*i%M;
	}
	scanf("%d%d",&n,&k);
	// printf("%lld\n",443664176ll*n*n%M);
	FOR(i,1,n-1) {
		int u,v,z;
		scanf("%d%d%d",&u,&v,&z);
		edge[u].push_back(make_pair(v,z));
		edge[v].push_back(make_pair(u,z));
	} dfs(1,0);
	// puts("");
	dfs2(1,0);
	// printf("%d\n",ans);
	printf("%lld\n",2*ans*powMM(n,M-2)%M*powMM(n,M-2)%M);
}