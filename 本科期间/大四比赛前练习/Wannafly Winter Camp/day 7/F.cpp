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
const LL maxn=1e5+1007;
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
char str[maxn];//倒着的

int tot;
int cnt[maxn*40],nxt[maxn*40][2];
int C[maxn][2],D[maxn];//C:之后的为x
inline void insert(int x) {
	int p=0,i;
	rREP(i,31) {
		int c=(x>>i)&1;
		if (!nxt[p][c]) nxt[p][c]=++tot;
		add_(C[i][c],cnt[nxt[p][!c]]);//
		p=nxt[p][c]; cnt[p]++;
	}
}
void getD(int m){
	int i,k;
	FOR(i,1,m){
		REP(k,31) if ((i>>k)&1) D[k]++;
	} 
}

ll dp[107][2];
ll Cnt(ll x) {
	return (x+1)/2;
}
void getd(ll val) {
	for (int i=0; i<=31; i++) {
		ll val=(m>>i);
		if (val==0)break;
		--val;
		ll num=Cnt(val);//为1的个数
		dp[i][1]+=(num<<i);
		dp[i][0]+=((val+1-num)<<i);//把0加了进去
		ll cnt;
//            if(i==0)
		cnt=m-((val+1)<<i)+1;//等于原本值的个数
//            else cnt=m-((val+1)<<i);
		// cout<<"cnt="<<cnt<<endl;
		if (m&(1<<i)) dp[i][1]+=cnt;
		else dp[i][0]+=cnt;
		--dp[i][0];
	}
	for (int i=0; i<=31; i++) D[i]=dp[i][1];
}
int main() {
	int i,k;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) {
		scanf("%d",&k);
		insert(k);
	} int ans=0;
	getd(m);
	// FOR(i,0,10) printf("%d : %d-%d\n",i,C[i][0],C[i][1]);
	// FOR(i,0,10) printf("%d ",D[i]);puts(" << D");
	FOR(i,0,31) {//D:1
		add_(ans,((ll)(m-D[i])*C[i][0]+(ll)D[i]*C[i][1])%M);
	} printf("%d\n",ans);
}
/*
3 153
1 2 3

*/