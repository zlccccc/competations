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

int mark[maxn];
int f[maxn][2];
void dfs(int x,int y){//used,not_used
	int n,m,w,i;
	vector<pair<int,int> > E;//V:nodes
	vector<int> V;
	if (scanf("%d%d%d",&n,&m,&w)==EOF) exit(0);
	FOR(i,1,m){
		int u,v;
		scanf("%d%d",&u,&v);
		f[u][0]=f[u][1]=0;
		f[v][0]=f[v][1]=0;
		V.push_back(u); V.push_back(v);
		E.push_back(make_pair(u,v));
	} FOR(i,1,w){
		int u,v;
		scanf("%d%d",&u,&v);
		dfs(u,v);
	} sort(V.begin(), V.end());
	V.erase(unique(V.begin(), V.end()),V.end());
	// assert(V.size()==n);
	int status;
	int ret_0=INF,ret_1=INF;
	REP(status,(1<<n)){
		int now=0,okay=1;
		REP(i,n) {
			if ((status>>i)&1){
				now+=f[V[i]][0]+1;
				mark[V[i]]=1;
			}else{
				now+=f[V[i]][1];
				mark[V[i]]=0;
			}
		}
		for (auto e:E){
			if (!mark[e.first]&&!mark[e.second]) okay=0;
		} if (!okay) continue;
		min_(ret_0,now);
		if (mark[y]) min_(ret_1,now);
	} f[x][0]+=ret_0;
	f[x][1]+=ret_1;
}
int main() {
	while (1) {
		f[0][0]=f[0][1]=0; dfs(0,0);
		printf("%d\n",f[0][0]);
	}
}
/*
*/
