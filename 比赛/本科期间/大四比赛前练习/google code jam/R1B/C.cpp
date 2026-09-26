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

// lower_than X+K - lower_than X-K-1
inline int lowbit(int x){
	return x&-x;
}
int T[maxn];
void update(int x,int val) {//pos(change)
	for (;x<=100010;x+=lowbit(x)) T[x]=val; 
}
inline int get(int x) {
	x=max(x,0);
	int ret=0; 
	for (;x;x-=lowbit(x)) ret=max(ret,T[x]);
	return ret;
}
int A[maxn],B[maxn];
int L[maxn],R[maxn];
int L_[maxn],R_[maxn];
int L__[maxn],R__[maxn];
void getans(int x){
	int i;
	FOR(i,1,n) {
		
	}
}
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n,k,i;
		scanf("%d%d",&n,&k);
		FOR(i,1,n) scanf("%d",&A[i]);
		FOR(i,1,n) scanf("%d",&B[i]); //第一个大于这个的位置->小于的位置
		FOR(i,1,n) L[i]=get(A[i]),update(A[i],i);
		FOR(i,1,n) update(A[i],0);
		reverse(A+1,A+1+n);
		FOR(i,1,n) R[i]=n+1-get(A[i]+1),update(A[i],i);
		FOR(i,1,n) update(A[i],0);
		reverse(A+1,A+1+n);
		reverse(R+1,R+1+n);
		int ans=0;
		FOR(i,1,n) printf("%2d-%2d ",L[i],R[i]); puts("");
		//first
		FOR(i,1,n) update(B[i],i),L_[i]=get(A[i]+k-1),L__[i]=get(A[i]-k);
		FOR(i,1,n) update(B[i],0);
		reverse(A+1,A+1+n);
		reverse(B+1,B+1+n);
		FOR(i,1,n) update(B[i],i),R_[i]=n+1-get(A[i]+k-1),R__[i]=n+1-get(A[i]-k);
		FOR(i,1,n) update(B[i],0);
		reverse(A+1,A+1+n);
		reverse(B+1,B+1+n);
		reverse(R_+1,R_+1+n);
		reverse(R__+1,R__+1+n);
		FOR(i,1,n) printf("%2d-%2d ",L_[i],R_[i]); puts("");
		FOR(i,1,n) printf("%2d-%2d ",L__[i],R__[i]); puts("");
		FOR(i,1,n) {
			ans+=(ll)(max(L[i],L__[i])-max(L[i],L_[i]))*(min(R[i],R_[i])-min(R[i],R__[i]));
		}

		// printf("first: %d %d\n",ansx.first,ansy.first);
		printf("Case #%d: %d\n",_,ans);
	}
}
/*
6
4 0
1 1 1 8
8 8 8 8
3 0
0 1 1
1 1 0
1 0
3
3
5 0
0 8 0 8 0
4 0 4 0 4
3 0
1 0 0
0 1 2
5 2
1 2 3 4 5
5 5 5 5 10

6
4 0
8 1 1 1
8 8 8 8
*/