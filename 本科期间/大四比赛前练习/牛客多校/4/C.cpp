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
const LL maxn=3e6+107;
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


int A[maxn],fa[maxn],id[maxn];//id: topo
void buildtree(int n){
	static int S[maxn],top,tot,i;
	tot=top=0;
	FOR(i,1,n){
		int now=0;
		while (top&&A[S[top]]>A[i]){
			if (now) fa[now]=S[top],id[++tot]=now;//pop
			now=S[top];  top--;
		} S[++top]=i;
		if (now) fa[now]=S[top],id[++tot]=now;//pop
	} int now=0;
	while (top){
		if (now) fa[now]=S[top],id[++tot]=now;
		now=S[top]; top--;
	} fa[now]=0; id[++tot]=now;
	reverse(id+1,id+1+n);// 变成正的
}
ll B[maxn],Min[maxn],Max[maxn],Min_[maxn],Max_[maxn];
int ls[maxn],rs[maxn];//
int main() {
	// int T,_; T=1;
	// scanf("%d",&T);
	int n,k,i;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,n) scanf("%lld",&B[i]),B[i]+=B[i-1];
	buildtree(n);
	// FOR(i,1,n) printf("%d %d %d\n",id[i],A[id[i]],fa[id[i]]);//分成两个部分,Ar-Al; A[r]-A[l-1]
	ll ans=-INFF;
	FOR(i,1,n) ls[i]=rs[i]=0;
	FOR(i,0,n) Min[i]=Min_[i]=INFF,Max[i]=Max_[i]=-INFF;
	rFOR(i,1,n) {
		int x=id[i];
		ans=max(ans,A[x]*(max(Max[rs[x]],B[x])-min(B[x-1],Min_[ls[x]])));
		ans=max(ans,A[x]*(min(Min[rs[x]],B[x])-max(B[x-1],Max_[ls[x]])));
		Max[x]=max(Max[x],B[x]); Min[x]=min(Min[x],B[x]);
		Max_[x]=max(Max_[x],B[x-1]); Min_[x]=min(Min_[x],B[x-1]);
		// printf("%d:%d-%d; rsum,lsum=%lld %lld\n",x,ls[x],rs[x],max(Max[rs[x]],B[x]),min(B[x-1],Min_[ls[x]]));
		// printf("%d:%d-%d; rsum,lsum=%lld %lld\n",x,ls[x],rs[x],min(Max[rs[x]],B[x]),max(B[x-1],Min_[ls[x]]));
		if (fa[x]) {
			if (x<fa[x]) ls[fa[x]]=x;
			else rs[fa[x]]=x;
			Max[fa[x]]=max(Max[fa[x]],Max[x]);
			Min[fa[x]]=min(Min[fa[x]],Min[x]);
			Max_[fa[x]]=max(Max_[fa[x]],Max_[x]);
			Min_[fa[x]]=min(Min_[fa[x]],Min_[x]);
		}
	}
	printf("%lld\n",ans);
}
/*
3
-1 -1 -1
1 2 3
*/