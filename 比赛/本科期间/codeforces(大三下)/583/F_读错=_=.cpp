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
const LL maxn=3e5+107;
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

struct Tnode{
	struct node{
		int l,r; ll val;
	}T[maxn*60];
	int root; int tot;
	void pushdown(int x) {
		if (!T[x].l) T[x].l=++tot;
		if (!T[x].r) T[x].r=++tot;
		T[T[x].l].val+=T[x].val;
		T[T[x].r].val+=T[x].val;
	}
	void update(int &x,int l,int r,int val,int L=0,int R=INF) {
		// printf("update: %d %d\n",L,R);
		if (!x) x=++tot;
		if (l<=L&&R<=r) {
			T[x].val+=val; return;
		} int mid=(L+R)/2;
		// pushdown(x);
		if (l<=mid) update(T[x].l,l,r,val,L,mid);
		if (mid<r) update(T[x].r,l,r,val,mid+1,R);
	}
	LL query(int x,int pos,int L=0,int R=INF) {
		if (!x) return 0;
		if (L==R) return T[x].val;
		LL ret=0; int mid=(L+R)/2;
		pushdown(x);
		if (pos<=mid) ret+=query(T[x].l,pos,L,mid);
		if (mid<pos) ret+=query(T[x].r,pos,mid+1,R);
		return ret;
	}
}T[2];
void update(int l,int r,ll k,ll b) {//l->r +=x+b
	printf("update: %d->%d %lld %lld\n",l,r,k,b);
	printf(" small upd: %d->%d %lld %lld\n",l,r,k,-(l-1)*k+b);
	T[0].update(T[0].root,l,r,k);
	T[1].update(T[1].root,l,r,b);
}
int m;
void Update(int l,int r,ll k,ll b) {
	printf("initial_update: %d %d %lld %lld\n",l,r,k,b);
	if (l<m&&m<r) {
		update(l,m,k,b);
		update(1,r-m,k,b+m*k);
	} else if (m<=l){
		update(l-m,r-m,k,b+m*k);
	} else {
		update(l,r,k,b);
	}
}
int main() {
	int i,j,n;
	scanf("%d%d",&m,&n);
	FOR(i,1,n) {
		int k;
		scanf("%d",&k);
		int mid=k+(m/2),r=k+m;
		Update(k,mid,1,-k);//x-y
		Update(mid+1,r,-1,k+m);//x-y
	}
	FOR(i,1,n) {
		int k;
		scanf("%d",&k);
		printf("%lld ",(ll)k*T[0].query(T[0].root,k)+T[1].query(T[1].root,k));
	}
}
/*
10 1 5 5
10 4 6

*/