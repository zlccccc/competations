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
const LL maxn=1e6+107;
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

int rot[6][3][4]={
	{{1,7,17,21},{3,13,19,23},{8,14,15,9}},//right
	{{21,17,7,1},{23,19,13,3},{9,15,14,8}},
	{{10,12,14,21},{11,13,15,20},{16,17,19,18}},//down
	{{21,14,12,10},{20,15,13,11},{18,19,17,16}},
	{{5,3,14,16},{11,2,8,17},{6,7,13,12}},
	{{16,14,3,5},{17,8,2,11},{12,13,7,6}},
};
int ans=0;
void dfs(int n,int A[]) {
	int nxt[24],i,j,k,t;
	int now=0;
	if (A[0]==A[1]&&A[1]==A[2]&&A[2]==A[3]) now++;
	if (A[4]==A[5]&&A[5]==A[10]&&A[10]==A[11]) now++;
	if (A[6]==A[7]&&A[7]==A[12]&&A[12]==A[13]) now++;
	if (A[8]==A[9]&&A[9]==A[14]&&A[14]==A[15]) now++;
	if (A[16]==A[17]&&A[17]==A[18]&&A[18]==A[19]) now++;
	if (A[20]==A[21]&&A[21]==A[22]&&A[22]==A[23]) now++;
	// printf("n=%d; now=%d\n",n,now);
	// printf("1\n");
	// REP(i,24) printf("%d ",A[i]); puts("");
	ans=max(ans,now);
	if (n==0) return;
	REP(i,6) {
		REP(t,24) nxt[t]=A[t];
		REP(j,3) REP(k,4) {
			nxt[rot[i][j][(k+1)&3]]=A[rot[i][j][k]];
		} dfs(n-1,nxt);
	}
}
int main(){
	int n,i;
	// int j,k;
	// REP(i,6) {
	// 	REP(j,3) REP(k,4) {
	// 		printf("%d->%d ",rot[i][j][k],rot[i][j][(k+1)&3]);
	// 	} puts("");
	// }
	while (~scanf("%d",&n)){
		int A[24]; ans=0;
		REP(i,24) scanf("%d",&A[i]);
		// REP(i,24) printf("%d ",A[i]); puts("");
		dfs(n,A);
		printf("%d\n",ans);
	}
}
/*
1
0 0 0 0 1 1 2 2 3 3 1 1 2 2 3 3 4 4 4 4 5 5 5 5
1
0 4 0 4 1 1 2 5 3 3 1 1 2 5 3 3 4 0 4 0 5 2 5 2
2
0 0 1 1 1 4 2 2 0 3 1 4 2 2 0 3 3 3 4 4 5 5 5 5
1
0 0 1 1 1 4 2 2 0 3 1 4 2 2 0 3 3 3 4 4 5 5 5 5
*/