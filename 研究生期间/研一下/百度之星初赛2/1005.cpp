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

int A[maxn];
ll getval(int n) {
    ll all=0; int i;
    // FOR(i,1,n) val[i]=0,fa[i]=i,sz[i]=1;
    // FOR(i,1,n) {
    //     int x=getfa(i),y=getfa(A[i]);
    //     if (x!=y) fa[x]=y,sz[y]+=sz[x];
    //     // if (abs(i-getx(A[i]))<n/4) all++;
    //     // // all+=getx(A[i]); 
    //     // addx(A[i],n);
    // }
    // FOR(i,1,n) all=max(all,(ll)sz[i]);
    // // FOR(i,1,n) all+=sz[getfa(i)];
    // return all;
    // // FOR(i,1,n) if (A[i]==i) all++;
    // return all/n;
    // FOR(i,1,n) {
    //     int now=0;
    //     for (int x=A[i];x!=i;x=A[x]) now++;
    //     L[i]=now;
    // }
    FOR(i,1,n) {
        int x=A[i],k;
        REP(k,10) if (x==i) all++; x=A[x];
    }
    return all;
}
void solve(int n) {
    int i;
    int ans=getval(n);
    if (ans<100) puts("Second");
    else puts("First");
}
void check(int n) {
    int i;
    FOR(i,1,n) A[i]=i;
    FOR(i,1,n*3) {
        int x,y;
        x=((rand()<<16)|rand())%n+1;
        y=((rand()<<16)|rand())%n+1;
        // if (x==y) i--;
        // printf("swap %d %d\n",x,y);
        swap(A[x],A[y]);
    }
    // FOR(i,1,n) printf("%d ",A[i]); puts("<- swap 3 times"/);
    solve(n);
    printf("%lld\n",getval(n));
    FOR(i,1,n*4) {
        int x,y;
        x=((rand()<<16)|rand())%n+1;
        y=((rand()<<16)|rand())%n+1;
        // if (x==y) i--;
        swap(A[x],A[y]);
    }
    solve(n);
    printf("%lld\n",getval(n));
    // FOR(i,1,n) printf("%d ",A[i]); puts("<- swap 7 times");
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i,n;
        scanf("%d",&n);
        // check(n);
        FOR(i,1,n) scanf("%d",&A[i]);
        solve(n);
    }
}
/*
100
1000
1000
50000
50000
100000
100000
100000
*/