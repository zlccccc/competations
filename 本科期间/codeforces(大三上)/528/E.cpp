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
const LL maxn=2000+107;
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

inline int lowbit(int x) {return x&-x;}
int pre[maxn],now[maxn];
// x to y; x man; y pair
ll fac[maxn];
int n;
inline void add(int sum[],int x,int val) {
	for (; x<=n; x+=lowbit(x)) sum[x]+=val;
}
inline int get(int sum[],int x) {
	int ret=0;
	for (; x; x-=lowbit(x)) ret+=sum[x];
	return ret;
}
ll f[maxn][maxn];
int A[maxn],B[maxn];
bool mark[maxn];
int main() {
	int i,j;
	fac[0]=1;
	FOR(i,1,2000) fac[i]=i*fac[i-1]%M;
	FOR(i,0,2000) {
		f[i][0]=fac[i];//j pair(first), 有序
		FOR(j,1,i) f[i][j]=(f[i][j-1]-f[i-1][j-1]+M)%M;
	} f[0][0]=0;
	// FOR(i,0,10) {
	// 	FOR(j,0,10) printf("%-8lld ",f[i][j]);puts("");
	// }
	scanf("%d",&n);
	int ans=0;
	FOR(i,1,n) {
		FOR(j,1,n) pre[j]=now[j];
		FOR(j,1,n) scanf("%d",&now[j]);
		int all=n; //右侧same对数
		if (i==1) all=0;
		FOR(j,1,n) mark[j]=0,A[j]=B[j]=0;
		FOR(j,1,n) add(A,j,1),add(B,j,1);
		int noww=0;
		FOR(j,1,n) {//D: not same+1的数量
			bool bpre=0;
			if (pre[j]&&pre[j]<now[j]&&!mark[pre[j]]) bpre=1;
			if (pre[j]&&!mark[pre[j]]) {
				all--,mark[pre[j]]=1;
				add(B,pre[j],-1);
			} int y=get(B,now[j]-1);//--
			int x=get(A,now[j]-1)-y-bpre;//not --
			if (i==1) swap(x,y);
			ll way=(ll)x*f[n-j][all]+(ll)y*f[n-j][all-1];
			add_(noww,way%M);
			// printf("pos=%d: %d(%d) %d(%d); way=%lld; noww=%d\n",j,x,all,y,all-1,way,noww);
			if (!mark[now[j]]) {
				if (pre[j]) all--;
				mark[now[j]]=1;
				add(B,now[j],-1);//chosen
			} add(A,now[j],-1);//chosen
		} add_(ans,noww*powMM(f[n][n],(ll)n-i)%M);
	} printf("%d\n",ans);
}
/*
3
3 2 1
1 2 3
2 1 3
*/