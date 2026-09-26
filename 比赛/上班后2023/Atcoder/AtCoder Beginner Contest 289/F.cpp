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
// const LL M=585698298;
// const LL M=998244353;
const LL M=1e9+7;
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

int sx,sy,tx,ty;
int a,b,c,d;
int main() {
    // must be a point!
    scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
    scanf("%d%d%d%d",&a,&b,&c,&d);
    if ((sx^tx)&1) return 0*puts("No");
    if ((sy^ty)&1) return 0*puts("No");
    // solve A-B
    bool s1=1,s0=1;
    if (a==b) {
        if (sx!=tx) s0=0;
        if (sx+tx!=a+a) s1=0;  
    } else b=a+1; // 对称
    if (c==d) {
        if (sy!=ty) s0=0;
        if (sy+ty!=c+c) s1=0;
    } else d=c+1; // 对称
    if (!s0&&!s1) return 0*puts("No");
    // if (sx==tx&&sy==ty) return 0*puts("Yes\n0");
    vector<pii> ans;
    if (!s0) {
        ans.push_back({a,c});
        sx=a+a-sx;
        sy=c+c-sy;
    }
    // int length=min(abs(sx-tx),abs(sy-ty));
    while (sx!=tx||sy!=ty) {
        // printf("solve %d %d  %d %d\n",sx,tx,sy,ty);
        ar4 now={a,a,c,c};
        if (sx!=tx) {
            if (sx<tx) now[1]=b; else now[0]=b;
        }
        if (sy!=ty) {
            if (sy<ty) now[3]=d; else now[2]=d;
        }
        ans.push_back({now[0],now[2]});
        ans.push_back({now[1],now[3]});
        sx+=now[1]*2-now[0]*2;
        sy+=now[3]*2-now[2]*2;
    }
    puts("Yes");
    // printf("%d\n",(int)ans.size());
    for (auto p:ans) printf("%d %d\n",p.first,p.second);
}
/*
0 0
8 4
4 4 2 2


*/