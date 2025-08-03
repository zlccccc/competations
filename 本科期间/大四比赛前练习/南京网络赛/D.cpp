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

int cnt[maxn],d[maxn];
double dis[maxn],ans[maxn];
vector<int> edge[maxn];
queue<int> Q;
int main() {
	// FOR(i,1,10) printf("%d ",phi[i]);puts("");
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		/*to solve the problem*/
		int n,m,i;
		scanf("%d%d",&n,&m);
		FOR(i,1,n) {
			cnt[i]=dis[i]=ans[i]=d[i]=0;
			edge[i].clear();
		}
		FOR(i,1,m) {
			int u,v; scanf("%d%d",&u,&v);
			edge[v].push_back(u); d[u]++;
		} int x=0;
		FOR(i,1,n) if (!d[i]) Q.push(i);
		while (Q.size()) {
			x=Q.front(); Q.pop();
			if (cnt[x]) {
				dis[x]+=1;//this; self
				dis[x]=dis[x]/cnt[x];

				ans[x]+=1+dis[x]*2;
				ans[x]/=cnt[x];
			} else {
				dis[x]=ans[x]=0;
			}
			// printf("%d: %f %f\n",x,dis[x],ans[x]);
			for (int v:edge[x]) {
				d[v]--; if (!d[v]) Q.push(v);
				dis[v]+=dis[x]+1; cnt[v]++;
				ans[v]+=ans[x]+dis[x]*2+1;
			}
		}
		// printf("%f\n",dis[x]);
		// printf("%f\n",ans[x]);
		printf("%.2f\n",(ans[x]+dis[x])/2);
	}
}
/*
*/