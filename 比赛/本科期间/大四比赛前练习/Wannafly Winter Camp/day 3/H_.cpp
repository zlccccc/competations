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
	int sum0,sum1,sum2;
	int ans0,ans1,ans2;
	int lazy;
} T[maxn<<2];
node merge(node A,node B) {
	node ret; ret.lazy=0;
	ret.sum0=Add(A.sum0,B.sum0);
	ret.sum1=Add(A.sum1,B.sum1);
	ret.sum2=Add(A.sum2,B.sum2);
	ret.ans0=Add(A.ans0,B.ans0);
	ret.ans1=Add(A.ans1,B.ans1);
	ret.ans2=Add(A.ans2,B.ans2);
	return ret;
}
void change(int x,int val) {
	T[x].lazy+=val;
	if (T[x].lazy==0&&T[x].sum0!=1){
		T[x]=merge(T[x<<1],T[x<<1|1]);
	}else {
		T[x].ans0=T[x].sum0;
		T[x].ans1=T[x].sum1;
		T[x].ans2=T[x].sum2;
	}
	if (T[x].lazy) {
		T[x].ans0=0;
		T[x].ans1=0;
		T[x].ans2=0;
	}
}
void build(int x,int L,int R) {
	if (L==R) {
		int s2=(ll)L*L%M;
		T[x]=node{1,L,s2,1,L,s2,0};
		return;
	} int mid=(L+R)/2;
	build(x<<1,L,mid); build(x<<1|1,mid+1,R);
	T[x]=merge(T[x<<1],T[x<<1|1]);
	// printf("%d  %d-%d: %d %d %d %d %d %d\n",x,L,R,T[x].ans0,T[x].ans1,T[x].ans2,T[x].sum0,T[x].sum1,T[x].sum2);
}
void update(int x,int l,int r,int val,int L,int R) {
	if (l<=L&&R<=r) {
		change(x,val);
		// printf("upd %d  %d-%d: %d %d %d %d %d %d\n",x,L,R,T[x].ans0,T[x].ans1,T[x].ans2,T[x].sum0,T[x].sum1,T[x].sum2);
		return;
	} int mid=(L+R)/2;
	if (l<=mid) update(x<<1,l,r,val,L,mid);
	if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
	T[x]=merge(T[x<<1],T[x<<1|1]);
	// printf("upd %d  %d-%d: %d %d %d %d %d %d\n",x,L,R,T[x].ans0,T[x].ans1,T[x].ans2,T[x].sum0,T[x].sum1,T[x].sum2);
}
node query(int x,int l,int r,int L,int R,int upper) {
	if (l<=L&&R<=r) {
		node ret=T[x];
		if (upper) {
			ret.ans0=0;
			ret.ans1=0;
			ret.ans2=0;
		}
		// printf("rete %d  %d %d %d %d %d %d\n",x,ret.ans0,ret.ans1,ret.ans2,ret.sum0,ret.sum1,ret.sum2);
		return ret;
	} node ret=node{0,0,0,0,0,0,1};
	int mid=(L+R)/2;
	if (l<=mid) ret=merge(ret,query(x<<1,l,r,L,mid,upper+T[x].lazy));
	if (mid<r) ret=merge(ret,query(x<<1|1,l,r,mid+1,R,upper+T[x].lazy));
	// printf("ret %d  %d-%d: %d %d %d %d %d %d\n",x,L,R,T[x].ans0,T[x].ans1,T[x].ans2,T[x].sum0,T[x].sum1,T[x].sum2);
	// printf("rete %d  %d %d %d %d %d %d\n",x,ret.ans0,ret.ans1,ret.ans2,ret.sum0,ret.sum1,ret.sum2);
	return ret;
}
vector<pair<pii,int> > changes[maxn];
int l[maxn],r[maxn];
int main() {
	scanf("%d%d%d",&n,&m,&q);
	int i;
	FOR(i,1,n) scanf("%d%d",&l[i],&r[i]);
	FOR(i,1,q) {
		int lx,ly,rx,ry;
		scanf("%d%d%d%d",&lx,&ly,&rx,&ry);
		changes[lx].push_back(make_pair(make_pair(ly,ry),1));
		changes[rx+1].push_back(make_pair(make_pair(ly,ry),-1));
	}
	int ans=0;
	build(1,1,m);
	FOR(i,1,n) {
		for (auto now:changes[i]) {
			update(1,now.first.first,now.first.second,now.second,1,m);
		} node ret=query(1,l[i],r[i],1,m,0);
		printf("query ret: %d %d %d\n",ret.ans0,ret.ans1,ret.ans2);
		ll all=(ll)(M-ret.ans2+(r[i]+l[i])*ret.ans1+ret.ans0*(r[i]+1)%M*(M+1-l[i]))%M;
		printf("query ret: %d %d %d; all=%lld\n",ret.ans0,ret.ans1,ret.ans2,all);
		all=all*powMM((ll)(r[i]-l[i]+2)*(r[i]-l[i]+1)%M,M-2)%M;
		printf("%lld\n",all*powMM((ll)(r[i]-l[i]+2)*(r[i]-l[i]+1)%M,M-2)%M);
		add_(all,all);//2
		add_(ans,all);
		// printf("%d\n",ans);
	}
	printf("%d\n",ans);
}
/*
*/