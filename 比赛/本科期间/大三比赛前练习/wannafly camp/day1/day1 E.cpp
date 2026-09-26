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
#ifdef DEBUG1
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
const LL maxn=1e3+7;
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

int A[maxn];
ll F[maxn][maxn],G[maxn][maxn];
vector<int> Vx,Vy;
int _x[maxn],_y[maxn],_z[maxn];
int TaskA() {
	int i,j;
	scanf("%d%d",&n,&m);
	Vx.push_back(0);
	Vy.push_back(0);
	FOR(i,1,n){
		scanf("%d%d%d",&_x[i],&_y[i],&_z[i]);
		Vx.push_back(_x[i]);
		Vy.push_back(_y[i]);
	}sort(Vx.begin(),Vx.end());
	Vx.erase(unique(Vx.begin(),Vx.end()),Vx.end());
	sort(Vy.begin(),Vy.end());
	Vy.erase(unique(Vy.begin(),Vy.end()),Vy.end());
	FOR(i,1,n) F[lower_bound(Vx.begin(),Vx.end(),_x[i])-Vx.begin()]
				[lower_bound(Vy.begin(),Vy.end(),_y[i])-Vy.begin()]+=_z[i];
	ll ans=0;
	rep(i,1,(int)Vx.size()) rep(j,1,(int)Vy.size()) if (Vx[i]+Vy[j]<=m) {
		F[i][j]+=F[i-1][j]+F[i][j-1]-F[i-1][j-1];
		max_(G[i][j],G[i-1][j]+(Vx[i]-Vx[i-1])*F[i-1][j]);
		max_(G[i][j],G[i][j-1]+(Vy[j]-Vy[j-1])*F[i][j-1]);
		max_(ans,G[i][j]+F[i][j]*(m-Vx[i]-Vy[j]+1));
	}
	printf("%lld\n",ans);
	return 0;
}
void initialize() {}
int main() {
	// int startTime=clock();
	//initialize
	initialize();
	// debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*

*/