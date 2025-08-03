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
template<typename T>inline void add_(T &A,ll B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b,ll MOD=M) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%MOD)
		if (b&1) ret=(LL)ret*a%MOD;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int A[maxn],B[maxn];
pair<ll,ll> val[maxn*4];
pll merge(pll x,pll y){
	pll ret;
	ret.first=x.first+y.first;
	ret.second=min(x.second,y.second+x.first);
	return ret;
}
void build(int x,int l,int r){
	if (l==r){
		val[x].first=A[l]-B[l];
		val[x].second=min(0,min(A[l],A[l]-B[l]));
		return;
	}int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	val[x]=merge(val[x<<1],val[x<<1|1]);
}
pll ret;
void query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) {
		ret=merge(ret,val[x]);
		return;
	} int mid=(L+R)/2;
	if (l<=mid) query(x<<1,l,r,L,mid);
	if (mid<r) query(x<<1|1,l,r,mid+1,R);
}
int main() {
	int _t,T; scanf("%d",&T);
	int n,k;
	FOR(_t,1,T) {
		scanf("%d%d",&n,&k); int i;
		FOR(i,1,n) scanf("%d",&A[i]),A[i+n]=A[i];
		FOR(i,1,n) scanf("%d",&B[i]),B[i+n]=B[i];
		build(1,1,n*2);
		int ans=-1;
		rFOR(i,1,n) {
			ret=make_pair(0,0); query(1,i,i+n-1,1,n*2);
			// printf("%d : %lld %lld\n",i,ret.first,ret.second);
			if (ret.second+k>=0) ans=i;
		} printf("%d\n",ans);
	}
}
/*
*/
