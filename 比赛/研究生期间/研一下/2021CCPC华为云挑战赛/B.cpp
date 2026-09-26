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

int n;
ll A[maxn],B[maxn],C[maxn];
int check(int k) {
    int i;
    ll lx=-INF,rx=INF;
    FOR(i,1,n) {
        rx=min(rx,B[i]-A[i]*k+10);
        lx=max(lx,B[i]-A[i]*k-10);
    }
    // if (lx<=rx) printf("k=%d: %d %d\n",k,lx,rx);
    if (lx<=rx) return 1;
    lx=-INF,rx=INF;
    FOR(i,1,n) {
        rx=min(rx,B[i]-C[i]*k+10);
        lx=max(lx,B[i]-C[i]*k-10);
    }
    // if (lx<=rx) printf("2 k=%d: %d %d\n",k,lx,rx);
    if (lx<=rx) return 2;
    return 0;
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int k,i;
        scanf("%d",&n);
        FOR(i,1,n) scanf("%lld",&A[i]);
        FOR(i,1,n) scanf("%lld",&C[i]);
        FOR(i,1,n) scanf("%lld",&B[i]);
        FOR(k,0,1000000) {
            int now=check(k);
            if (!now) now=check(-k);
            if (!now) continue;
            printf("%d\n",now); break;
        }
    }
}
/*
2
5 1
4 3 5 1 2
5 4
4 3 5 1 2
*/