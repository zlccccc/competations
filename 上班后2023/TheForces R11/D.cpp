// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
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
#include <functional>
#include <random>
#include <unordered_set>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP_(I,N) for (int I=0;I<N;I++)
#define rREP_(I,N) for (int I=N-1;I>=0;I--)
#define rep_(I,S,N) for (int I=S;I<N;I++)
#define rrep_(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR_(I,S,N) for (int I=S;I<=N;I++)
#define rFOR_(I,S,N) for (int I=N;I>=S;I--)

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
// const LL M=1e9+7;
const LL M=998244353;
// ll M=1;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

int f(int n,int i) {
    int cnt0=0,cnt1=0;
    if (n&(1<<i)) cnt0+=n%(1<<i);
    cnt0+=n>>(i+1)<<i; //一半一半
    REP_(x,n) if (x&(1<<i)) cnt1++;
    // printf("%d; i=%d: %d %d\n",n,i,cnt0,cnt1);

    int odd=0;
    if (i==0) odd=(n>>1)&1;
    else odd=((n>>i)&1)&&(n&1);
    if (odd!=(cnt1&1)) puts("??");
    return odd;
    // printf("%d; i=%d: odd=%d; %d\n",n,i,odd,cnt1&1);
}
int g(int n,int i) {
    // if (i==0) odd=(n>>1)&1;
    // else odd=((n>>i)&1)&&(n&1);
    int one=0;
    int cnt=0;
    // REP_(x,n) if (f(x,i)) cnt++;
    if (i==0) {
        if (n&2) one+=n%2;
        one+=n/4*2;
    } else {
        if ((n>>i)&1) {
            int k=n%(1<<i);
            one+=k/2;
        } n-=n%(1<<(i+1));
        one+=n/2/2;
    }
    // if (one!=cnt) printf("g: %d,%d: %d %d\n",n,i,one,cnt);
    return one;
}
int main() {
    FOR_(i,0,10) FOR_(n,0,1000) g(n,i);
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n;
        scanf("%d",&n);
        int ans=0;
        REP_(i,30) {
            int one=g(n+1,i);
            int zero=n+1-one;
            // printf("n=%d; i=%d; one=%d; zero=%d\n",n,i,one,zero);
            add_(ans,(ll)one*zero%M*(1<<i)%M);
        }
        printf("%d\n",ans);
    }
}
/*
*/