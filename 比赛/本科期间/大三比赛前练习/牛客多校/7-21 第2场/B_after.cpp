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

#define DEBUG1
#ifdef DEBUG
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
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void multi(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod(T &A,ll B=M) {A%=M;}
template<typename T>inline void maxi(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void mini(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m;
char S[maxn];
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string() {while (~scanf("%s",S)) TaskA();}

int p[maxn],d[maxn],f[maxn];
int Q[maxn],ST,ED;
int D[maxn];
ll F[maxn][2],G[maxn][2];//0:must_buy; 1:free_more
vector<int> V;
int TaskA() {
	int i;
	ST=0; ED=-1; scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&p[i]);
	FOR(i,1,n) scanf("%d",&d[i]);
	FOR(i,1,n) F[i][0]=D[i]=0,F[i][1]=p[i]-d[i];
	FOR(i,1,n) scanf("%d",&f[i]),D[f[i]]++;
	FOR(i,1,n) if (!D[i]) Q[++ED]=i;
	while (ST<=ED) {
		int x=Q[ST++]; D[f[x]]--; if (!D[f[x]]) Q[++ED]=f[x];
		F[x][1]+=F[x][0]; F[x][0]+=p[x];
		F[f[x]][0]+=F[x][1];
		mini(F[f[x]][1],F[x][0]-F[x][1]); f[x]=0;
		// printf("%d %d; x=%d\n",ST,ED,x);
	}ll ans=0;
	vector<int> have;
	FOR(i,1,n) if (f[i]) {
		// printf("que: %d\n",i);
		ll now=INFF;
		// not use
		have.clear(); have.push_back(i);
		if (f[i]==i) mini(now,F[i][1]+F[i][0]);
		else{
			for (int x=f[i]; x!=i; x=f[x]) have.push_back(x);
			// for (auto x:have) printf("%d ",x);puts("");
			for (auto x:have) G[x][0]=0,G[x][1]=p[x]-d[x];
			for (auto x:have) {
				if (x==i) {
					G[x][0]=F[x][0]; G[x][1]=F[x][1];
				} else {
					G[x][0]+=F[x][0]; mini(G[x][1],F[x][1]);
				} G[x][1]+=G[x][0]; G[x][0]+=p[x];
				G[f[x]][0]+=G[x][1];
				mini(G[f[x]][1],G[x][0]-G[x][1]);
				if (f[x]==i) mini(now,G[x][1]);
				// printf("%d : %lld %lld\n",x,G[x][0],G[x][1]);
			}
			for (auto x:have) G[x][0]=0,G[x][1]=p[x]-d[x];
			for (auto x:have){
				if (x==i){
					G[x][0]=F[x][0]; G[x][1]=0;
				}else{
					G[x][0]+=F[x][0]; mini(G[x][1],F[x][1]);
				} G[x][1]+=G[x][0]; G[x][0]+=p[x];
				G[f[x]][0]+=G[x][1];
				mini(G[f[x]][1],G[x][0]-G[x][1]);
				if (f[x]==i) mini(now,G[x][0]);
			}
		} ans+=now;
		for (auto x:have) f[x]=0;
	} printf("%lld\n",ans);
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	TaskA();
	assert(scanf("%d",&n)==EOF);
}
/*
3
10 3 5
5 1 2
1 1 1
*/