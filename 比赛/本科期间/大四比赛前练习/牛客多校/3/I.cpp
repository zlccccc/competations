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
#include <list>
#include <unordered_map>
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
const LL maxn=5e5+107;
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

int pre[maxn][3][3];//pre_pre是几
int A[maxn],ans[maxn];
int min(int x,int y,int z){
	return min(min(x,y),z);
}
int max(int x,int y,int z) {
	return max(max(x,y),z);
}
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int i,j,k,l,n;
		scanf("%d",&n);
		FOR(i,1,n-2) scanf("%d",&A[i]);
		memset(pre+1,-1,n*3*3*sizeof(int));
		FOR(k,1,n) {
			REP(i,3) REP(j,3) {
				if (k-max(i+1,j)<1) continue;
				if (k-min(i+1,j)>n-2) continue;
				if (k<=2) pre[k][i][j]=0;//self
				else REP(l,3) if (pre[k-1][l][i]!=-1){//pre of pre
					if ((ll)A[k-j]+A[k-1-i]+A[k-2-l]
						-min(A[k-j],A[k-1-i],A[k-2-l])
						-max(A[k-j],A[k-1-i],A[k-2-l])==A[k-2])
						pre[k][i][j]=l;
				}
			}
		}
		REP(i,3) {
			REP(j,3) if (pre[n][i][j]!=-1) break;
			if (j<3&&pre[n][i][j]!=-1) break;
		}
		if (i==3&&j==3) {
			puts("-1"); continue;
		}
		rFOR(k,1,n) {
			ans[k]=A[k-j];
			int tmp=pre[k][i][j];
			j=i; i=tmp;
		}
		FOR(k,1,n) printf("%d%c",ans[k]," \n"[k==n]);
	}
}
/*

*/