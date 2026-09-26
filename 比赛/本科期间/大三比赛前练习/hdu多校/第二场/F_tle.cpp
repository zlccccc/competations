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
const LL M=998244353;
const LL maxn=1e6+7;
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

ll pw[3007*3007];
ll fac[10007],inv[10007];
ll C(int n,int m){
	return fac[n]*inv[m]%M*inv[n-m]%M;
}
ll fa[maxn],fb[maxn];
int TaskA() {
	int i,j;
	int A,B;
	scanf("%d%d",&A,&B);
	FOR(i,1,n) fa[i]=0; FOR(i,A,n) fa[i]=1;
	FOR(i,A+1,n) FOR(j,A,i-1) add_(fa[i],M-C(i,j)*fa[j]%M);
	FOR(i,1,m) fb[i]=0; FOR(i,B,m) fb[i]=1;
	FOR(i,B+1,m) FOR(j,B,i-1) add_(fb[i],M-C(i,j)*fb[j]%M);
	ll ans=0;
	FOR(i,A,n) FOR(j,B,m) add_(ans,fa[i]*fb[j]%M*C(n,i)%M*C(m,j)%M*pw[(n-i)*(m-j)]%M);
	printf("%lld\n",ans);
    return 0;
}
void initialize() {
	int i;
	fac[0]=1; inv[0]=inv[1]=1;
	FOR(i,1,10000) fac[i]=fac[i-1]*i%M;
	FOR(i,2,10000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,10000) inv[i]=inv[i-1]*inv[i]%M;
	pw[0]=1;
	FOR(i,1,3000*3000) pw[i]=pw[i-1]*2%M;
}
int main() {
    int startTime=clock();
    //initialize
    initialize();
    debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
    Task_more_n_m();
}
/*
3000 3000 0 0
*/