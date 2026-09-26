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
const LL maxn=2e5+7;
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

int A[maxn];
double SIN[maxn<<2],COS[maxn<<2];
double lazysin[maxn<<2],lazycos[maxn<<2];//sin
void change(int x,double sin,double cos){
	double S=SIN[x]*cos+COS[x]*sin;
	double C=COS[x]*cos-SIN[x]*sin;
	SIN[x]=S; COS[x]=C;
	S=lazysin[x]*cos+lazycos[x]*sin;
	C=lazycos[x]*cos-lazysin[x]*sin;
	lazysin[x]=S; lazycos[x]=C;
}
void pushdown(int x){
	if (abs(lazysin[x])>eps){
		change(x<<1,lazysin[x],lazycos[x]);
		change(x<<1|1,lazysin[x],lazycos[x]);
		lazysin[x]=0; lazycos[x]=1;
	}
}
void pushup(int x){
	SIN[x]=SIN[x<<1]+SIN[x<<1|1];
	COS[x]=COS[x<<1]+COS[x<<1|1];
}
void build(int x,int L,int R){
	lazysin[x]=0; lazycos[x]=1;
	if (L==R){
		SIN[x]=sin(A[L]);
		COS[x]=cos(A[L]);
		return;
	}int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
	pushup(x);
}
void update(int x,int l,int r,double sin,double cos,int L,int R){
	if (l<=L&&R<=r){
		change(x,sin,cos);
		return;
	} int mid=(L+R)/2;
	pushdown(x);
	if (l<=mid) update(x<<1,l,r,sin,cos,L,mid);
	if (mid<r) update(x<<1|1,l,r,sin,cos,mid+1,R);
	pushup(x);
}
double query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) return SIN[x];
	double ret=0;
	int mid=(L+R)/2;
	pushdown(x);
	if (l<=mid) ret+=query(x<<1,l,r,L,mid);
	if (mid<r) ret+=query(x<<1|1,l,r,mid+1,R);
	pushup(x);
	return ret;
}
char buffer[36000000],*buf=buffer;
char write[7000000],*ed=write;
void read(int &x){
    for(x=0;*buf<48;++buf);
    while(*buf>=48)x=x*10+*buf-48,++buf;
}
int main() {
    fread(buffer,1,36000000,stdin);
	int i;
	read(n);
	FOR(i,1,n) read(A[i]);
	build(1,1,n);
	read(m);
	FOR(i,1,m){
		int op,l,r,x;
		read(op); read(l); read(r);
		// printf("i=%d\n",i);
		if (op==1) read(x);
		if (op==1) update(1,l,r,sin(x),cos(x),1,n);
		if (op==2) printf("%.1f\n",query(1,l,r,1,n));
	}
}
/*
4
1 2 3 4
5
2 2 4
1 1 3 1
2 2 4
1 2 4 2
2 1 3
*/
