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
const LL maxn=4e4+107;
// const double pi=acos(-1.0);
// const double eps=0.0000000001;
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

const double eps = 1e-10 , pi = acos(-1.0);
inline int dcmp(double x) {
    return (x > eps) - (x < -eps);
}

struct Point {
    double x , y;
    Point (double x = 0 , double y = 0) : x(x) , y(y) {}
    void input() {
        scanf("%lf%lf",&x,&y);
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
    double operator ^ (const Point& R) const {
        return x * R.y - y * R.x;
    }
    double operator % (const Point& R) const {
        return x * R.x + y * R.y;
    }
    double len() {
        return sqrt(*this % *this);
    }
    double angle() {
        return atan2(y , x);
    }
};
// 两个向量的夹角，不分正负[0,pi)
double Angle(Point A , Point B) {
    return acos((A % B) / A.len() / B.len());
}
// 逆时针旋转
Point Rotate(Point A , double rad) {
    double Sin = sin(rad) , Cos = cos(rad);
    return Point(A.x * Cos - A.y * Sin , A.x * Sin + A.y * Cos);
}
// 向量的单位法向量，利用旋转得到
Point Normal(Point A) {
    double L = A.len();
    return Point(-A.y / L , A.x / L);
}
// 直线交点，v和w为两个直线的方向向量，
// 设交点的参数为P+vt,Q+wt,连立方程解t
// 线段，射线对这个t的参数有限制，很好理解。
Point GetLineIntersection(Point P , Point v , Point Q , Point w) {
    Point u = P - Q;
    double t1 = (w ^ u) / (v ^ w);
    return P + v * t1;
}
// 点到直线有向距离，这里直线是用两个点表示的
double DistancePointToLine(Point P , Point A , Point B) {
    Point v = B - A;
    return (v ^ (P - A)) / v.len();
}
// 点到线段距离，就是上面的代码判断一下P在AB上投影的位置。
double DistancePointToSegment(Point P , Point A , Point B) {
    if (A == B) return (P - A).len();
    Point v1 = B - A , v2 = P - A , v3 = P - B;
    if (dcmp(v1 % v2) < 0) return v2.len();
    if (dcmp(v1 % v3) > 0) return v3.len();
    return fabs(v1 ^ v2) / v1.len();
}
// 返回点在直线上的投影
Point GetLineProjection(Point P , Point A , Point B) {
    Point v = B - A;
    return A + v * (v % (P - A) / (v % v));
}
// 判断线段是否严格相交。
bool SegmentProperIntersection(Point a1 , Point a2 , Point b1 , Point b2) {
    double c1 = (a2 - a1) ^ (b1 - a1);
    double c2 = (a2 - a1) ^ (b2 - a1);
    if (dcmp(c1) == 0 && dcmp(c2) == 0) {
        if (a2 < a1) swap(a1 , a2);
        if (b2 < b1) swap(b1 , b2);
        return max(a1 , b1) < min(a2 , b2);
    }
    double c3 = (b2 - b1) ^ (a1 - b1);
    double c4 = (b2 - b1) ^ (a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
// 点是否在线段上,判定方式为到两个端点的方向是否不一致。
bool OnSegment(Point P , Point a1 , Point a2) {
    double len = (P - a1).len();
    if (dcmp(len) == 0) return true;
    a1 = a1 - P , a2 = a2 - P;
    return dcmp((a1 ^ a2) / len) == 0 && dcmp(a1 % a2) <= 0;
}
inline LL OnLeft(Point P , Point A , Point B) {
    return (B - A) ^ (P - A);
}

int n;
Point p[maxn],s[maxn];
int solve_0() {
    /********* Naive 凸包 2.0 O(n+m) *********/
    sort(p,p+n);
    int top = 0;
    for (int i = 0 ; i < n ; ++ i) {
        while (top > 1 && OnLeft(p[i] , s[top - 2] , s[top - 1]) <= 0) {
            -- top;
        }
        s[top ++] = p[i];
    }
    int tmp = top;
    for (int i = n - 2 ; i >= 0 ; -- i) {
        while (top > tmp && OnLeft(p[i] , s[top - 2] , s[top - 1]) <= 0) {
            -- top;
        }
        s[top ++] = p[i];
    }
    if (n > 1)
        -- top;
    return top;
}


int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i; scanf("%d",&n); n*=4;
        REP(i,n) p[i].input();
        n=solve_0();//凸包
        // REP(i,n) printf("%f %f\n",s[i].x,s[i].y);
        printf("Case #%d:\n",_);
        s[n]=s[0];
        double ans=INF;
        REP(i,n) {
            int k;
            double maxd=0,l=0,r=0;
            Point nxt=s[i+1]-s[i];
            nxt=nxt/nxt.len();
            REP(k,n) {
                double x=nxt%(s[k]-s[i]);
                double y=nxt^(s[k]-s[i]);
                min_(l,-x); max_(r,-x); max_(maxd,y);
                // printf("%f %f %f\n",x,y,maxd);
            }
            ans=min(ans,maxd*(r-l));
        }
        printf("%.0f\n",ans);
    }
}
/*
*/