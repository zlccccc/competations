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
const LL maxn=1e5+7;
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

const ll MAX=1e12+7;
struct node{
	int l,r; ll val;
}T[maxn*100];
int root,tot;
void pushup(int x){
	T[x].val=0;
	if (T[x].l) T[x].val+=T[T[x].l].val;
	if (T[x].r) T[x].val+=T[T[x].r].val;
}
void update(int &x,ll pos,ll val,ll L,ll R){
	if (!x) x=++tot;
	if (L==R) {T[x].val+=val; return;}
	ll mid=(L+R)/2;
	if (pos<=mid) update(T[x].l,pos,val,L,mid);
	else update(T[x].r,pos,val,mid+1,R);
	pushup(x);
	// printf("upd: %d pos,val=%lld %lld L,R=%lld %lld  val=%lld\n",x,pos,val,L,R,T[x].val);
}
ll query(int &x,ll l,ll r,ll L,ll R){
	if (!x) return 0;
	if (l<=L&&R<=r) return T[x].val;
	ll mid=(L+R)/2,ret=0;
	if (l<=mid) ret+=query(T[x].l,l,r,L,mid);
	if (mid<r) ret+=query(T[x].r,l,r,mid+1,R);
	return ret;
}
int ret;
ll query(int &x,ll sum,ll L,ll R){
	if (!x) return 0;
	if (L==R) return min(T[x].val,sum/L*L);
	ll mid=(L+R)/2;
	if (sum<T[T[x].l].val) return query(T[x].l,sum,L,mid);
	else return T[T[x].l].val+query(T[x].r,sum-T[T[x].l].val,mid+1,R);
}
int query(){
	ll sum=query(root,1,MAX,1,MAX); int ret=0;
	while (sum){
		ll nxt=query(root,sum/2,1,MAX);
		if (query(root,1,nxt-1,1,MAX)<=nxt) ret++;
		// printf("sum=%lld, nxt=%lld, ret=%d\n",sum,nxt,ret);
		sum=nxt;
	} return ret;
}
ll A[maxn];
int main() {
	scanf("%d",&n);
	int i;
	FOR(i,1,n) scanf("%lld",&A[i]);
	FOR(i,1,n) update(root,A[i],A[i],1,MAX);
	scanf("%d",&m);
	printf("%d\n",query());
	FOR(i,1,m){
		int x; ll y;
		scanf("%d%lld",&x,&y);
		update(root,A[x],-A[x],1,MAX);
		A[x]=y;
		update(root,A[x],A[x],1,MAX);
		printf("%d\n",query());
	}
}
/*
5
1 1 1 1 1
10
1 4
*/
