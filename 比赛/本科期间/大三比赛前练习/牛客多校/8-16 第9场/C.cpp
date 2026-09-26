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
const LL maxn=2e6+7;
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

double p[27][27];
LL inv[1000002];//inverse
LL fac[1000002];//Factorial
ll pw2[1000002];
LL C(int m,int n){
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
int main() {
	int i,j;
	// REP(i,19){
	// 	if (i==1) p[i][0]=pow(2,6);
	// 	//这里倒着看...可能就..会发现, 能转移到的状态完全一样的
	// 	rep(j,1,i) p[i][j]=(p[i-1][j]+p[i-1][j-1])/2;
	// 	printf("%d :\n",i);
	// 	REP(j,i) printf("%-10.0f",p[i][j]);puts("");
	// }
	// 某位置(从下往上数第k层) F[k][i]=val=\sum_{j=i}^{2*n-k-1} C(i,j)*pow(1/2,j-i);
	// 底下一层减上面一层是 j=2*n-k-1;  C(i-1,j)*pow(1/2,j)

    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
    pw2[0]=1;
    FOR(i,1,1000000) pw2[i]=pw2[i-1]*2%M;
	scanf("%d",&n);
	int n1=n,n2=n;
	FOR(i,1,2*n-1){//第i层, 有n1个
		int o; j=2*n-i-1;
		printf("%lld\n",C(n1-1,j)*pw2[n*2-1-j]%M);
		scanf("%d",&o);
		if (o) n1--; else n2--;
		if (n1==0||n2==0) break;
	}
}
/*
*/