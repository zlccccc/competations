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
const LL maxn=1e7+107;
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

LL inv[10000002];//inverse
LL fac[10000002];//Factorial
LL C(int n,int m) {
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
ll pw2[maxn];
int main() {
    int i;
    fac[0]=1;
    FOR(i,1,10000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,10000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,10000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
    pw2[0]=1;
    FOR(i,1,10000000) pw2[i]=pw2[i-1]*2%M;

    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        int n,m,i,k;
        int ans=0;
        scanf("%d%d",&n,&m);
        FOR(k,0,min(n,m)) {
            ll noww=0,mor=n+m-k-1; // mor:可选可不选
            noww=(pw2[mor]*(2+k))%M;
            // FOR(i,0,mor) add_(noww,i*C(mor,i)%M);
            if (mor) add_(noww,mor*pw2[mor-1]%M);
            // printf("k=%d; mor=%lld; noww=%lld; base=%lld\n",k,mor,noww,C(n,k)*C(m,k));
            // 考虑向右向上走 (up first)
            // 拐点x in [0,n-1], y in [1,m]
            add_(ans,C(n,k)*C(m,k)%M*noww%M);
        }
        printf("%d\n",ans);
    }
}
/*
*/