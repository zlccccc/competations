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
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
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

pii T[maxn*4]; int lz[maxn*4];
pii merge(pii x,pii y) {
	pii ret; ret.first=min(x.first,y.first); ret.second=0;
	if (ret.first==x.first) ret.second+=x.second;
	if (ret.first==y.first) ret.second+=y.second;
	return ret;
}
void pushdown(int x) {
	if (lz[x]) {
		T[x<<1].first+=lz[x]; T[x<<1|1].first+=lz[x];
		lz[x<<1]+=lz[x]; lz[x<<1|1]+=lz[x];
		lz[x]=0;
	}
}
void build(int x,int L,int R) {
	if (L==R) {
		T[x].first=0; T[x].second=1;
		lz[x]=0;
		return;
	} int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
	T[x]=merge(T[x<<1],T[x<<1|1]); lz[x]=0;
}
void update(int x,int l,int r,int val,int L,int R) {
	// printf("update: %d (%d %d) %d (%d %d)\n",x,l,r,val,L,R);
	if (l<=L&&R<=r) {
		T[x].first+=val; lz[x]+=val;
		// printf("update_: %d->%d: %d %d; left,right=%d %d %d %d; value=%d\n",L,R,T[x].first,T[x].second,T[x<<1].first,T[x<<1].second,T[x<<1|1].first,T[x<<1|1].second,val);
		return;
	} int mid=(L+R)/2;
	pushdown(x);
	// printf("  update_down: %d->%d: %d %d; left,right=%d %d %d %d. val=%d\n",L,R,T[x].first,T[x].second,T[x<<1].first,T[x<<1].second,T[x<<1|1].first,T[x<<1|1].second,val);
	if (l<=mid) update(x<<1,l,r,val,L,mid);
	if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
	T[x]=merge(T[x<<1],T[x<<1|1]);
	// printf("update: %d->%d: %d %d; left,right=%d %d %d %d val=%d\n",L,R,T[x].first,T[x].second,T[x<<1].first,T[x<<1].second,T[x<<1|1].first,T[x<<1|1].second,val);
}
pii query(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) {
		return T[x];
	} int mid=(L+R)/2; pii ret=make_pair(INF,0);
	pushdown(x);
	if (l<=mid) ret=merge(ret,query(x<<1,l,r,L,mid));
	if (mid<r) ret=merge(ret,query(x<<1|1,l,r,mid+1,R));
	T[x]=merge(T[x<<1],T[x<<1|1]);
	return ret;
}
int A[maxn];
int Smax[maxn],Smin[maxn],topmin,topmax;
map<int,int> MP;
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n,i; ll ans=0;
		scanf("%d",&n);
		FOR(i,1,n) scanf("%d",&A[i]);
		build(1,1,n); MP.clear(); topmin=topmax=0;
		FOR(i,1,n) {
			while (topmax&&A[Smax[topmax]]<A[i]) {
				// printf("changemax:%d-%d %d\n",Smax[topmax-1]+1,Smax[topmax],-A[Smax[topmax]]);
				update(1,Smax[topmax-1]+1,Smax[topmax],-A[Smax[topmax]],1,n); topmax--;
			} Smax[++topmax]=i;
			// printf("changemax2:%d-%d %d\n",Smax[topmax-1]+1,Smax[topmax],A[Smax[topmax]]);
			update(1,Smax[topmax-1]+1,Smax[topmax],A[Smax[topmax]],1,n);
			while (topmin&&A[Smin[topmin]]>A[i]) {
				// printf("changemin:%d-%d %d\n",Smin[topmin-1]+1,Smin[topmin],A[Smin[topmin]]);
				update(1,Smin[topmin-1]+1,Smin[topmin],A[Smin[topmin]],1,n); topmin--;
			} Smin[++topmin]=i;
			// printf("changemin2:%d-%d %d\n",Smin[topmin-1]+1,Smin[topmin],-A[Smin[topmin]]);
			update(1,Smin[topmin-1]+1,Smin[topmin],-A[Smin[topmin]],1,n);
			// printf("change cnt:%d-%d %d\n",MP[A[i]]+1,i,-1);
			update(1,MP[A[i]]+1,i,-1,1,n); MP[A[i]]=i;
			pii should=query(1,1,i,1,n);
			if (should.first==-1) ans+=should.second;
			// printf("%d :%d %d\n",i,should.first,should.second);
			// system("pause");
		}
		printf("Case #%d: %lld\n",_,ans);
	}
}
/*
max-min-cnt=0;
*/