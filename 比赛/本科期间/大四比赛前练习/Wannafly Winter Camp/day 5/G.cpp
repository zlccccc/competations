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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
// int n,m,q;
// char str[maxn];//倒着的

struct Point {
    ll x , y;
    void input() {
        scanf("%lld%lld",&x,&y);
    }
    Point(ll x = 0 , ll y = 0) : x(x) , y(y) {}
    __int128 operator ^ (const Point &R) const {
        return (__int128)x * R.y - (__int128)y * R.x;
    }
    bool operator < (const Point &R) const {
        if (x - R.x == 0) return y - R.y < 0;
        return x - R.x < 0;
    }
    Point operator - (const Point &R) const {
        return Point(x - R.x , y - R.y);
    }
    __int128 operator % (const Point &R) const {
        return (__int128) x * R.x + (__int128)y * R.y;
    }
    __int128 len() {
        return *this % *this;
    }
    void print() {
        printf("(%lld,%lld)",x,y);
    }
} P[maxn];
// 判断线段是否严格相交。
bool SegmentProperIntersection(Point a1 , Point a2 , Point b1 , Point b2) {
    __int128 c1 = (a2 - a1) ^ (b1 - a1);
    __int128 c2 = (a2 - a1) ^ (b2 - a1);
    if (c1 == 0 && c2 == 0) {//平行
        if (a2 < a1) swap(a1 , a2);
        if (b2 < b1) swap(b1 , b2);
        return max(a1 , b1) < min(a2 , b2);
    }
    __int128 c3 = (b2 - b1) ^ (a1 - b1);
    __int128 c4 = (b2 - b1) ^ (a2 - b1);
    return (__int128)c1 * c2 < 0 && (__int128)c3 * c4 < 0;
}
bool OnSegment(Point P , Point a1 , Point a2) {
    __int128 len = (P - a1).len();
    if (len == 0) return true;
    a1 = a1 - P , a2 = a2 - P;
    // a1.print(); a2.print();
    // printf("  : %lld %lld\n",(ll)(a1^a2),(ll)(a1%a2));
    return (a1 ^ a2) == 0 && a1 % a2 <= 0;
}
int u[maxn],v[maxn];
int main() {
    int n,m; int ans=0;
    scanf("%d%d",&n,&m);
    int i,j;
    FOR(i,1,n) scanf("%d",&A[i]);
    sort(A+1,A+1+n);
    
}
/*
5 6
1 2
1 3
2 3
1 4
2 5
4 5

1 1
1 2
1 3
2 2
0 2
*/