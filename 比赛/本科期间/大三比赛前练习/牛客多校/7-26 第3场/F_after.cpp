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

#define DEBUG1
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

inline int get(char A){
	if ('0'<=A&&A<='9') return A-'0';
	return A-'A'+10;
}
struct node{
	int val[16];
	node(){memset(val,0,sizeof(val));}
}T[maxn<<2];
node merge(node &A,node &B){
	node ret=A; int i,j;
	REP(i,16) add_(ret.val[i],B.val[i]);
	REP(i,16) if (A.val[i]) REP(j,16){
		int k=i+j; (k>15)&&(k-=15);
		add_(ret.val[k],(ll)A.val[i]*B.val[j]%M);
	} return ret;
}
void build(int x,int L,int R){
	if (L==R){
		T[x]=node(); T[x].val[get(str[L])]=1;
		return;
	}int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
	T[x]=merge(T[x<<1],T[x<<1|1]);
}
void update(int x,int pos,char val,int L,int R){
	if (L==R){
		T[x]=node(); T[x].val[get(val)]=1;
		return;
	}int mid=(L+R)/2;
	if (pos<=mid) update(x<<1,pos,val,L,mid);
	if (mid<pos) update(x<<1|1,pos,val,mid+1,R);
	T[x]=merge(T[x<<1],T[x<<1|1]);
}
node ans;
void query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) {ans=merge(ans,T[x]); return;}
	int mid=(L+R)/2;
	if (l<=mid) query(x<<1,l,r,L,mid);
	if (mid<r) query(x<<1|1,l,r,mid+1,R);
}
int TaskA() {
	int i;
	scanf("%d%d",&n,&m);
	scanf("%s",str+1);
	build(1,1,n);
	FOR(i,1,m){
		int op;
		scanf("%d",&op);
		if (op==1){
			int x; char y[2];
			scanf("%d%s",&x,y);
			update(1,x,y[0],1,n);
		} else {
			int x,y;
			scanf("%d%d",&x,&y);
			ans=node(); query(1,x,y,1,n);
			ll Ans=0,p=1,i;
			REP(i,16) add_(Ans,ans.val[i]*p%M),p=p*1021%M;
			printf("%lld\n",Ans);
		}
	}
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
any
any
abcdefghijklmnopqrstuvwxyz
*/