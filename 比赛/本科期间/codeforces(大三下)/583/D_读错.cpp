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
const LL maxn=4e6+107;
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

priority_queue<pair<int,pii> > Q;
char pool[maxn],*st=pool;
// char *str[maxn];
int dis[maxn];
int n,m;
inline int getid(int x,int y) {
	return (x-1)*(m+2)+y-1;
} //不使用
int main() {
	int i,j;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) {
		scanf("%s",st);
		st+=m+2;
	}
	// FOR(i,1,n) {
	// 	FOR(j,1,m) {
	// 		printf("%c",pool[getid(i,j)]);
	// 	} puts("");
	// } puts("<- init_map2");
	memset(dis,0x3f,sizeof(dis));
	FOR(i,1,n) {
		FOR(j,1,m) {
			if (i==1&&j==1) continue;
			if (i==n&&j==m) continue;
			if (i==1||j==m) {
				dis[getid(i,j)]=(pool[getid(i,j)]=='.');
				Q.push(make_pair(-dis[getid(i,j)],make_pair(i,j)));
				// printf("%d %d : %d(%c)\n",i,j,(pool[getid(i,j)]=='.'),pool[getid(i,j)]);
			}
		}
	}
	while (Q.size()) {
		pair<int,pii> P=Q.top(); Q.pop();
		int x=P.second.first,y=P.second.second;
		// printf("get:%d %d: %d\n",x,y,dis[getid(x,y)]);
		if (dis[getid(x,y)]!=-P.first) continue;
		FOR(i,-1,1) FOR(j,-1,1) {
			int ax=x+i,ay=y+j;
			// printf("tow%d %d; getid=(%d)\n",ax,ay,getid(ax,ay));
			if (1<=ax&&ax<=n&&1<=ay&&ay<=m) {
				if (ax==1&&ay==1) continue;
				if (ax==n&&ay==m) continue;
				int nxtdis=dis[getid(x,y)]+(pool[getid(ax,ay)]=='.');
				if (dis[getid(ax,ay)]>nxtdis) {
					dis[getid(ax,ay)]=nxtdis;
					Q.push(make_pair(-dis[getid(ax,ay)],make_pair(ax,ay)));
				}
			}
		}
	} int ans=INF;
	FOR(i,1,n) {
		FOR(j,1,m) {
			if (i==1&&j==1) continue;
			if (i==n&&j==m) continue;
			if (i==n||j==1) {
				ans=min(ans,dis[getid(i,j)]);
			}
		}
	} printf("%d\n",ans);
}
/*
4 1
...
.
#
.
*/