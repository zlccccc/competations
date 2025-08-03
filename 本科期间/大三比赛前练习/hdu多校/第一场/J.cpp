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
const LL maxn=1e6+7;
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

int H[maxn][2];
int L[maxn],R[maxn],L_back[maxn],R_back[maxn];
void solve(char str[],int L[],int L_back[],int left,int right){
	int i;
	FOR(i,1,n){//H[i]:
		int now=str[i-1]-'0';
		H[i][0]=H[i][1]=INF;
		if (i<left) H[i][0]=0;
		else if (i==left) H[i][0]=0,H[i][1]=3;
		else {
			H[i][0]=H[i-1][now^1]+1;
			H[i][1]=H[i-1][now]+3;
			if (i==left+1) H[i][1]=2;
		} 
	} int pre=0;
	FOR(i,1,n){
		pre^=str[i-1]-'0';
		if (i<=left) L_back[i]=0;
		else L_back[i]=L_back[i-1]+2;
		if (i>left+1&&!pre) L_back[i]+=2;
	} pre=0;
	rFOR(i,1,n){
		pre^=str[i]-'0';
		L[i]=H[i][pre];
	}
}
int TaskA() {
	int i;
	scanf("%d",&n);
	scanf("%s",str+1); str[0]=str[n+1]='0';
	int left,right; left=right=0;
	FOR(i,1,n) if (str[i]-'0') {if (!left) left=i; right=i;}
	if (!right) return 0*puts("0");
	solve(str,L,L_back,left,right);
	reverse(str+1,str+1+n);
	solve(str,R,R_back,n-right+1,n-left+1);
	reverse(R+1,R+1+n);
	reverse(R_back+1,R_back+1+n);
	// FOR(i,1,n) printf("%-10d ",L[i]);puts("");
	// FOR(i,1,n) printf("%-10d ",R[i]);puts("");
	// FOR(i,1,n) printf("%-10d ",L_back[i]);puts("");
	// FOR(i,1,n) printf("%-10d ",R_back[i]);puts("");
	// FOR(i,1,n) printf("%d ",H[i][0]);puts("");
	// FOR(i,1,n) printf("%d ",H[i][1]);puts("");
	ll ans=0;
	FOR(i,1,n){
		int now=min(L[i]+R_back[i],R[i]+L_back[i]);
		add_(ans,(ll)now*i%M);
		// printf("%-10d ",now);
	}
	printf("%lld\n",ans);
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_T();
}
/*
30
3
000
3
111
7
1010101
3
101
5
00100
\sum{i*zi}
0
26
432
*/
