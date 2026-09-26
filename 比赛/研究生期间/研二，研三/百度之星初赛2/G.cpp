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
const LL M=998244353;
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
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m) {
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
ll get(int x,int y) {
    return C(x+y,x);
}
pii A[maxn];
ll S[maxn],T[maxn];
int main() {
    int n,m,k,i,j;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)

    scanf("%d%d%d",&n,&m,&k);
    FOR(i,1,k) scanf("%d%d",&A[i].first,&A[i].second);
    sort(A+1,A+1+k);
    FOR(i,1,k) {
        S[i]=get(A[i].first,A[i].second);
        FOR(j,1,i-1) {
            if (A[j].first<=A[i].first&&A[j].second<=A[i].second) {
                add_(S[i],M-S[j]*get(A[i].first-A[j].first,A[i].second-A[j].second)%M);
            }
        }
    }
    FOR(i,1,k) A[i].first=n-A[i].first,A[i].second=m-A[i].second;
    reverse(A+1,A+1+k);
    FOR(i,1,k) {
        T[i]=get(A[i].first,A[i].second);
        FOR(j,1,i-1) {
            // printf("%d %d, %d %d\n",A[i].first,A[i].second,A[j].first,A[j].second);
            if (A[j].first<=A[i].first&&A[j].second<=A[i].second) {
                add_(T[i],M-T[j]*get(A[i].first-A[j].first,A[i].second-A[j].second)%M);
            }
        }
    }
    reverse(A+1,A+1+k);
    FOR(i,1,k) A[i].first=n-A[i].first,A[i].second=m-A[i].second;
    reverse(T+1,T+1+k);
    // FOR(i,1,k) {
    //     printf("%d %d: %lld %lld\n",A[i].first,A[i].second,S[i],T[i]);
    // }
    ll ans=0;
    FOR(i,1,k) FOR(j,1,k) {
        if (i!=j) add_(ans,S[i]*T[j]%M);
    }
    printf("%lld\n",ans);
}
/*
*/