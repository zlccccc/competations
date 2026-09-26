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
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

inline int dcmp(double x) {
    return (x > 0) - (x < 0);
}
struct Point {
    ll x,y;
    Point (ll x = 0 , ll y = 0) : x(x) , y(y) {}
    void input() {
        scanf("%lld%lld",&x,&y);
    }
    bool operator < (const Point& R) const {
        if (dcmp(x - R.x) == 0)
            return dcmp(y - R.y) < 0;
        return dcmp(x - R.x) < 0;
    }
    bool operator == (const Point& R) const {
        return dcmp(x - R.x) == 0 && dcmp(y - R.y) == 0;
    }
    Point operator + (const Point& R) const {
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point& R) const {
        return Point(x - R.x , y - R.y);
    }
    Point operator * (const double& R) const {
        return Point(x * R , y * R);
    }
    Point operator / (const double& R) const {
        return Point(x / R , y / R);
    }
    ll operator ^ (const Point& R) const {
        return x * R.y - y * R.x;
    }
    ll operator % (const Point& R) const {
        return x * R.x + y * R.y;
    }
    ll len() { // not sqrt
        return (*this % *this);
    }
}P[maxn];
// 判断线段是否严格相交。
bool SegmentProperIntersection(Point a1 , Point a2 , Point b1 , Point b2) {
    ll c1 = (a2 - a1) ^ (b1 - a1);
    ll c2 = (a2 - a1) ^ (b2 - a1);
    if (dcmp(c1) == 0 && dcmp(c2) == 0) {
        if (a2 < a1) swap(a1 , a2);
        if (b2 < b1) swap(b1 , b2);
        return max(a1 , b1) < min(a2 , b2);
    }
    ll c3 = (b2 - b1) ^ (a1 - b1);
    ll c4 = (b2 - b1) ^ (a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
// 点是否在线段上,判定方式为到两个端点的方向是否不一致。
bool OnSegment(Point P , Point a1 , Point a2) {
    ll len = (P - a1).len();
    if (dcmp(len) == 0) return true;
    a1 = a1 - P , a2 = a2 - P;
    return dcmp(a1 ^ a2) == 0 && dcmp(a1 % a2) <= 0;
}

int main() {
    int n;
    scanf("%d",&n);
    REP_(i,n) P[i].input();
    REP_(i,n+n) P[i+n]=P[i];
    int A=0;
    while (P[A+1].x<=P[A].x) A++; // left-down
    int B=A;
    while (P[B+1].x>=P[B].x) B++; // right-top
    int C=A+n;
    auto check=[&](Point x,Point y,Point sol) {
        // on-segment
        return 1;
    };
    rep_(i,A,B+1) printf("(%lld,%lld) ",P[i].x,P[i].y); puts("<- fir");
    rep_(i,B,C+1) printf("(%lld,%lld) ",P[i].x,P[i].y); puts("<- sec");
    int q; scanf("%d",&q);
    REP_(i,q) {
        Point now; now.input();
        Point nxt; nxt=Point(now.x-1,INFF);
        int ans=0;
        {
            int id=upper_bound(P+A,P+B+1,now)-P;
            printf("left-id=%d\n",id);
            if (A<id&&id<B+1) {
                Point x=P[id-1],y=P[id];
                printf("%lld %lld -> %lld %lld\n",x.x,x.y,y.x,y.y);
                if (OnSegment(now,x,y)) {puts("ON"); continue;}
                ans^=SegmentProperIntersection(x,y,now,nxt);
            }
        }
        {
            int id=upper_bound(P+B,P+C+1,now,less<Point>())-P;
            printf("right-id=%d\n",id);
            if (B<id&&id<C+1) {
                Point x=P[id-1],y=P[id];
                printf("%lld %lld -> %lld %lld\n",x.x,x.y,y.x,y.y);
                if (OnSegment(now,x,y)) {puts("ON"); continue;}
                ans^=SegmentProperIntersection(x,y,now,nxt);
            }
        }
        if (ans) puts("IN");
        else puts("OUT");
    }
}
/*
*/