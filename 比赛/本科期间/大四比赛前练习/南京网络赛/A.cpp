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

vector<pair<int,int> > ins[maxn];
vector<pair<pii,pii> > queries[maxn];
int sum[maxn];
inline int lowbit(int x){return x&-x;}
void update(int x,int val,int n) {
	for (;x<=n;x+=lowbit(x)) sum[x]+=val;
}
int query(int x){
	int ret=0;
	for (;x;x-=lowbit(x)) ret+=sum[x];
	return ret;
}
int ans[maxn];
inline int getBitSum(ll x) {
	int ret=0;
	for (;x;x/=10) ret+=x%10;
	return ret;
}
//123
//894
//765
inline ll getValue(ll n,ll x,ll y) {
	//n*n-x-y
	ll r = 0;
	x=n-x+1; y=n-y+1;
	if (x<=y && x+y <= n+1) {
		r = x;
		return  4*(r-1)*n - 4*(r-1)*(r-1) +1 + y-r;
	}
	if (x<=y && x+y >= n+1) {
		r = n- y + 1;
		return 4*(r-1)*n - 4*(r-1)*(r-1) + 1 + n-2*r + 1 + x - r;
	}
	if (x>=y && x+y >= n+1) {
		r = n - x +1;
		return 4*(r-1)*n - 4*(r-1)*(r-1) + 1 + 3*n-6*r + 3 - y + r;
	}
	if (x>=y && x+y <= n+1) {
		r = y;
		return 4*(r-1)*n - 4*(r-1)*(r-1) + 1 + 4*n-8*r + 4  - x + r;
	}
	assert(0);
	return -1;
}
int main() {
	// int i,j;
	// rFOR(j,1,5) {//y->down
	// 	FOR(i,1,5) {//x->right
	// 		printf("%lld ",getValue(5,i,j));
	// 	} puts("");
	// }
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		/*to solve the problem*/
		int i,n,m,p;
		scanf("%d%d%d",&n,&m,&p);
		// startTimer();
		FOR(i,1,n) {
			ins[i].clear(); sum[i]=0;
			queries[i].clear();
		}
		FOR(i,1,m) {
			int x,y;
			//x=n/i+1; y=n%i+1;
			scanf("%d%d",&x,&y);
			ll value=getValue(n,x,y);
			ins[x].push_back(make_pair(y,getBitSum(value)));
		}
		// printTimer();
		FOR(i,1,p) {
			int x0,y0,x1,y1; ans[i]=0;
			scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
			queries[x0-1].push_back(make_pair(make_pair(y0,y1),make_pair(i,-1)));
			queries[x1].push_back(make_pair(make_pair(y0,y1),make_pair(i,1)));
		}
		FOR(i,1,n) {
			for (auto now:ins[i]) update(now.first,now.second,n);
			for (auto now:queries[i]) {
				ans[now.second.first]+=now.second.second*(query(now.first.second)-query(now.first.first-1));
			}
		}
		FOR(i,1,p) printf("%d\n",ans[i]);
	}
}
/*
1
1000000 100000 100000
*/