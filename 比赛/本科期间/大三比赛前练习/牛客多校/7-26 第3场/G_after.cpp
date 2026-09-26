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

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e4+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void mul_(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod_(T &A,ll B=M) {A%=M;}
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
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_n_m_q() {while (~scanf("%d%d%d",&n,&m,&q)) TaskA();}
void Task_more_string() {while (~scanf("%s",str)) TaskA();}

vector<int> edge[maxn];
int used[maxn],mask[maxn],dep[maxn];
struct queue {
	int Q[maxn],ST,ED;
	void init() {ST=0; ED=-1;}
	void push(int x) {Q[++ED]=x;}
	int front() {return Q[ST];}
	void pop() {ST++;}
	bool size() {return ED-ST+1;}
} Q,SQ;
int bfs(int start,int len) {
	int ret=0; Q.init(); Q.push(start);
	dep[start]=0; mask[start]=start;
	while (Q.size()) {
		int x=Q.front(); Q.pop(); ret++;//printf("   %d(%d) ",x,ret);
		if (dep[x]==len) continue; 
		for (int v:edge[x]) if (mask[v]&&mask[v]!=start)
			Q.push(v),dep[v]=dep[x]+1,mask[v]=start;
	} return ret-1;
}
ll solve(int k){
	ll ret=1,i;
	// printf("solve: %d\n",k);
	FOR(i,1,n) used[i]=mask[i]=0;
	SQ.init(); SQ.push(1); used[1]=-1;
	while (SQ.size()) {
		int x=SQ.front(); SQ.pop(); mask[x]=-1;
		int cnt=bfs(x,k); if (cnt>=m) return 0;
		ret=ret*(m-cnt)%M;
		// printf("  %d : %d\n",x,cnt);
		for (int v:edge[x]) if (!used[v]) SQ.push(v),used[v]=-1;
	} //printf("%d : %lld\n",k,ret);
	return ret;
}
int TaskA() {
	int i;int D;
	scanf("%d%d%d",&n,&m,&D);
	FOR(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	printf("%lld\n",(solve(D-1)-solve(D)+M)%M);
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*
10 10 5
1 2
2 3
3 4
3 5
5 6
6 7
7 8
8 9
9 10
*/
