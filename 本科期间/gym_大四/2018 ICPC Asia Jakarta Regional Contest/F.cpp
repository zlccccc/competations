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

int A[maxn],B[maxn];
ll sumA[maxn];
vector<int> tl[maxn];
vector<int> ans;
int main(){
	int n,m,i;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,n) scanf("%d",&B[i]);
	FOR(i,1,n) sumA[i]=A[i]+sumA[i-1];
	int last=upper_bound(sumA+1,sumA+1+n,m)-sumA-1;//last_time
	int la=last,lb=last; ll tb=m;//Ai对应B的时间戳;
	pii maxr=make_pair(0,0);
	// FOR(i,1,last) printf("%lld ",sumA[i]); puts("");
	rFOR(lb,0,last) {//add_it_to_b
		while (la&&(lb==0||A[la]-B[lb]>=tb)) {
			ll now=A[la]-tb;
			if (lb==0||now<maxr.first) {
				printf("first : %d:(%d,%d), %lld\n",la,maxr.first,maxr.second,now);
				tl[maxr.second].push_back(maxr.first);
				tb-=maxr.first;
			} else {
				printf("second : %d:(%d,%d), %lld\n",la,maxr.first,maxr.second,now);
				tl[lb].push_back(now);
				tb-=now;
			} la--;
		} tb-=B[lb];//solved this problem
		maxr=max(maxr,make_pair(B[lb],lb));
		printf("tb=%lld\n",tb);
	} if (tb>0) return 0*puts("-1");
	ll now=0;
	FOR(i,1,n) {
		if (tl[i].size()) reverse(tl[i].begin(),tl[i].end());
		for (int v:tl[i]) {
			now+=v;
			if (now<=m) ans.push_back(now);
		} now+=B[i];
	}
	printf("%d\n",(int)ans.size());
	for (int v:ans) printf("%d ",v);
}
/*
3 20
5 4 11
9 1 1

5 40
5 10 5 10 5
3 4 5 9 4
*/