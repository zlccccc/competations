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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

ll B,MMOD;
struct cpx {
    ll x,y;
    cpx(ll a=0,ll b=0):x(a),y(b) {}
};

cpx operator + (cpx a,cpx b) {cpx re= cpx( (a.x+b.x)%MMOD, (a.y+b.y)%MMOD);if(re.x<0)re.x+=MMOD;if(re.y<0)re.y+=MMOD;return re; }
cpx operator - (cpx a,cpx b) {cpx re=cpx( (a.x-b.x)%MMOD, (a.y-b.y)%MMOD);if(re.x<0)re.x+=MMOD;if(re.y<0)re.y+=MMOD;return re; }
cpx operator * (cpx a,cpx b) {cpx re=cpx( (a.x*b.x+a.y*b.y%MMOD*B)%MMOD,(a.x*b.y+a.y*b.x)%MMOD ); if(re.x<0)re.x+=MMOD;if(re.y<0)re.y+=MMOD;return re;}

//inline ll poww(ll a, ll b,ll M) {
//    ll ret=1;
//    a=(a%M+M)%M;
//    for (; b; b>>=1ll,a=(ll)a*a%M)
//        if (b&1LL) ret=(ll)ret*a%M;
//    return ret;
//}

inline cpx poww(ll x,ll y, ll b,ll z) {
    cpx ret=cpx(1,0);
    cpx a;a.x=x;a.y=y;
    a.x%=MMOD;
//    a.x=(a.x+MMOD)%MMOD;
    if(a.x<MMOD)a.x+=MMOD;
    a.y%=MMOD;
    if(a.y<MMOD)a.y+=MMOD;
//    a.y=(a.y+MMOD)%MMOD;

//    ll ret=1;
//    a=(a%M+M)%M;
    for (; b; b>>=1ll,a=a*a)
        if (b&1LL) ret=ret*a;
    return ret;
}
int C[maxn];
int main() {
    int T,_t,i;
    scanf("%d",&T);
    FOR(i,1,1000) for (int j=i*i;j<=1000000;j+=i*i) C[j]=i;
    FOR(_t,1,T){
        int A,B1; ll n,p;
        scanf("%d%d%lld%lld",&A,&B1,&n,&p);
        MMOD=2LL*p;
        B=B1/C[B1]/C[B1];
        printf("1 %lld %d\n",((poww(A,C[B1],n,2*p)-poww(A,-C[B1],n,2*p)).y/2LL%p+p)%p,B1/C[B1]/C[B1]);
//        printf("1 %lld %d\n",((poww(A+C[B],n,2*p)-poww(A-C[B],n,2*p))/2%p+p)%p,B/C[B]/C[B]);
    }
}
/*
10
1 1
*/