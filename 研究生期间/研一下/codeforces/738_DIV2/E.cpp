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
const LL maxn=2e5+107;
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

int n,m;
int L[maxn],R[maxn];
int Nxt[maxn],Val[maxn];
int solve() {
    int i,j;
    Val[0]=1; FOR(j,1,m) Val[j]=0;
    FOR(i,1,n) {
        FOR(j,0,m) Nxt[j]=0;
        FOR(j,0,m) add_(Nxt[j+L[i]],Val[j]),add_(Nxt[j+R[i]+1],M-Val[j]);
        FOR(j,0,m) Val[j]=Nxt[j];
        FOR(j,1,m) add_(Val[j],Val[j-1]);
        // printf("%d -> %d\n",L[i],R[i]);
        // FOR(j,0,m) printf("%d ",Val[j]); puts(" <- val");
    } int ans=0;
    // printf("m=%d\n",m);
    FOR(j,0,m) add_(ans,Val[j]);
    return ans;
}
int _m;
int _L[maxn],_R[maxn];
int A[maxn];
int main() {
    int i,k;
    scanf("%d%d",&n,&_m);
    FOR(i,1,n) scanf("%d%d",&_L[i],&_R[i]);
    rFOR(k,1,_m) {
        m=_m/k;
        FOR(i,1,n) L[i]=(_L[i]-1+k)/k,R[i]=_R[i]/k;
        A[k]=solve();
        // printf("before solve %d %d\n",k,A[k]);
        for (i=k+k;i<=_m;i+=k) add_(A[k],M-A[i]);
        // if (A[k]!=0) 
        // printf("solve %d %d\n",k,A[k]);
    } printf("%d\n",A[1]);
}
/*
*/