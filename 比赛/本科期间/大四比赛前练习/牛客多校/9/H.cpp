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
const LL maxn=2e5+107;
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
	int l,r;
	int cnt; ll sum;
}T[maxn*32]; int tot;
inline void update(int &x,int y,int pos,int L,int R) {
	x=++tot; T[x]=T[y];
	if (L==R) {
		T[x].cnt++; T[x].sum+=pos;
		return;
	} int mid=(L+R)/2;
	if (pos<=mid) update(T[x].l,T[y].l,pos,L,mid);
	if (mid<pos) update(T[x].r,T[y].r,pos,mid+1,R);
	T[x].sum=T[T[x].l].sum+T[T[x].r].sum;
	T[x].cnt=T[T[x].l].cnt+T[T[x].r].cnt;
	// printf("x=%d; L=%d-%d; CNT=%d; SUM=%lld\n",x,L,R,T[x].cnt,T[x].sum);
}
//每个点: x->x+1
inline long double query(int x,int y,long double sum,ll cnt,int L,int R) {
	// printf("query: %d %d %f %lld:L,R= %d %d (SUM=%lld, CNT=%d)\n",x,y,(double)sum,cnt,L,R,T[x].sum-T[y].sum,T[x].cnt-T[y].cnt);
	if (L==R) {
		if (cnt==0) return L;
		return L+sum/(cnt-(T[x].cnt-T[y].cnt));
	}
	int mid=(L+R)/2;
	long double leftvalue=(T[T[x].l].sum-T[T[y].l].sum)+(cnt-(T[T[x].l].cnt-T[T[y].l].cnt))*(mid+1)-cnt*L;//left to (mid-1)
	// printf("leftvalue=%f\n",(double)leftvalue);
	if (sum>leftvalue) {
		sum-=leftvalue; cnt-=T[T[x].l].cnt-T[T[y].l].cnt;
		return query(T[x].r,T[y].r,sum,cnt,mid+1,R);
	} else return query(T[x].l,T[y].l,sum,cnt,L,mid);
}
const int MAX=INF;
int A[maxn],root[maxn];
int main(){
	int n,q,i;
	scanf("%d%d",&n,&q);
	FOR(i,1,n) {
		scanf("%d",&A[i]);
		update(root[i],root[i-1],A[i],0,MAX);
	} 
	FOR(i,1,q) {
		int l,r,x,y;
		scanf("%d%d%d%d",&l,&r,&x,&y);
		ll all=T[root[r]].sum-T[root[l-1]].sum;
		// printf("all=%lld\n",all);
		printf("%.12f\n",(double)query(root[r],root[l-1],(double)all/y*(y-x),r-l+1,0,MAX));
	}
}
/*
3 3
94 39 9
1 2 16 65
2 2 10 40

*/