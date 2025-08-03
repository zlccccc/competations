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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
//昂神板子
struct Point {
    double x , y;
    Point (double x = 0 , double y = 0) : x(x) , y(y) {}
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
}P,A,B;
int n,q;
Point GetLineProjection(Point P , Point A , Point B) {
    Point v = B - A;
    return A + v * (v % (P - A) / (v % v));
}
int main() {
    int i,j,k;
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%lf%lf%lf%lf%lf%lf",&P.x,&P.y,&A.x,&A.y,&B.x,&B.y);
        Point mid=GetLineProjection(P,A,B);
        Point ans=mid+mid-P;
        printf("%.10f %.10f\n",mid.x,mid.y);
    }
    return 0;
}
/*
3 0 1 0 0 1 1 2.13 -6.89 1.78 1.20 -7.73 0.56 3.473 -4.326 -4.851 -0.819 2.467 -2.729
*/
