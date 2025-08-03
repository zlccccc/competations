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
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

// 本质就是算一个整数拆分即可
// m拆成k个数字, 每个数字小于m, 假设方案数是g(k)
// ans=\sum_k g(k)*(k-1)! * (剩余的随便选的方案数=(n-k)^(n-k-1)*powm[n-k-1]的额外边)

ll powm[maxn],pown[maxn];
ll fac[maxn],inv[maxn];
LL C(int n,int m){
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
int main() {
	int n,m,a,b,k,i;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!
	scanf("%d%d%d%d",&n,&m,&a,&b);
	powm[0]=pown[0]=1;
	FOR(i,1,n) powm[i]=powm[i-1]*m%M;
	FOR(i,1,n) pown[i]=pown[i-1]*n%M;
	int ans=0;
	FOR(k,1,min(m,n-1)) {//ab之间的边数
		int now=C(m-1,k-1)*C(n-2,k-1)%M*fac[k-1]%M*powm[n-k-1]%M;
		//接下来是个度数为k+1的点和一堆度数为?的点连成一个生成树
		//考虑prufer序列, 假装现有的全是最小值
		if (n-k-1>0) now=(ll)now*(k+1)%M*pown[n-k-2]%M;
		add_(ans,now);
	} printf("%d\n",ans);
}
/*
*/