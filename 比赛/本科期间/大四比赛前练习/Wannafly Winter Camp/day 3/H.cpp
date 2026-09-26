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
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
int n,m,q;
// char str[maxn];//倒着的

inline int Add(int A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD); return A;}
struct node {
	int ans[3];//del_sum
	int lazy;
	int l,r;
} T[maxn*100]; int tot;
inline int getsum(int x,int C){
	if (C==0) return x;
	if (C==1) return (ll)x*(x+1)%M*499122177%M;//1/2
	if (C==2) return (ll)x*(x+1)%M*(2*x+1)%M*166374059%M;//1/6
	assert(0); return 0;
}
void merge(node &ret,node A,node B) {
	int i; REP(i,3) ret.ans[i]=(A.ans[i]+B.ans[i])%M;
}
void change(int x,int val,int L,int R) {
	int i; T[x].lazy+=val;
	if (T[x].lazy==0) merge(T[x],T[T[x].l],T[T[x].r]);
	else REP(i,3) T[x].ans[i]=(getsum(R,i)-getsum(L-1,i)+M)%M;
}
void update(int &x,int l,int r,int val,int L,int R) {
	if (!x) x=++tot;
	if (l<=L&&R<=r) {
		change(x,val,L,R);
		// printf("upd %d  %d-%d: %d %d %d %d %d %d\n",x,L,R,T[x].ans0,T[x].ans1,T[x].ans2,T[x].sum0,T[x].sum1,T[x].sum2);
		return;
	} int mid=(L+R)/2;
	if (l<=mid) update(T[x].l,l,r,val,L,mid);
	if (mid<r) update(T[x].r,l,r,val,mid+1,R);
	change(x,0,L,R);
	// printf("upd %d  %d-%d: %d %d %d %d %d %d\n",x,L,R,T[x].ans0,T[x].ans1,T[x].ans2,T[x].sum0,T[x].sum1,T[x].sum2);
}
node query(int x,int l,int r,int L,int R,int upper) {
	if (l<=L&&R<=r) {
		node ret=T[x]; int i;
		if (upper) REP(i,3) ret.ans[i]=(getsum(R,i)-getsum(L-1,i)+M)%M;
		// printf("rete %d  %d %d %d %d %d %d\n",x,ret.ans0,ret.ans1,ret.ans2,ret.sum0,ret.sum1,ret.sum2);
		return ret;
	} node ret=node{0,0,0,0,0,0};
	int mid=(L+R)/2;
	if (l<=mid) merge(ret,ret,query(T[x].l,l,r,L,mid,upper+T[x].lazy));
	if (mid<r) merge(ret,ret,query(T[x].r,l,r,mid+1,R,upper+T[x].lazy));
	// printf("ret %d  %d-%d: %d %d %d %d %d %d\n",x,L,R,T[x].ans0,T[x].ans1,T[x].ans2,T[x].sum0,T[x].sum1,T[x].sum2);
	// printf("rete %d  %d %d %d %d %d %d\n",x,ret.ans0,ret.ans1,ret.ans2,ret.sum0,ret.sum1,ret.sum2);
	return ret;
}
vector<pair<pii,int> > changes[maxn];
int l[maxn],r[maxn];
int root;
int main() {
	scanf("%d%d%d",&n,&m,&q);
	int i,k;
	FOR(i,1,n) scanf("%d%d",&l[i],&r[i]);
	FOR(i,1,q) {
		int lx,ly,rx,ry;
		scanf("%d%d%d%d",&lx,&ly,&rx,&ry);
		changes[lx].push_back(make_pair(make_pair(ly,ry),1));
		changes[rx+1].push_back(make_pair(make_pair(ly,ry),-1));
	}
	int ans=0;
	FOR(i,1,n) {
		for (auto now:changes[i]) {
			update(root,now.first.first,now.first.second,now.second,1,m);
		} node ret=query(1,l[i],r[i],1,m,0);
		// printf("query %d-%d ret: %d %d %d\n",l[i],r[i],ret.ans[0],ret.ans[1],ret.ans[2]);
		REP(k,3) ret.ans[k]=((ll)getsum(r[i],k)-getsum(l[i]-1,k)+M-ret.ans[k]+M)%M;
		ll all=(ll)(M-ret.ans[2]+(ll)(r[i]+l[i])*ret.ans[1]+(ll)ret.ans[0]*(r[i]+1)%M*(M+1-l[i]))%M;
		// printf("query ret: %d %d %d; all=%lld\n",ret.ans[0],ret.ans[1],ret.ans[2],all);
		all=all*powMM((ll)(r[i]-l[i]+2)*(r[i]-l[i]+1)%M,M-2)%M;//div
		// printf("%lld\n",all*powMM((ll)(r[i]-l[i]+2)*(r[i]-l[i]+1)%M,M-2)%M);
		add_(all,all);//2
		add_(ans,all);
		// printf("%d\n",ans);
	}
	printf("%d\n",ans);
}
/*
*/