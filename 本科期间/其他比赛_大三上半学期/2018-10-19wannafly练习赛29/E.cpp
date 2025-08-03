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
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+7;
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

int op,l,r,v; ll Ans;
int ans[maxn*4][20],tmp[20],lazy[maxn*4];
void rotate(int x,int v){
	// printf("rotate: %d %d\n",x,cnt);
	int i;
	REP(i,20) tmp[i]=ans[x][(i+v)%20];
	REP(i,20) ans[x][i]=tmp[i];
	lazy[x]+=v; lazy[x]%=20;
}
int A[maxn];
void build(int x,int l,int r){
	int i;
	// printf("build %d : %d %d\n",x,l,r);
	if (l==r){
		REP(i,20) ans[x][i]=(A[l]>>i)&1;
		// printf("%d : %d %d\n",x,l,r);REP(i,20) printf("%d ",ans[x][i]);puts("");
		return;
	} int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	REP(i,20) ans[x][i]=ans[x<<1][i]+ans[x<<1|1][i];
	// printf("%d : %d %d\n",x,l,r);REP(i,20) printf("%d ",ans[x][i]);puts("");
}
void update(int x,int L,int R){
	int i;
	// printf("update %d : %d %d\n",x,L,R);
	if (l<=L&&R<=r){
		if (op==1) rotate(x,v);
		if (op==2) rotate(x,20-v);
		if (op==3) REP(i,20) if ((v>>i)&1) ans[x][i]=R-L+1;
		if (op==4) REP(i,20) if (!((v>>i)&1)) ans[x][i]=0;
		if (op==5) REP(i,20) Ans+=((ll)ans[x][i])<<i;
		// if (op==5) {printf("%d : %d %d\n",x,l,r);REP(i,20) printf("%d ",ans[x][i]);puts("");}
		return;
	}
	int len=R-L+1,mid=(L+R)/2;
	//pushdown
	if (lazy[x]) rotate(x<<1,lazy[x]),rotate(x<<1|1,lazy[x]),lazy[x]=0;
	REP(i,20) {
		if (ans[x][i]==len) ans[x<<1][i]=len-len/2,ans[x<<1|1][i]=len/2;
		else if (ans[x][i]==0) ans[x<<1][i]=0,ans[x<<1|1][i]=0;
	} if (l<=mid) update(x<<1,L,mid);
	if (mid<r) update(x<<1|1,mid+1,R);
	REP(i,20) ans[x][i]=ans[x<<1][i]+ans[x<<1|1][i];
}
int main() {
	scanf("%d%d",&n,&q); int i;
	FOR(i,1,n) scanf("%d",&A[i]);
	build(1,1,n);
	while (q--){
		scanf("%d%d%d%d",&op,&l,&r,&v);
		Ans=0; update(1,1,n);
		if (op==5) printf("%lld\n",Ans);
	}
}
/*
10 100
10112 23536 1305 7072 12730 29518 12315 3459 12435 29055
5 1 1 10
5 2 2 10
5 3 3 10
4 5 10 12373
2 1 6 7
5 4 10 24895
1 1 4 8
5 3 7 7767
5 7 9 6127
4 2 8 30971
5 4 10 2663
1 7 10 1
1 2 9 5
*/
