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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=21092013;
const LL maxn=10000+7;
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

int A[maxn];
ll downval[maxn],nowans;
ll ans[maxn];
vector<int> edge[maxn];
void dfs(int x,int fa){
	downval[x]=A[x]; add_(nowans,A[x]);
	for (int v:edge[x]) if (v!=fa){
		dfs(v,x);
		add_(nowans,downval[x]*downval[v]%M);
		add_(downval[x],downval[v]*A[x]%M);
	}
}
int L[maxn],R[maxn];
int main() {
	int T,_T;
	scanf("%d",&T);
	FOR(_T,1,T){
		int i,k;
		scanf("%d",&n);
		FOR(i,1,n) edge[i].clear();
		FOR(i,1,n-1){
			int u,v;
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		} FOR(i,1,n) scanf("%d",&L[i]);
		FOR(i,1,n) scanf("%d",&R[i]);
		FOR(k,1,50){
			FOR(i,1,n){
				A[i]=R[i]/k-(L[i]-1)/k;
			} nowans=0;
			dfs(1,0); ans[k]=nowans;
			// FOR(i,1,n) printf("%d ",A[i]);puts(" <- A");
			// FOR(i,1,n) printf("%lld ",downval[i]);puts(" <- down");
			// printf(" %d : %lld\n",k,nowans);
		}
		printf("Case %d:\n",_T);
		rFOR(k,1,50){
			for (i=k+k;i<=50;i+=k) ans[k]-=ans[i];
			mod_(ans[k]);
		}
		FOR(k,1,50) printf("%d: %lld\n",k,ans[k]);
	}
}
/*
*/
