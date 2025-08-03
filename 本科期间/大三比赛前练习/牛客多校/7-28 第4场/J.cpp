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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void mul_(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod_(T &A,ll B=M) {A%=M;}
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

int A[maxn],B[maxn];
priority_queue<pii> Q;
int check(int L,int MIN){
	if (A[L]==-1) return -1;
	int pos=L%n,val=A[L]%n;
	// printf("%d : %d %d\n",L,val,MIN);
	if (val>=MIN) Q.push(make_pair(-A[L],pos)),A[L]=-1;
	if (A[L]==-1) return -1;
	return val;
}
int MAX[maxn*4];
void build(int x,int L,int R){
	if (L==R) {
		MAX[x]=check(L,L);return;
	} int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
	MAX[x]=max(MAX[x<<1],MAX[x<<1|1]);
}
void getval(int x,int l,int r,int val,int L,int R){
	// printf("SEG:  Getval: %d %d %d %d l,r=%d %d; MAX=%d\n",x,l,r,val,L,R,MAX[x]);
	if (MAX[x]<val) return;
	if (l<=L&&R<=r){
		if (L==R) {MAX[x]=check(L,val); return;}
		int mid=(L+R)/2;
		getval(x<<1,l,r,val,L,mid);
		getval(x<<1|1,l,r,val,mid+1,R);
		MAX[x]=max(MAX[x<<1],MAX[x<<1|1]);
		return;
	}int mid=(L+R)/2;
	if (l<=mid) getval(x<<1,l,r,val,L,mid);
	if (mid<r) getval(x<<1|1,l,r,val,mid+1,R);
	MAX[x]=max(MAX[x<<1],MAX[x<<1|1]);
}
int pre[maxn],suf[maxn];
void erase(int x){
	// printf("getval: %d-%d : %d\n",x,suf[x],pre[x]+1);
	pre[suf[x]]=pre[x];
	getval(1,x,suf[x],pre[x]+1,0,n*3);
	if (x==0) return;
	suf[pre[x]]=suf[x];//x->suf; ans
}
vector<int> ans;
int TaskA() {
	int i;
	scanf("%d",&n);
	REP(i,n) scanf("%d",&B[i]);
	FOR(i,0,n*3) pre[i]=i-1,suf[i]=i+1,A[i]=-1;
	REP(i,n) if (B[i]!=-1) {
		if (B[i]%n>i) A[i+n]=B[i];
		else A[i]=B[i];
	}
	// rep(i,0,n+n) printf("(%-2d)%-2d ",i,A[i]);puts("");
	build(1,0,n*3);
	// rep(i,0,n+n) printf("(%-2d)%-2d ",i,A[i]);puts("");
	ans.clear();
	while (Q.size()){
		auto now=Q.top(); Q.pop();
		// printf (" solve : %d %d\n",now.first,now.second);
		int pos=now.second;
		erase(pos); erase(pos+n);
		ans.push_back(-now.first);
	}
	REP(i,n*3) if (A[i]!=-1) return 0*puts("-1");
	REP(i,(int)ans.size()) printf("%d%c",ans[i]," \n"[i==(int)ans.size()-1]);
	if (ans.size()==0) puts("");
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
10
9
16 -1 -1 -1 -1 -1 -1 7 8
4
8 5 2 3
10
8 10 -1 -1 34 75 86 55 88 18
4
2 3 4 1
4
6 2 2 2
*/
