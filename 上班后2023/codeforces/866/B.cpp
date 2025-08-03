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
const LL maxn=2e5+107;
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
    ll az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
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
 
pii rect[maxn];
bool check(int n,ll x,ll y) {
    multiset<pii> vx,vy;
    FOR_(i,1,n) vx.insert({rect[i].first,rect[i].second});
    FOR_(i,1,n) vy.insert({rect[i].second,rect[i].first});
    while (vx.size()&&vy.size()) {
        // printf("x,y=%lld %lld  (%d %d); (%d %d)\n",x,y,(*vx.rbegin()).first,(*vx.rbegin()).second,(*vy.rbegin()).first,(*vy.rbegin()).second);
        if (vx.size()&&(*vx.rbegin()).first==x) {
            int nx=(*vx.rbegin()).first,ny=(*vx.rbegin()).second;
            y-=ny;
            vx.erase(vx.lower_bound({nx,ny}));
            vy.erase(vy.lower_bound({ny,nx}));
            continue;
        }
        if (vy.size()&&(*vy.rbegin()).first==y) {
            int ny=(*vy.rbegin()).first,nx=(*vy.rbegin()).second;
            x-=nx;
            vx.erase(vx.lower_bound({nx,ny}));
            vy.erase(vy.lower_bound({ny,nx}));
            continue;
        }
        return 0;
    }
    return 1;
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n;
        scanf("%d",&n);
        int MAXX=0,MAXY=0; ll all=0;
        FOR_(i,1,n) {
            scanf("%d%d",&rect[i].first,&rect[i].second);
            all+=(ll)rect[i].first*rect[i].second;
            max_(MAXX,rect[i].first);
            max_(MAXY,rect[i].second);
        }
        set<pll> ans;
        if (all%MAXX==0&&check(n,MAXX,all/MAXX)) ans.insert({MAXX,all/MAXX});
        if (all%MAXY==0&&check(n,all/MAXY,MAXY)) ans.insert({all/MAXY,MAXY});
        printf("%d\n",(int)ans.size());
        for (auto now:ans) printf("%lld %lld\n",now.first,now.second);
     }
}
/*
3
6
1 1
1 3 4 3 1
4 3 1 2 5
 
 
6
1 1
3
2
1
4
1
4
1
2
3
5
 
 
5
7
*/