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

int C[107][107];
int f[2][107][107][2];
int solve() {
	int A,B,C;
	int i,j,k;
	scanf("%d%d%d",&A,&B,&C); C=A+B;
	int now=1,pre=0; memset(f,0,sizeof(f));
	f[now][0][0][0]=1;//cnt1,cnt2,is1,pre
	rREP(k,32) {
		int c=(C>>k)&1;
		swap(pre,now); memset(f[now],0,sizeof(f[now]));
		REP(i,40) REP(j,40) {
			if (c) {
				f[now][i][j+1][1]+=f[pre][i][j][1];//3-2
				f[now][i+1][j][0]+=f[pre][i][j][0];//1-1
				f[now][i][j][1]+=f[pre][i][j][0];//1-0
			} else {
				f[now][i][j+1][0]+=f[pre][i][j][1];//2-2
				f[now][i+1][j][1]+=f[pre][i][j][1];//2-1
				f[now][i][j][0]+=f[pre][i][j][0];//0
			}
		}
	} int a=__builtin_popcount(A),b=__builtin_popcount(B),ans=0;
	FOR(i,0,min(a,b)) {
		ans+=f[now][a+b-i*2][i][0]*::C[a-i][a+b-i*2];
		// printf("%d : %d\n",f[now][a+b-i*2][i][0],::C[a-i][a+b-i*2]);
	} printf("%d\n",ans);
	// ans=0;
	// FOR(i,0,C) if (__builtin_popcount(i)==a&&__builtin_popcount(C-i)==b) ans++;
	// printf("%d\n",ans);
	return 0;
}
int main() {
	int i,j;
	C[0][1]=C[1][1]=C[0][0]=1;
	FOR(j,2,80) {
		C[0][j]=1;
		FOR(i,1,j) C[i][j]=(C[i-1][j-1]+C[i][j-1])%M;
	}// printf("%d\n",C[4][10]);
	int T; scanf("%d",&T);
	while (T--) solve();
}
/*
100
1 2 3
369 428 797
10000 100 10100

100000 100000 100100
*/
