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
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_n_m_q() {while (~scanf("%d%d%d",&n,&m,&q)) TaskA();}
void Task_more_string() {while (~scanf("%s",str)) TaskA();}

int T[maxn*4],lazy[maxn*4];
inline void change(int x,int val){
	T[x]+=val; lazy[x]+=val;
}
inline void pushup(int x){
	T[x]=min(T[x<<1],T[x<<1|1]);
}
inline void pushdown(int x){
	if (lazy[x]){
		change(x<<1,lazy[x]); change(x<<1|1,lazy[x]);
		lazy[x]=0;
	}
}
void update(int x,int l,int r,int val,int L,int R){
	if (l<=L&&R<=r) {change(x,val); return;}
	int mid=(L+R)/2;
	pushdown(x);
	if (l<=mid) update(x<<1,l,r,val,L,mid);
	if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
	pushup(x);
}
inline int lowbit(int x){return x&-x;}
int cnt[maxn];
inline void add(int x){
	for (;x<=n;x+=lowbit(x)) cnt[x]++; 
}
inline int get(int x){
	int ret=0;
	for (;x;x-=lowbit(x)) ret+=cnt[x];
	return ret;
}
int A[maxn],B[maxn];
int id[maxn],all;
int TaskA() {
	int i; ll ans=0;
	scanf("%d",&n); m=n/2+1;
	FOR(i,1,n/2) {
		scanf("%d",&A[i]);
		id[A[i]]=i+1;
		add(A[i]); ans+=i-get(A[i]);
		update(1,i+1,m,1,1,m);
	}
	// printf(" init: %lld\n",ans);
	for(i=1;i<=n+1;i+=2){//i*2-1
		ans+=T[1]+all;
		// printf("%d:  %d + %d = %d\n",i,T[1],all,T[1]+all);
		if (i<=n) all++,update(1,id[i+1],m,-2,1,m);
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
	Task_one();
}
/*
*/
