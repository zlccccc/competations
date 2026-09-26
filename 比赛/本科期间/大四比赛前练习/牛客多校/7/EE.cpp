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

struct node{
	int l,r; ll val; int lz;//val=sum
}T[maxn*100]; int tot;
void pushup(int x) {
	T[x].val=0; 
	if (T[x].l) T[x].val+=T[T[x].l].val;
	if (T[x].r) T[x].val+=T[T[x].r].val;
}
void pushdown(int x,int l,int mid,int r) {
	if (!T[x].l) T[x].l=++tot;
	if (!T[x].r) T[x].r=++tot;
	T[T[x].l].val+=(ll)T[x].lz*(mid-l+1);
	T[T[x].l].lz+=T[x].lz;
	T[T[x].r].val+=(ll)T[x].lz*(r-mid);
	T[T[x].r].lz+=T[x].lz;
	T[x].lz=0;
}
void update(int &x,int l,int r,int L,int R) {
	if (!x) x=++tot;
	if (l<=L&&R<=r) {
		T[x].val+=R-L+1;
		T[x].lz++;
		return;
	} int mid=(L+R)/2;
	if (l<=mid) update(T[x].l,l,r,L,mid);
	if (mid<r) update(T[x].r,l,r,mid+1,R);
	pushup(x);
}
int query(int x,ll pos,int L,int R) {
	if (L==R) return L;
	int mid=(L+R)/2;
	pushdown(x,L,mid,R);
	if (T[T[x].l].val<pos) {
		pos-=T[T[x].l].val;
		return query(T[x].r,pos,mid+1,R);
	} else {
		return query(T[x].l,pos,L,mid);
	}
}
int root=0;
int X[maxn],Y[maxn];
const int MAX=1e9+1;
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
		// printf("%d %d\n",l,r);
		update(root,l,r,1,MAX);
		printf("%d\n",query(root,(T[root].val+1)/2,1,MAX));
	}
}