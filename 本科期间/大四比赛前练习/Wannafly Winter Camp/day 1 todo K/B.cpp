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
const LL maxn=1e4+107;
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
// char str[maxn];

int T[27][27];
struct mat {
	ll trans[100][100];
	mat() {
		int i,j;
		REP(i,100) REP(j,100) trans[i][j]=(i==j)?0:-INF; 
	}
} one;//time=2520
inline int getid(int x,int y) {return (x-1)*m+y-1;}
int g[2][107];
mat mul(mat x,mat y) {
	int i,j,k; mat ret;
	REP(i,n*m) REP(j,n*m) REP(k,n*m) max_(ret.trans[i][j],x.trans[i][k]+y.trans[k][j]);
	return ret;
}
mat tmp[107];//pow
int main() {
	int i,j; ll C;
	scanf("%d%d%lld",&n,&m,&C);
	FOR(i,1,n) FOR(j,1,m) scanf("%d",&T[i][j]);
	int xs,ys,xt,yt;
	scanf("%d%d%d%d",&xs,&ys,&xt,&yt);
	//part one
	int *now=g[0],*nxt=g[1];
	int x,y,u,v;
	FOR(x,1,n) FOR(y,1,m) { //(x,y)->(u,v)
		FOR(u,1,n) FOR(v,1,m) now[getid(u,v)]=-INF;
		now[getid(x,y)]=0;
		FOR(i,1,2520) {
			REP(j,n*m) nxt[j]=-INF;
			FOR(u,1,n) FOR(v,1,m) {
				if (u!=1) max_(nxt[getid(u-1,v)],now[getid(u,v)]);
				if (u!=n) max_(nxt[getid(u+1,v)],now[getid(u,v)]);
				if (v!=1) max_(nxt[getid(u,v-1)],now[getid(u,v)]);
				if (v!=m) max_(nxt[getid(u,v+1)],now[getid(u,v)]);
				max_(nxt[getid(u,v)],now[getid(u,v)]);
			} swap(now,nxt);
			FOR(u,1,n) FOR(v,1,m) if (i%T[u][v]==0) now[getid(u,v)]++;
		}
		FOR(u,1,n) FOR(v,1,m) one.trans[getid(x,y)][getid(u,v)]=now[getid(u,v)];
	}
	// FOR(x,1,n) FOR(y,1,m) {
	// 	FOR(u,1,n) FOR(v,1,m) {
	// 		printf("(%d,%d)->(%d %d): %lld\n",x,y,u,v,one.trans[getid(x,y)][getid(u,v)]);
	// 	}
	// }
	// puts("part 1 ok");
	//part two
	ull ans=0;
	tmp[0]=one;
	int s=getid(xs,ys),t=getid(xt,yt);
	for (i=0; tmp[i].trans[s][t]<C; i++)
		tmp[i+1]=mul(tmp[i],tmp[i]);
	mat matnow;
	for (; i!=-1; i--) {
		mat matnxt=mul(matnow,tmp[i]);
		// printf("trans=%lld; time=%llu\n",(ll)matnxt.trans[s][t],(ull)(ans+(2520ull<<i)));
		if (matnxt.trans[s][t]<C)
			matnow=matnxt,ans+=(1ull<<i)*2520ull;
	}
	// printf("matnow=%lld; time=%lu\n",(ll)matnow.trans[s][t],(ull)ans);
	// puts("part 2 ok");
	//part 3
	if (ans>0){
		C-=matnow.trans[s][t];
		FOR(u,1,n) FOR(v,1,m) now[getid(u,v)]=matnow.trans[s][getid(u,v)]-matnow.trans[s][t];
	} else {
		FOR(u,1,n) FOR(v,1,m) now[getid(u,v)]=-INF; now[s]=0;
	}
	FOR(i,0,M) {
		if (now[t]>=C) break;
		REP(j,n*m) nxt[j]=-INF;
		FOR(u,1,n) FOR(v,1,m) {
			if (u!=1) max_(nxt[getid(u-1,v)],now[getid(u,v)]);
			if (u!=n) max_(nxt[getid(u+1,v)],now[getid(u,v)]);
			if (v!=1) max_(nxt[getid(u,v-1)],now[getid(u,v)]);
			if (v!=m) max_(nxt[getid(u,v+1)],now[getid(u,v)]);
			max_(nxt[getid(u,v)],now[getid(u,v)]);
		} swap(now,nxt);
		FOR(u,1,n) FOR(v,1,m) if ((i+1)%T[u][v]==0) now[getid(u,v)]++;
	} ans+=i;
	printf("%llu\n",(ull)(ans));
}
/*
1 3 0
1 2 3
1 1 1 3

1 3 
1000000000000000000
10 10 10
1 1 1 3
*/