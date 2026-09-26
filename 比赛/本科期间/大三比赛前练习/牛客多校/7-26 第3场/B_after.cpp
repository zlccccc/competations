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
template<typename T>inline void mod_(T &A,ll B=M) {A%=M; A+=M; A%=M;}
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

LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m) {
	return fac[n]*inv[m]%M*inv[n-m]%M;
}
vector<int> sons,have,edge[maxn];
int sz[maxn];
int cnt[maxn],all;//C(x,k)
ll ans[maxn];
void dfs(int x,int fa) {
	sz[x]=1;
	for (int v:edge[x]) if (v!=fa) {
			dfs(v,x),sz[x]+=sz[v];
		} sons.clear();
	for (int v:edge[x]) if (v!=fa) {
			sons.push_back(sz[v]);
		} if (sz[x]!=n) sons.push_back(n-sz[x]);
	if (sons.size()>2) {
		int i,j; all++;
		REP(i,(int)sons.size()) rep(j,i+1,(int)sons.size()) cnt[sons[i]+sons[j]]--;
		REP(i,(int)sons.size()) cnt[sons[i]]+=sons.size()-1-1;
	}
}
int TaskA() {
	int i,j;
	scanf("%d",&n);
	FOR(i,1,n-1) {
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} dfs(1,0);
	FOR(i,1,n) ans[i]=n*C(n-1,i-1)%M;//choose this
	FOR(i,3,n) add_(ans[i],all*C(n-1,i)%M);
	// printf("all=%d\n",all);
	// FOR(i,1,n) printf("%d ",cnt[i]); puts("");
	FOR(i,3,n) if (cnt[i]) {
		FOR(j,3,i)(ans[j]+=C(i,j)*cnt[i])%=M;
	} FOR(i,1,n) {
		mul_(ans[i],powMM(C(n,i)%M,M-2)); mod_(ans[i]);
	} FOR(i,1,n) printf("%lld\n",ans[i]);
	return 0;
}
void initialize() {
	int i;
	fac[0]=1;
	FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*
*/
