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
typedef array<int,2> ar2;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

deque<pair<ll,ll> > Q;
int A[maxn][2]; // Sum,Count (visit f(0/1) first)
int main() {
    int n; scanf("%d",&n);
    FOR_(i,1,n) scanf("%d",&A[i][0]);
    FOR_(i,1,n) scanf("%d",&A[i][1]);
    ll MID=0,nowans=0,ans=0;
    FOR_(i,1,n) {
        ll x=A[i][0],y=A[i][1];
        add_(nowans,(x+y)*((i-1)*2)%M);
        ll add_back=0,add_front=0;;
        while (Q.size()) {
            pll p=Q.front();
            ll div=p.first+MID;
            if (div>-x) break;
            Q.pop_front();
            // a+b -> a+a+x
            add_(add_front,p.second);
            add_(nowans,(div+x)%M*p.second%M+M);
        }
        while (Q.size()) {
            pll p=Q.back();
            ll div=p.first+MID;
            if (div<y) break;
            Q.pop_back();
            // a+b -> b+b+y
            add_(add_back,p.second);
            add_(nowans,(-div+y)%M*p.second%M+M);
        }
        // printf("chg:nowans=%lld\n",nowans);
        // for (auto now:Q) printf("(%lld,%lld)  ",now.first+MID,now.second); puts("<- chg Q");
        // x<=a-b<=y
        // (-y,x+x+y); (x,x+y+y)
        add_(nowans,3*(x+y)%M); // just this
        ++add_front; ++add_back;
        MID+=x-y;
        Q.push_front({-y-MID,add_front});
        Q.push_back({x-MID,add_back});
        // printf("nowans=%lld\n",nowans);
        // for (auto now:Q) printf("(%lld,%lld)  ",now.first+MID,now.second); puts("<- Q");
        add_(ans,nowans); // left-to-this
        add_(ans,nowans); // single
        add_(ans,(M-3)*(x+y)%M); // same
    }
    printf("%lld\n",ans);
}
/*
5
1 3 2 1 2
3 1 3 2 1
*/