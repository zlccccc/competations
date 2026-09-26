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

int d[maxn],f[maxn];
int choose[maxn],no[maxn];
vector<int> edge[maxn];
void dfs(int x,int fa){
	int notc=0,chose=f[x];
	for (int v:edge[x]) if (v!=fa){
		dfs(v,x);
		notc+=max(choose[v],no[v]);
		chose+=max(choose[v]-d[min(x,v)],no[v]);
	} no[x]=notc; choose[x]=chose;
	// printf("%d : %d %d\n",x,notc,chose);
}
int main() {
	int i;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&f[i]);
	FOR(i,1,n) scanf("%d",&d[i]);
	int ans=0;
	rFOR(i,1,n){
		if (i*2<=n) {
			edge[i].push_back(i*2);
			edge[i*2].push_back(i);
		}//not choose
		if ((i&1)&&i!=1&&i*3+1<=n) {
			edge[i].push_back(i*3+1);
			edge[i*3+1].push_back(i);
		}
	} FOR(i,1,n) if (!choose[i]){
		dfs(i,0); ans+=max(choose[i],no[i]);
	}
	printf("%d\n",ans);
}
/*
4
10 4 3 3
2 3 0 0
4
10 10 3 3
2 3 0 0
*/