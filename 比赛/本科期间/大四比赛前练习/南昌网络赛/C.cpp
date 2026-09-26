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

//9102 8102 reverse=2018; 2019
char str[maxn];
struct node {
	int A[5][5];//A->B至少要删几个
	node() {memset(A,0x3f,sizeof(A)); A[0][0]=0;}
} T[maxn<<2];
inline node merge(const node &_left,const node &_right) {
	node ret; int i,j,k;
	REP(i,5) rep(j,i,5) rep(k,j,5) {
		min_(ret.A[i][k],_left.A[i][j]+_right.A[j][k]);
	} return ret;
}
inline void print()
inline void build(int x,int l,int r) {
	int o;
	if (l==r) {
		REP(o,5) T[x].A[o][o]=1;//remove
		//not_remove
		// if (str[i]=='\0');//为了对齐
		if (str[l]=='2')	  T[x].A[0][1]=T[x].A[1][1]=T[x].A[2][2]=T[x].A[3][3]=T[x].A[4][4]=0;
		else if (str[l]=='0') T[x].A[0][0]=T[x].A[1][2]=T[x].A[2][2]=T[x].A[3][3]=T[x].A[4][4]=0;
		else if (str[l]=='1') T[x].A[0][0]=T[x].A[1][1]=T[x].A[2][3]=T[x].A[3][3]=T[x].A[4][4]=0;
		else if (str[l]=='9') T[x].A[0][0]=T[x].A[1][1]=T[x].A[2][2]=T[x].A[3][4]=T[x].A[4][4]=0;
		else if (str[l]=='8') T[x].A[0][0]=T[x].A[1][1]=T[x].A[2][2]=0;//3,4:notokay
		else 				  T[x].A[0][0]=T[x].A[1][1]=T[x].A[2][2]=T[x].A[3][3]=T[x].A[4][4]=0;
		return;
	} int mid=(l+r)/2;
	build(x<<1,l,mid); build(x<<1|1,mid+1,r);
	T[x]=merge(T[x<<1],T[x<<1|1]);
}
inline node query(int x,int l,int r,int L,int R) {
	// printf("query: %d %d-%d %d-%d\n",x,l,r,L,R);
	if (l<=L&&R<=r) return T[x];
	int mid=(L+R)/2;
	if (l<=mid&&mid<r) return merge(query(x<<1,l,r,L,mid),query(x<<1|1,l,r,mid+1,R));
	if (l<=mid) return query(x<<1,l,r,L,mid);
	if (mid<r) return query(x<<1|1,l,r,mid+1,R);
	puts("no!");
	return node();
}
int main() {
	int n,q,i;
	scanf("%d%d%s",&n,&q,str+1);
	reverse(str+1,str+1+n);
	build(1,1,n);
	FOR(i,1,q) {
		int l,r; scanf("%d%d",&l,&r);
		l=n-l+1; r=n-r+1; swap(l,r);
		node now=query(1,l,r,1,n);
		if (now.A[0][4]>=INF) puts("-1");
		else printf("%d\n",now.A[0][4]);
	}
}
/*
8 3
88988102
1 8
2 8
1 7

9 1
910288102
1 9
*/