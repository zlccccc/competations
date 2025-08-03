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
const LL maxn=5e5+107;
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

//cnt,num
pair<int,int> T[maxn*4];
pii merge(pii A,pii B) {
	pii ret=make_pair(max(A.first,B.first),0);
	if (ret.first==A.first) add_(ret.second,A.second);
	if (ret.first==B.first) add_(ret.second,B.second);
	return ret;
}
void update(int x,int pos,pii val,int L,int R){
	if (L==R) {
		T[x]=merge(T[x],val);
		// printf("update:%d %d\n",T[x].first,T[x].second);
		return;
	} int mid=(L+R)/2;
	if (pos<=mid) update(x<<1,pos,val,L,mid);
	if (mid<pos) update(x<<1|1,pos,val,mid+1,R);
	T[x]=merge(T[x<<1],T[x<<1|1]);
}
pii query(int x,int l,int r,int L,int R) {
	// printf("query:%d %d %d %d %d; %d %d\n",x,l,r,L,R,T[x].first,T[x].second);
	if (l<=L&&R<=r) return T[x];
	int mid=(L+R)/2; pii ret=make_pair(0,0);
	if (l<=mid) ret=merge(ret,query(x<<1,l,r,L,mid));
	if (mid<r) ret=merge(ret,query(x<<1|1,l,r,mid+1,R));
	// printf("ret:%d %d\n",ret.first,ret.second);
	return ret;
}
vector<int> V;

int A[maxn];
pii L[maxn],R[maxn];
int main() {
	int n,i;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&A[i]),V.push_back(A[i]);
	sort(V.begin(), V.end());
	V.erase(unique(V.begin(), V.end()),V.end());
	FOR(i,1,n) A[i]=lower_bound(V.begin(), V.end(),A[i])-V.begin()+1;
	// FOR(i,1,n) printf("%d ",A[i]);
	FOR(i,1,n*4) T[i]=make_pair(0,0);
	FOR(i,1,n) {
		pii now=make_pair(0,1);
		if (A[i]-1) now=merge(now,query(1,1,A[i]-1,1,n));
		L[i]=make_pair(now.first+1,now.second);
		update(1,A[i],L[i],1,n);
	}
	FOR(i,1,n*4) T[i]=make_pair(0,0);
	rFOR(i,1,n) {
		pii now=make_pair(0,1);
		if (A[i]!=n) now=merge(now,query(1,A[i]+1,n,1,n));
		R[i]=make_pair(now.first+1,now.second);
		update(1,A[i],R[i],1,n);
	}
	// FOR(i,1,n) printf("%d:%d %d:%d\n",L[i].first,L[i].second,R[i].first,R[i].second);
	pii ans=make_pair(0,0);
	FOR(i,1,n) ans=merge(ans,L[i]);
	int rev=powMM(ans.second,M-2);
	// printf("ans=%d %d\n",ans.first,ans.second);
	FOR(i,1,n) {
		if (L[i].first+R[i].first-1==ans.first) {
			printf("%lld ",(ll)rev*L[i].second%M*R[i].second%M);
		} else printf("%d ",0);
	}
}