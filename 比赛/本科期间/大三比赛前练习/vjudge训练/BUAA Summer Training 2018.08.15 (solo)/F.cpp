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

int have[maxn*4];//not used
vector<int> nodes[maxn];
void build(int x,int L,int R){
	have[x]=0;
	if (L==R) return;
	int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
}
void update(int x,int l,int r,int val,int L,int R){
	if (have[x]) return; //all_okay
	if (l<=L&&R<=r){
		if (L==R) {
			nodes[val].push_back(L);
			have[x]=-1; return;
		}
	} int mid=(L+R)/2;
	if (l<=mid) update(x<<1,l,r,val,L,mid);
	if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
	if (have[x<<1]&&have[x<<1|1]) have[x]=-1;
}
int cnt[maxn];
inline int lowbit(int x){return x&-x;}
struct node{
	int l,r,k;
}Q[maxn];
vector<node> queries[maxn];
inline void add(int x,int val){
	for (;x<=n;x+=lowbit(x)) cnt[x]+=val;
}
inline void add(int l,int r,int val){
	l=max(l,1); r=min(r,n);
	add(l,val); add(r+1,-val);
}
inline int get(int x){
	int ret=0;
	for (;x;x-=lowbit(x)) ret+=cnt[x];
	return ret;
}
int solve() {
	int i;
	scanf("%d%d",&n,&m);
	build(1,1,n);
	FOR(i,1,100000) nodes[i].clear(),queries[i].clear();
	FOR(i,1,m){
		int x,l,k;
		scanf("%d%d%d",&x,&l,&k);
		Q[i].l=x-k; Q[i].r=x+k; Q[i].k=l;
		queries[l].push_back(Q[i]);
	} rFOR(i,1,m) update(1,Q[i].l,Q[i].r,Q[i].k,1,n);
	int ans=0;
	FOR(i,1,100000){
		for (auto now:queries[i]) add(now.l,now.r,1);
		for (auto now:nodes[i]) if (get(now)!=1) {
			ans++;
		}
		for (auto now:queries[i]) add(now.l,now.r,-1);
	} printf("%d\n",ans);
	return 0;
}
int main() {
	int T; scanf("%d",&T);
	while (T--) solve();
}
/*
1
10 7
3 11 0
3 11 2
5 12 1
8 13 2
7 11 2
10 12 1
9 12 0
*/
