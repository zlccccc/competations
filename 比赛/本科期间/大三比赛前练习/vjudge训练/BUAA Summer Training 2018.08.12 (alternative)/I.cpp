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

vector<int> edge[maxn];
priority_queue<pair<int,int> > Q;
int have[maxn];
int V[maxn][4];
void bfs(int o){
	while(Q.size()) {
		auto now=Q.top(); Q.pop();
		int x=now.second;
		if (V[x][o]!=-now.first) continue;
		for (int v:edge[x]){
			if (V[v][o]==-1||V[v][o]>V[x][o]+1){
				V[v][o]=V[x][o]+1;
				Q.push(make_pair(-V[v][o],v));
			}
		}
	}
}
int main() {
	int i,k;
	scanf("%d%d%d",&n,&m,&k);
	FOR(i,1,m){
		int o;
		scanf("%d",&o);
		have[o]|=1;
	}
	FOR(i,1,k){
		int o;
		scanf("%d",&o);
		have[o]|=2;
	}
	FOR(i,1,n) {
		int p;
		scanf("%d",&p);
		while (p--){
			int o;
			scanf("%d",&o);
			edge[o].push_back(i);
		}
	}
	memset(V,0xff,sizeof(V));
	FOR(i,1,n) if (have[i]&1){
		V[i][1]=0; Q.push(make_pair(0,i));
	} bfs(1);
	FOR(i,1,n) if (have[i]&2){
		V[i][2]=0; Q.push(make_pair(0,i));
	} bfs(2);
	FOR(i,1,n) if (V[i][1]!=-1&&V[i][2]!=-1){
		V[i][3]=V[i][1]+V[i][2]; Q.push(make_pair(-V[i][3],i));
	} bfs(3);
	// FOR(i,1,n) printf("%d ",V[i][1]);puts("");
	// FOR(i,1,n) printf("%d ",V[i][2]);puts("");
	// FOR(i,1,n) printf("%d ",V[i][3]);puts("");
	if (V[1][3]==-1) puts("impossible");
	else printf("%d\n",V[1][3]);
}
/*
3 1 1
2
3
1 2
2 3 1
1 1

*/
