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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

//++++++++
//++++++--
//++++----//+:b
//++------//-:a
//--------//last_position(a)
ll bias[maxn*4],Max[maxn*4];
void build(int x,int l,int r) {
	bias[x]=Max[x]=0;
	if (l==r) return;
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void update(int x,int l,int r,int val,int L,int R) {
	if (l<=L&&R<=r) {
		bias[x]+=val; Max[x]+=val;
		return;
	} int mid=(L+R)/2;
	if (l<=mid) update(x<<1,l,r,val,L,mid);
	if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
	Max[x]=max(Max[x<<1],Max[x<<1|1])+bias[x];
}
void updatepos(int x,int pos,ll val,int L,int R) {
	if (L==R) {Max[x]=max(Max[x],val); return;}//choose this
	int mid=(L+R)/2;
	if (pos<=mid) updatepos(x<<1,pos,val-bias[x],L,mid);
	if (mid<pos) updatepos(x<<1|1,pos,val-bias[x],mid+1,R);
	Max[x]=max(Max[x<<1],Max[x<<1|1])+bias[x];
}
inline ll query(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) return Max[x];
	int mid=(L+R)/2;
	ll ret=-INFF;
	if (l<=mid) max_(ret,query(x<<1,l,r,L,mid)+bias[x]);
	if (mid<r) max_(ret,query(x<<1|1,l,r,mid+1,R)+bias[x]);
	return ret;
}
struct node{
	int x,y,a,b;
}A[maxn];
vector<int> V;
int getid(int x){
	return lower_bound(V.begin(), V.end(),x)-V.begin()+1;
}
int main() {
	int n;
	while (~scanf("%d",&n)) {
		int i;
		V.clear();
		FOR(i,1,n) scanf("%d%d%d%d",&A[i].x,&A[i].y,&A[i].a,&A[i].b);
		FOR(i,1,n) V.push_back(A[i].y);
		sort(V.begin(), V.end());
		V.erase(unique(V.begin(), V.end()),V.end());
		int m=V.size()+1;//right
		build(1,1,m);
		FOR(i,1,n) A[i].y=getid(A[i].y);
		sort(A+1,A+1+n,[&](node &x,node &y){
			if (x.x!=y.x) return x.x<y.x;
			return x.y>y.y;
		});
		FOR(i,1,n) {//|1|2|3|..
			ll sumpre=query(1,1,A[i].y,1,m);//previous
			// updatepos(1,A[i].y+1,sumpre,1,m);
			update(1,A[i].y+1,m,A[i].b,1,m);
			update(1,1,A[i].y,A[i].a,1,m);
			updatepos()
		}
		printf("%lld\n",Max[1]);
	}
}
/*
6
1 1 1 0
1 2 1 0
2 2 1 0
2 1 0 1
3 1 0 1
3 2 0 1
*/
