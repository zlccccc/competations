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

int f[1<<15|7],g[1<<15|7];
char str[27][27];
int mark[1<<15|7];//count&1
int main(){
	int n,m;
	int i,j,k;
	REP(i,(1<<15)) mark[i]=mark[i>>1]^(i&1);
	while (~scanf("%d%d",&n,&m)){
		REP(i,n) scanf("%s",str[i]);
		REP(k,1<<(m+1)) g[k]=INF;
		REP(j,m) g[1<<(j+1)]=0;//top_插头
		REP(i,n) {
			REP(j,m) {//check_position; to_right
				int val=str[i][j]-'0';
				REP(k,(1<<(m+1))) {//x_left; y:down
					int x=1<<j,y=1<<(j+1);//v=value
					int z=mark[k&(x-1)];//downpos
					// z^=w;//z:previous_okay
					if ((str[i][j]=='#'||str[i][j]=='W'||str[i][j]=='L')&&((k&x)||(k&y))) {
						f[k]=INF;//有插头
					} else if (str[i][j]=='W') {
						if (z) f[k]=INF;//no!
						else f[k]=g[k];//no way
					} else if (str[i][j]=='L') {
						if (!z) f[k]=INF;//no!
						else f[k]=g[k];//no way
					} else if (str[i][j]=='#') {//all is ok
						f[k]=g[k];
					} else {
						if ((k&x)&&(k&y)) {//value:(left and up)
							f[k]=g[k^x^y]+val;
						} else if (k&x) {//left
							f[k]=min(g[k],g[k^x^y])+val;//down
						} else if (k&y) {
							f[k]=min(g[k],g[k^x^y])+val;//right
						} else {
							f[k]=min(g[k],g[k^x^y]+val);//not choose
						}
					}
				} REP(k,(1<<(m+1))) g[k]=f[k];
				// printf("i=%d; j=%d(f)\n",i,j);
				// REP(k,(1<<(m+1))) if (f[k]<INF){
				// 	pr2(k,m+1); printf("%d\n",f[k]);
				// } system("pause");
			}
			rREP(k,(1<<(m+1))) {
				if (k&1) g[k]=INF;
				else g[k]=g[k>>1];
			}
			// printf("i=%d(f)\n",i);
			// REP(k,(1<<(m+1))) if (f[k]<INF){
			// 	pr2(k,m+1); printf("%d\n",f[k]);
			// }  printf("g:\n");
			// REP(k,(1<<(m+1))) if (g[k]<INF){
			// 	pr2(k,m+1); printf("%d\n",g[k]);
			// } system("pause");
		} int ans=INF;
		REP(i,m) ans=min(ans,g[1<<(i+1)]);
		if (ans<INF) printf("%d\n",ans);
		else puts("-1");
	}
}
/*
3 5
88888
8L888
88111

3 4
L88W
88W8
8L8W

3 5
38848
88288
88888

6 8
88W888L8
888#W888
888888L8
8W8LL#88
8888888L
00000W88

3 6
000888
0L08W8
000888
*/