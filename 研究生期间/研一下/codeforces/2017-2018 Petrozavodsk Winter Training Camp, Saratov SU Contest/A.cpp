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
const LL maxn=1.2e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

int A[maxn],B[maxn],C[maxn];
int main() {
    int d,na,nb,nc;
    while (~scanf("%d%d%d%d",&d,&na,&nb,&nc)) {
        ll la=0,ra=0,lb=0,rb=0,lc=0,rc=0,ans=0;
        int i;
        FOR(i,1,na) scanf("%d",&A[i]); A[0]=-INF;
        FOR(i,1,nb) scanf("%d",&B[i]); B[0]=-INF;
        FOR(i,1,nc) scanf("%d",&C[i]); C[0]=-INF;
        FOR(i,1,na) { // a<=b, a<=c
            //a is min
            while (lb<=nb&&B[lb]<A[i]) lb++;
            while (rb<=nb&&B[rb]<=A[i]+d) rb++;
            while (lc<=nc&&C[lc]<A[i]) lc++;
            while (rc<=nc&&C[rc]<=A[i]+d) rc++;
            ans+=(rc-lc)*(rb-lb);
        } la=ra=lc=rc=0;
        FOR(i,1,nb) { // b<a, b<=c
            //b is min
            while (la<=na&&A[la]<=B[i]) la++;
            while (ra<=na&&A[ra]<=B[i]+d) ra++;
            while (lc<=nc&&C[lc]<B[i]) lc++;
            while (rc<=nc&&C[rc]<=B[i]+d) rc++;
            ans+=(rc-lc)*(ra-la);
        } la=ra=lb=rb=0;
        FOR(i,1,nc) { // c<a, c<b
            //b is min
            while (la<=na&&A[la]<=C[i]) la++;
            while (ra<=na&&A[ra]<=C[i]+d) ra++;
            while (lb<=nb&&B[lb]<=C[i]) lb++;
            while (rb<=nb&&B[rb]<=C[i]+d) rb++;
            ans+=(rb-lb)*(ra-la);
        } printf("%lld\n",ans);
    }
}
/*
4
4 2 5
3 1 2
3 3 10
2000000000 1 2000000000
*/