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
const LL maxn=1e5+107;
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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
// int n,m,q;
// char str[maxn];//倒着的

struct node{
	int l,r;
	ll sum; int cnt;
}T[maxn*100]; int tot;
int root[maxn];
int MAX=1e9+7;
void insert(int &x,int pos,int L,int R){
	// printf("insert: %d\n",pos);
	T[++tot]=T[x]; x=tot;
	T[x].cnt++; T[x].sum+=pos;
	if (L==R) return;
	int mid=(L+R)/2;
	if (pos<=mid) insert(T[x].l,pos,L,mid);
	if (mid<pos) insert(T[x].r,pos,mid+1,R);
}
ll query(int x,int y,int &k,int L,int R) {
	if (x==y||!k) return 0;
	// printf("query: %d; %d ; %d %d %d %d\n",x,y,k,L,R);
	if (L==R) {
		int div=min(k,T[y].cnt-T[x].cnt);
		k-=div; return (ll) div*L;
	} int C=T[T[y].r].cnt-T[T[x].r].cnt;
	int mid=(L+R)/2;
	if (C<=k) {
		k-=C;
		return query(T[x].l,T[y].l,k,L,mid)+T[T[y].r].sum-T[T[x].r].sum;
	} else {
		return query(T[x].r,T[y].r,k,mid+1,R);
	}
}
ll all[maxn];
int ql[maxn*5],qr[maxn*5],qk[maxn*5];
int A[maxn];
ll ans[maxn*5];
int main() {
	int n,m;
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) {
		scanf("%d",&A[i]);
		all[i]=all[i-1]+A[i];
	} FOR(i,1,m){
		scanf("%d%d%d",&ql[i],&qr[i],&qk[i]);
		ans[i]=all[qr[i]]-all[ql[i]-1];
	} int k;
	rREP(k,31){
		MAX=1<<(k+1); tot=0;
		FOR(i,1,n) {
			root[i]=root[i-1]; 
			while ((A[i]-A[i]/2)>=(1<<k)) {
				// printf("insert: %d\n",A[i]-A[i]/2);
				insert(root[i],A[i]-A[i]/2,1,MAX); A[i]/=2;
			}
		} FOR(i,1,m) if (qk[i]){
			// printf("k=%d query %d-%d %d: %lld\n",k,ql[i],qr[i],qk[i],query(root[ql[i]-1],root[qr[i]],qk[i],1,MAX));
			ans[i]-=query(root[ql[i]-1],root[qr[i]],qk[i],1,MAX);
		}
	}
	FOR(i,1,m) printf("%lld\n",ans[i]);
}
/*
5 1
2 4 7 9 7
1 3 2
*/