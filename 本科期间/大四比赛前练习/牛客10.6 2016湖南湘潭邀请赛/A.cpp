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
const LL maxn=1e5+107;
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

struct mat {
	int A[2][2];
	mat() {memset(A,0,sizeof(A));}
};
mat multiply(const mat &A,const mat &B) {
	mat ret; int i,j,k;
	REP(i,2) REP(j,2) {
		REP(k,2) ret.A[i][j]+=A.A[i][k]*B.A[k][j];
		ret.A[i][j]%=7;
	} return ret;
}
mat poww(mat A,int b) {
	mat ret; ret.A[0][0]=ret.A[1][1]=1;
	for (; b; b>>=1) {
		if (b&1) ret=multiply(ret,A);
		A=multiply(A,A);
	} return ret;
}
char str[maxn];
mat A[10];
void print(mat A) {
	int i,j;
	REP(i,2) REP(j,2) printf("%d%c",A.A[i][j]," \n"[j==1]);
}
int main() {
	A[0].A[0][0]=A[0].A[1][1]=1;
	while (~scanf("%s",str)) {
		int len=strlen(str),i,j;
		REP(i,2) REP(j,2) scanf("%d",&A[1].A[i][j]);
		rep(i,2,10) A[i]=multiply(A[1],A[i-1]);
		mat ans;// print(ans);
		ans.A[0][0]=ans.A[1][1]=1;
		REP(i,len) {
			ans=poww(ans,10);
			// print(ans);
			ans=multiply(ans,A[str[i]-'0']);
		} print(ans);
	}
}
/*
3 3
.##
##.
...
*/