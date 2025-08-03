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
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
int n,m,q;
// char str[maxn];

vector<pair<int,ll> > edge[maxn*2];
priority_queue<pair<ll,int> > Q;
ll dis[maxn*2];
int A[maxn];
int main() {
	int i,j,k;
	scanf("%d%d%d",&n,&m,&k);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,n) {
		ll T=max(0,A[i]-A[1]-k);
		edge[i].push_back(make_pair(i+n,T*T));
	}
	FOR(i,1,m){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		edge[u+n].push_back(make_pair(v,w));
		edge[v+n].push_back(make_pair(u,w));
	}
	FOR(i,1,n+n) dis[i]=INFF; dis[1]=0;
	Q.push(make_pair(0,1));
	while (Q.size()){
		auto now=Q.top(); Q.pop();
		if (-now.first!=dis[now.second]) continue;
		// printf("%d : %lld\n",now.second,now.first);
		for (auto e:edge[now.second]){
			if (-now.first+e.second<dis[e.first]){
				dis[e.first]=e.second-now.first;
				Q.push(make_pair(-dis[e.first],e.first));
			}
		}
	}
	// FOR(i,1,n) printf("%lld ",dis[i]);
	printf("%lld\n",dis[n+n]);
}
/*
100
2 3 2
2 4 2
2 5 2
2 6 2
*/