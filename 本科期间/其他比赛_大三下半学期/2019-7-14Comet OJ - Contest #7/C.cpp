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
const double eps=1e-10;
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

int A[20];
ll ans[1<<16];//ways
ll value[1<<16][16][4];//count_j; j; pj; j*pj;
ll sum[1<<16][16][4];
int C[1<<16];
vector<int> inside[1<<16];
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	C[0]=0;
	rep(_,1,(1<<16)) {
		int k;
		C[_]=C[_>>1]+(_&1);
		REP(k,16) if ((_>>k)&1) inside[_].push_back(k);
	}
	// startTimer();
	assert(T<=10);
	FOR(_,1,T){
		/*to solve the problem*/
		int i,j,t,sta;
		int n;
		scanf("%d",&n);
		int m=1<<n;
		REP(i,n) scanf("%d",&A[i]),A[i]--;
		memset(value,0,sizeof(value));
		memset(sum,0,sizeof(sum));
		memset(ans,0,sizeof(ans));
		// memset(way,0,sizeof(way));//ans must right
		// way[0]=1;
		//calc nxt
		REP(sta,m) {
			i=C[sta];
			rREP(j,n) REP(t,4) sum[sta][j][t]=value[sta][j][t]+sum[sta][j+1][t];//后缀和
			for (int j:inside[(m-1)^sta]) if (i!=A[j]) {//choose this
				// int nxtsta=sta|(1<<j);
				int nxtsta=sta|(1<<j); ll now=0;
				for (int k:inside[nxtsta]){//initial
					value[nxtsta][k][0]+=value[sta][k][0];
					value[nxtsta][k][1]+=value[sta][k][1];
					value[nxtsta][k][2]+=value[sta][k][2];
					value[nxtsta][k][3]+=value[sta][k][3];
				}//choose this
				now-=sum[sta][j+1][0]*(i+1)*(j+1);//j*pj
				now+=sum[sta][j+1][1]*(i+1);//j*pi
				now+=sum[sta][j+1][2]*(j+1);//i*pj
				now-=sum[sta][j+1][3];//i*pi
				//nxt,这个放这里j的贡献
				ll way=sta?sum[sta][0][0]/i:1;
				ans[nxtsta]+=ans[sta]+now;
				// way[nxtsta]+=way[sta];
				value[nxtsta][j][0]+=way;
				value[nxtsta][j][1]+=way*(j+1);
				value[nxtsta][j][2]+=way*(i+1);
				value[nxtsta][j][3]+=way*(i+1)*(j+1);
				// printf("i=%d; j=%d; ans=%lld; nxtsta=%d\n",i,j,ans[sta],nxtsta);
				// printf("%lld %lld %lld %lld\n",value[nxtsta][j][0],value[nxtsta][j][1],value[nxtsta][j][2],value[nxtsta][j][3]);
			}
		}
		printf("%lld\n",ans[m-1]);
	}
	// printTimer();
}
/*
10
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16

*/