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
const LL maxn=4e5+107;
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

// length=value[i+1]-value[i];
vector<int> value;//[l to r-1]++;//from zero
ll val[maxn*8],lz[maxn*8];
// void build(int x,int l,int r) {
// 	int mid=(L+R)/2;
// 	value[i]=0;
// }
void pushup(int x) {
	val[x]=0;
	val[x]+=val[x<<1];
	val[x]+=val[x<<1|1];
}
void pushdown(int x,int l,int mid,int r) {
	if (lz[x]) {
		val[x<<1]+=(ll)lz[x]*(value[mid+1]-value[l]);//l to mid
		val[x<<1|1]+=(ll)lz[x]*(value[r+1]-value[mid+1]);//mid+1 to r
		lz[x<<1]+=lz[x]; lz[x<<1|1]+=lz[x];
		lz[x]=0;
	}
}
void update(int x,int l,int r,int L,int R) {
	// printf("update: %d %d %d %d %d\n",x,l,r,L,R);
	if (l<=L&&R<=r) {
		val[x]+=value[R+1]-value[L];
		lz[x]++;
		return;
	} int mid=(L+R)/2;
	pushdown(x,L,mid,R);
	if (l<=mid) update(x<<1,l,r,L,mid);
	if (mid<r) update(x<<1|1,l,r,mid+1,R);
	pushup(x);
}
int query(int x,ll pos,int L,int R) {
	// printf("query: %d %lld %d %d; lz=%lld\n",x,pos,L,R,lz[x]);
	if (L==R) return value[L]+(pos-1)/lz[x];
	int mid=(L+R)/2;
	pushdown(x,L,mid,R);
	if (val[x<<1]<pos) {
		pos-=val[x<<1];
		return query(x<<1|1,pos,mid+1,R);
	} else {
		return query(x<<1,pos,L,mid);
	}
}
int root=0;
int X[maxn],Y[maxn];
int main(){
	int i,n;
	scanf("%d",&n);
	ll x1,x2,a1,b1,c1,m1;
	scanf("%lld%lld%lld%lld%lld%lld",&x1,&x2,&a1,&b1,&c1,&m1);
	ll y1,y2,a2,b2,c2,m2;
	scanf("%lld%lld%lld%lld%lld%lld",&y1,&y2,&a2,&b2,&c2,&m2);
	X[1]=x1; X[2]=x2;
	Y[1]=y1; Y[2]=y2;
	FOR(i,3,n) {
		X[i]=(a1*X[i-1]+b1*X[i-2]+c1)%m1;
		Y[i]=(a2*Y[i-1]+b2*Y[i-2]+c2)%m2;
	}
	FOR(i,1,n) {
		int l=min(X[i],Y[i])+1,r=max(X[i],Y[i])+1;
		// printf("query: %d %d\n",l,r);
		value.push_back(l);
		value.push_back(r+1);
	}
	value.push_back(0);
	sort(value.begin(), value.end());
	value.erase(unique(value.begin(), value.end()),value.end());
	int m=value.size()-1;//r
	// printf("m=%d\n",m);
	FOR(i,1,n) {
		int l=min(X[i],Y[i])+1,r=max(X[i],Y[i])+1;
		int posl=lower_bound(value.begin(), value.end(),l)-value.begin();
		int posr=lower_bound(value.begin(), value.end(),r+1)-value.begin()-1;
		// printf("%d %d\n",l,r);
		update(1,posl,posr,1,m);
		printf("%d\n",query(1,(val[1]+1)/2,1,m));
		// system("pause");
	}
}