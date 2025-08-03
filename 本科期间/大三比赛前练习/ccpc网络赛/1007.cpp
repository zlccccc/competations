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

vector<int> V;
struct node{
	ll lval,sum;
	node(ll a=0,ll b=0):lval(a),sum(b){};
}T[maxn*4];
node merge(const node &A,const node &B){
	node ret=A;
	max_(ret.lval,B.lval+A.sum);
	ret.sum+=B.sum;
	return ret;
}
void build(int x,int L,int R){
	if (L==R){
		T[x].sum=V[L]; T[x].lval=max(T[x].sum,0ll);
		return;
	} int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
	T[x]=merge(T[x<<1],T[x<<1|1]);
	// printf("%d-%d : %lld %lld\n",L,R,T[x].lval,T[x].sum);
}
node query(int x,int l,int r,int L,int R){
	if (l>r) return node(0,0);
	// printf("query: %d %d %d %d %d\n",x,l,r,L,R);
	if (l<=L&&R<=r) return T[x];
	int mid=(L+R)/2; node ret=node(0,0);
	if (l<=mid&&mid<r) ret=merge(query(x<<1,l,r,L,mid),query(x<<1|1,l,r,mid+1,R));
	else if (l<=mid) ret=query(x<<1,l,r,L,mid);
	else if (mid<r) ret=query(x<<1|1,l,r,mid+1,R);
	else assert(0);
	// printf("  %d-%d %d-%d: %lld %lld\n",l,r,L,R,ret.lval,ret.sum);
	return ret;
}
int A[maxn];
int main() {
	int T,_t;
	scanf("%d",&T);
	FOR(_t,1,T){
		int i,m,k; ll s;
		scanf("%d%lld%d%d",&n,&s,&m,&k); m--;
		REP(i,n) scanf("%d",&A[i]);
		int g=gcd(n,k),G=n/g;//循环节
		ll ans=0;
		REP(i,g) {
			ll sum=0; int j; V.clear();
			REP(j,G) V.push_back(A[(k*j+i)%n]),sum+=A[(k*j+i)%n];
			REP(j,G) V.push_back(A[(k*j+i)%n]);
			REP(j,G) V.push_back(A[(k*j+i)%n]);
			REP(j,G) V.push_back(A[(k*j+i)%n]);
			// printf("sum=%lld k=%d\n",sum,k);
			// for (int j=0;j<V.size();j++) printf("(%d)%d ",j,V[j]);puts("");
			int N=V.size()-1;
			build(1,1,N);
			for (int k=0;k<G;k++){
				if (m<=N-k){
					max_(ans,V[k]+query(1,k+1,k+m,1,N).lval);
					// printf("query: %d %d\n",k+1,k+m);
					// printf("now=%lld\n",V[k]+query(1,k+1,k+m,1,N).lval);
				} else {
					max_(ans,V[k]+query(1,k+1,N,1,N).lval);
					// printf("query: %d %d\n",k+1,N);//-1
					// printf("now1=%lld\n",V[k]+query(1,k+1,N,1,N).lval);
					max_(ans,V[k]+sum*(m/G-2)+query(1,k+1,k+m%G+G+G,1,N).lval);
					// printf("query: %d %d\n",k+1,k+m%G+G+G);//-1
					// printf("now2=%lld + %lld = %lld\n",V[k]+sum*(m/G-2),query(1,k+1,k+m%G+G+G,1,N).lval,V[k]+sum*(m/G-2)+query(1,k+1,k+m%G+G+G,1,N).lval);
				}
			}
		}
		printf("Case #%d: %lld\n",_t,max(0ll,s-ans));
	}
}
/*

100
3 10 5 2
3 2 1
5 20 6 3
2 3 2 1 5

5 100000000000 100 2
1 -200000000 3 -700000000 1000000000 

5 100000000000 100 2
1 3 1000000000 -200000000 -700000000

5 20 12 3
1 -3 7 2 -5

*/

