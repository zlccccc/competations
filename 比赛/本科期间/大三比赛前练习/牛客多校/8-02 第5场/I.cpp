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
const LL M=998244353;
const LL maxn=3e5+7;
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
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_n_m_q() {while (~scanf("%d%d%d",&n,&m,&q)) TaskA();}
void Task_more_string() {while (~scanf("%s",str)) TaskA();}

struct node{
	int l,r,cnt; 
	node(){l=r=cnt=0;}
}T[maxn*40]; int tot;
void update(int &x,int pos,int L,int R){
	if (!x) x=++tot,T[tot]=node(); T[x].cnt++;
	if (L==R) return;
	int mid=(L+R)/2;
	if (pos<=mid) update(T[x].l,pos,L,mid);
	else update(T[x].r,pos,mid+1,R);
}
int query(int x,int l,int r,int L,int R){
	if (!x) return 0;
	if (l<=L&&R<=r) return T[x].cnt;
	int ret=0,mid=(L+R)/2;
	if (l<=mid) ret+=query(T[x].l,l,r,L,mid);
	if (mid<r) ret+=query(T[x].r,l,r,mid+1,R);
	return ret;
}
struct point{
	int x,y,id;
}A[maxn];
int L[maxn],R[maxn];
int root;
int TaskA() {
	int i;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d%d",&A[i].x,&A[i].y),A[i].id=i;
	sort(A+1,A+1+n,[](point x,point y){
		if (x.y!=y.y) return x.y<y.y;
		return x.x<y.x;
	}); root=tot=0;
	FOR(i,1,n){
		L[A[i].id]=query(root,A[i].x+1,INF,1,INF);
		update(root,A[i].x,1,INF);
		// printf("update: %d  %d\n",A[i].x,L[A[i].id]);
	}
	sort(A+1,A+1+n,[](point x,point y){
		if (x.y!=y.y) return x.y>y.y;
		return x.x<y.x;
	}); root=tot=0;
	ll ans=n;
	FOR(i,1,n){
		// printf("update: %d\n",A[i].x);
		R[A[i].id]=query(root,A[i].x+1,INF,1,INF);
		add_(ans,query(root,A[i].x,A[i].x,1,INF));
		update(root,A[i].x,1,INF);
	}
	// FOR(i,1,n) printf("%d %d\n",L[i],R[i]);
	FOR(i,1,n){
		ans+=L[i]+R[i]; mod_(ans);
		ans+=(ll)L[i]*R[i]; mod_(ans);
	}
	printf("%lld\n",ans);
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*
*/
