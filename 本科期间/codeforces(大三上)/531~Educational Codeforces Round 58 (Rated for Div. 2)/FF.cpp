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
char str[maxn];

int A[maxn];
vector<int> f[407][407];//A->B; fuel k times

int i,j,k;
struct node {
	int l,r,xl,xr;
};
queue<node> Q;
void solve(vector<int> &dp,vector<int> &pre,int l,int r) {
	int i;
	Q.push(node{l,r,l,r-1});
	while (Q.size()) {
		auto F=Q.front(); Q.pop();
		int l=F.l,r=F.r,L=F.xl,R=F.xr;//l,r,check_l,check_r
		int m=(l+r)/2,M=L;
		int &now=dp[m];
		FOR(i,L,min(m-1,R)) {
			if (now>max(pre[i],A[m]-A[i]))
				now=max(pre[i],A[m]-A[i]),M=i;
		}
		if (l<m) Q.push(node{l,m-1,L,M});
		if (r>m) Q.push(node{m+1,r,M,R});
	}
}

int main() {
	int i,j,k;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,n) {
		f[i][0].resize(n-i+2);
		FOR(j,i+1,n) f[i][0][j-i+1]=A[j]-A[i];
		FOR(k,1,n) {
			f[i][k].resize(n-i+2);
			FOR(j,i+1,n) f[i][k][j-i+1]=INF;
			solve(f[i][k],f[i][k-1],1,n-i+1);
			// printf("%d - k= %d\n",i,k);
			// FOR(j,i+1,n) printf("%d ",f[i][k][j]); puts("");
		}
	} ll ans=0;
	FOR(i,1,m) {
		int s,f,c,r;
		scanf("%d%d%d%d",&s,&f,&c,&r);
		// printf("%d - %d %d  : %d\n",s,f,c,::f[s][r][f]);
		ans=max(ans,(ll)::f[s][r][f-s+1]*c);
	} printf("%I64d\n",ans);
}
/*
4
2 4 1 8
1 2
2 3
3 4
*/