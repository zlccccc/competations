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
const LL maxn=1e6+7;
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

queue<pii> Q;
char s[107][107];
bitset<40507> okay[40507];
int ax[4]={-1,1,0,0};
int ay[4]={0,0,1,-1};
int main() {
	int i;
	scanf("%d%d",&n,&m);
	REP(i,n) scanf("%s",s[i]);
	// n=m=20;
	Q.push(make_pair(n*n*2,m*m*2)); okay[n*n*2].set(m*m*2);
	while (Q.size()){
		auto now=Q.front(); Q.pop();
		REP(i,4){
			int nxtx=now.first+ax[i],nxty=now.second+ay[i];
			if (nxtx<0||nxtx>n*n*4+2||nxty<0||nxty>m*m*4+2) continue;
			if (s[nxtx%n][nxty%m]=='#') continue;
			// printf("%d %d\n",nxtx,nxty);
			if (!okay[nxtx][nxty]){
				okay[nxtx].set(nxty);
				Q.push(make_pair(nxtx,nxty));
			}
		}
	} int midx=n*n*2,midy=m*m*2;
	scanf("%d",&q);
	while (q--){
		int r,c,x,y;
		scanf("%d%d",&r,&c);
		x=r+midx; y=c+midy;
		if (x<0) x=x%(n*n)+n*n;
		if (x>n*n*4) x=x%(n*n)+n*n*3;
		if (y<0) y=y%(m*m)+m*m;
		if (y>m*m*4) y=y%(m*m)+m*m*3;
		// printf("%d %d\n",x-midx,y-midy);
		if (okay[x][y]) puts("yes");
		else puts("no");
	}
}
/*
*/
