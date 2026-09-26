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

struct node{
	int x,y;
	node(int x=0,int y=0):x(x),y(y){};
}p[maxn];
int C[maxn];
int g[maxn],f[maxn];
int main() {
	int i,j;
	scanf("%d",&n); m=1<<n;
	REP(i,n) scanf("%d%d",&p[i].x,&p[i].y);
	int sta;
	REP(i,m) C[i]=C[i>>1]+(i&1);
	int k;
	REP(i,n) rep(j,i+1,n) rep(k,j+1,n){
		node A,B;
		A.x=p[j].x-p[i].x; A.y=p[j].y-p[i].y;
		B.x=p[k].x-p[j].x; B.y=p[k].y-p[j].y;
		assert(A.y*B.x!=A.x*B.y);
	}
	REP(sta,m) {
		vector<node> now;
		REP(i,n) if ((sta>>i)&1){
			rep(j,i+1,n) if ((sta>>j)&1){
				node vi=node(p[i].x-p[j].x,p[i].y-p[j].y);
				if (vi.x<0) vi.x=-vi.x,vi.y=-vi.y;
				now.push_back(vi);
			}
		} sort(now.begin(), now.end(), [](node &A,node &B){
			return A.x*B.y>A.y*B.x;
		}); int nowans=0;
		REP(i,(int)now.size()){
			if (i&&now[i].x*now[i-1].y==now[i].y*now[i-1].x) nowans++;
			else nowans=1;
			max_(g[sta],nowans);
			// printf("%d %d: %d\n",now[i].x,now[i].y,nowans);
		}
		// pr2(sta,n); printf(": %d\n",g[sta]);
		g[sta]=g[sta]*(g[sta]-1)/2;
	}
	rep(sta,1,m) {
		for (int nowsta=sta;nowsta;nowsta=(nowsta-1)&sta){
			max_(f[sta],g[nowsta]+f[sta^nowsta]);
		}
	}
	printf("%d\n",f[m-1]);
}
/*
8
0 0
1 1
1 0
1 5
2 5
2 1
3 10
3 5
*/
