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
const LL maxn=1e4+7;
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

int K;
int A[27][27],cnt[27][27];
int col[407],ans;
bool okay[27][27][128];
struct node {
	int x,y,sta,k;
	node(int x=0,int y=0,int sta=0,int k=0):x(x),y(y),sta(sta),k(k) {};
};
queue<node> Q;
int _x[4]= {-1,1,0,0};
int _y[4]= {0,0,1,-1};
int solve() {
	int i,j,k;
	int ans=INF;
	scanf("%d%d%d",&n,&m,&K); int T=(1<<K)-1;
	FOR(i,1,n) {
		FOR(j,1,m) scanf("%d",&A[i][j]);
	} int times=500;
	while (times--) {
		int nowans=INF;
		FOR(i,1,n*m) col[i]=rand()%K;
		FOR(i,1,n) {
			FOR(j,1,m) {
				FOR(k,0,T) okay[i][j][k]=0;
				if (A[i][j]!=-1) {
					int sta=0;
					if (A[i][j]!=0) sta=1<<col[A[i][j]];
					Q.push(node(i,j,sta,0));
					okay[i][j][sta]=1;
				}
			}
		} while (Q.size()) {
			auto now=Q.front(); Q.pop();
			int x=now.x,y=now.y;
			if (now.sta==T) {min_(nowans,now.k); break;}
			REP(i,4) {
				int ax=x+_x[i],ay=y+_y[i];
				if (ax<1||ax>n||ay<1||ay>m) continue;
				if (A[ax][ay]==-1) continue;
				int nxtsta=now.sta;
				if (A[ax][ay]!=0) nxtsta|=1<<col[A[ax][ay]];
				if (okay[ax][ay][nxtsta]) continue;
				okay[ax][ay][nxtsta]=1;
				Q.push(node(ax,ay,nxtsta,now.k+1));
			}
		} while (Q.size()) Q.pop();
		min_(ans,nowans);
	} if (ans==INF) puts("-1");
	else printf("%d\n",ans);
	return 0;
}
int main() {
	int T;
	srand(19260817);
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/
