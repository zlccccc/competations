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
const LL maxn=3e5+107;
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

struct tnode{
	int l,r,val;
}T[maxn*30];
int totx;
void update(int &x,int pos,int val,int L,int R) {
	// printf("update:%d %d %d %d %d\n",x,pos,val,L,R);
	if (!x) x=++totx; T[x].val+=val;
	if (L==R) return;
	int mid=(R-L)/2+L;
	if (pos<=mid) update(T[x].l,pos,val,L,mid);
	if (mid<pos) update(T[x].r,pos,val,mid+1,R);
}
int query(int x,int l,int r,int L,int R) {
	// printf("query:%d %d %d %d %d\n",x,l,r,L,R);
	if (!x) return 0;
	if (l<=L&&R<=r) return T[x].val;
	int ret=0,mid=(R-L)/2+L;
	if (l<=mid) ret+=query(T[x].l,l,r,L,mid);
	if (mid<r) ret+=query(T[x].r,l,r,mid+1,R);
	return ret;
}
const int MAX=1e9+7;
struct node {
	int op,x,y,id;
} p[maxn]; int tot;
int ans[maxn];
int root;
int main() {
	int n,i;
	scanf("%d",&n);
	FOR(i,1,n) {
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		a++; b++; c++;
		p[++tot]=node{-i,b,b,a-1};
		p[++tot]=node{i,b,b,c};
		p[++tot]=node{0,a,c,b};
	}
	sort(p+1,p+1+tot,[&](const node &a,const node &b) {
		if (a.id!=b.id) return a.id<b.id;
		return abs(a.op)<abs(b.op);
	});
	FOR(i,1,tot) {
		if (p[i].op==0) {
			update(root,p[i].x-1,-1,1,MAX);
			update(root,p[i].y,1,1,MAX);
		} else {
			int now=query(root,p[i].x,MAX,1,MAX);
			if (p[i].op<0) ans[-p[i].op]-=now;
			else ans[p[i].op]+=now;
		}
	}
	FOR(i,1,n) printf("%d\n",ans[i]-1);
}