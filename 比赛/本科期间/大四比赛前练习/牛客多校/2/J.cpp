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
const LL maxn=4e7+107;
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

short A[maxn];//3e7
int cnt[maxn];//base
const int maxm=1e6+7;
int L[maxm],R[maxm],len[maxm],len_l[maxm];
int main() {
	int n,i;
	scanf("%d",&n);
	int nxtr,nowr;
	nxtr=nowr=-1;
	FOR(i,1,n) scanf("%d%d",&L[i],&R[i]);
	FOR(i,1,n) {//right_zero
		int more=0,l=L[i],r=R[i];//should_-1_left      
		// nxtr+=r-l+1+1;//should_-1
		int t=min(nxtr,l-1);
		more=nxtr-t; nxtr=t; len[i]=nxtr-nowr;//right;-1 ;//l->r
		nowr=r;//previous
		nxtr=nowr+more+r-l+1+1;
	} nxtr=min(nxtr,(int)1e9-1);
	len[n+1]=nxtr-nowr;//r->nxtr; rightmax
	// 对称
	int nxtl,nowl;
	nxtl=nowl=1e9;
	rFOR(i,1,n) {
		int more=0,l=L[i],r=R[i];//should_-1_left
		// nxtl-=r-l+1+1;
		int t=max(nxtl,r+1);
		more=t-nxtl; nxtl=t; len_l[i]=nowl-nxtl;//right;-1 ;//l->r
		nowl=l;//previous
		nxtl=nowl-(more+r-l+1+1);
	} nxtl=max(nxtl,0);
	len_l[0]=nowl-nxtl;
	int m=0,_,T=0; R[0]=-1; L[n+1]=1e9;
	FOR(i,1,n+1) {
		// printf("i=%d\n",L[i]-R[i-1]-1);
		REP(_,min(len_l[i-1]+len[i],L[i]-R[i-1]-1)) A[++m]=-1,T++;
		// printf("m=%d; len=%d\n",m,max(len_l[i-1],len[i]));
		if (i!=n+1) FOR(_,L[i],R[i]) A[++m]=1;
	}
	// FOR(i,1,m) printf("%d",max((short)0,A[i])); puts("");
	ll ans=0; int nowval=0;
	int base=T,now=0;//base; smaller than
	cnt[base]=1;//zero
	FOR(i,1,m) {
		if (A[i]==1) nowval+=cnt[now+base];//from
		else nowval-=cnt[now+base-1];//from
		// printf("%d : %d %d\n",i,now,nowval);
		ans+=nowval;
		now+=A[i]; cnt[now+base]++;
	}
	printf("%lld\n",ans);
}
/*
2
0 1
3 4

3
0 2
3 4
6 7

1
0 999999

2
0 0
1 999999

2
999999998 999999998
999999999 999999999

1
999999997 999999998

4
2 5
9 11
14 14
19 19

3
2 2
4 6
18 20
*/
