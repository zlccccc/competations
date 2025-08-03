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
template<typename T>inline void add_(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void mul_(T &A,ll B) {A=(A*B)%M;}
template<typename T>inline void mod_(T &A,ll B=M) {A%=M; A+=M; A%=M;}
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
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_n_m_q() {while (~scanf("%d%d%d",&n,&m,&q)) TaskA();}
void Task_more_string() {while (~scanf("%s",str)) TaskA();}

vector<int> V;
int sum[maxn*4],lazy[maxn*4];//val:exist
void build(int x,int L,int R) {
	lazy[x]=1;
	if (L==R) {sum[x]=V[R]-V[R-1]; return;}
	int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
	sum[x]=(sum[x<<1]+sum[x<<1|1])%M;
}
void change(int x,int val) {
	mul_(sum[x],val); mul_(lazy[x],val);
}
void pushdown(int x) {
	if (lazy[x]!=1) {
		change(x<<1,lazy[x]);
		change(x<<1|1,lazy[x]);
		lazy[x]=1;
	}
}
void update(int x,int l,int r,int val,int L,int R) {
	if (l<=L&&R<=r) {change(x,val); return;};
	int mid=(L+R)/2;
	pushdown(x);
	if (l<=mid) update(x<<1,l,r,val,L,mid);
	if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
	sum[x]=(sum[x<<1]+sum[x<<1|1])%M;
}
struct node {
	int x,y,p;
	node(int x=0,int y=0,int p=1):x(x),y(y),p(p) {};
} P[maxn];
vector<node> Points;
int TaskA() {
	int i;
	scanf("%d",&n);
	V.clear();
	FOR(i,1,n) {
		int x,y,p,q;
		scanf("%d%d%d%d",&x,&y,&p,&q);
		V.push_back(y);
		P[i]=node(x,y,(ll)p*powMM((ll)q,M-2)%M);
	} sort(P+1,P+1+n,[](node A,node B) {
		if (A.x!=B.x) return A.x>B.x;
		if (A.y!=B.y) return A.y>B.y;
		return A.p<B.p;
	}); P[n+1].x=0;
	V.push_back(0); sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	FOR(i,1,n) P[i].y=lower_bound(V.begin(),V.end(),P[i].y)-V.begin();
	ll ans=0; int N=V.size()-1;
	build(1,1,N);
	FOR(i,1,n) {
		Points.push_back(P[i]);
		if (P[i].x!=P[i+1].x) {
			for (auto now:Points) update(1,1,now.y,(M+1-now.p)%M,1,N);
			ans+=(ll)(P[i].x-P[i+1].x)*(V[V.size()-1]-sum[1])%M;
			Points.clear();
		}
	} mod_(ans);
	printf("%lld\n",ans);
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_T();
}
/*
*/
