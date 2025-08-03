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

double limit;
const double sq2=sqrt(2);
#define mp make_pair
typedef pair<double,pair<pii,pii>> Node;
const int base=50;
double Ans[50][50][100][100];
priority_queue<Node,vector<Node>,greater<Node> > Q;
inline void upd(int x,int y,int a,int b,double val) {
	if (x<0||y<0||x>n||y>m||a<-40||a>40||b<-20||b>20||a+b*sq2<-eps||a+b*sq2>limit) return;
	if (Ans[x][y][a+base][b+base]>val+eps) {
		Q.push(mp(val,mp(mp(x,y),mp(a,b))));
		Ans[x][y][a+base][b+base]=val;
	}
}
double A[50][50],diff[100][100];
pii more[100][100];
#define x second.first.first
#define y second.first.second
#define a second.second.first
#define b second.second.second
int main() {
	int i,j,k,t;
	scanf("%d%d%lf",&n,&m,&limit);
	limit=min(limit,20*sqrt(2)); limit+=eps;
	REP(i,n+1) REP(j,m+1) scanf("%lf",&A[i][j]);
	FOR(i,-40,40) FOR(j,-20,20) if (-eps<i+j*sq2){
		diff[i+base][j+base]=INF;
		FOR(k,-40,40) FOR(t,-20,20) if (i+j*sq2+eps<k+t*sq2)
			if (k+t*sq2<limit&&k+t*sq2-i-j*sq2<diff[i+base][j+base])
				more[i+base][j+base]=mp(k,t),diff[i+base][j+base]=k+t*sq2-i-j*sq2; 
	}
	REP(i,n+1) REP(j,m+1) REP(k,100) REP(t,100) Ans[i][j][k][t]=INF;
	Ans[0][0][base][base]=0;
	Q.push(mp(0,mp(mp(0,0),mp(0,0))));
	while (Q.size()) {
		auto now=Q.top(); Q.pop();
		if (now.first>eps+Ans[now.x][now.y][now.a+base][now.b+base]) continue;
		upd(now.x,now.y,more[now.a+base][now.b+base].first,more[now.a+base][now.b+base].second,
				now.first+A[now.x][now.y]*diff[now.a+base][now.b+base]);
		upd(now.x+1,now.y,now.a-1,now.b,now.first);
		upd(now.x-1,now.y,now.a-1,now.b,now.first);
		upd(now.x,now.y+1,now.a-1,now.b,now.first);
		upd(now.x,now.y-1,now.a-1,now.b,now.first);
		upd(now.x+1,now.y+1,now.a,now.b-1,now.first);
		upd(now.x+1,now.y-1,now.a,now.b-1,now.first);
		upd(now.x-1,now.y+1,now.a,now.b-1,now.first);
		upd(now.x-1,now.y-1,now.a,now.b-1,now.first);
	}
	printf("%.10f\n",Ans[n][m][base][base]);
}
/*
2 2 1
876322 702453 233424
215282 486678 123806
417986 759560 973610
*/