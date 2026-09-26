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
#include <bitset>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=1e-10;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

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
struct Circle {
    Point O;
    double r;
    Circle () {}
    Circle (Point _O , double _r) {
        O = _O , r = _r;
    }
    Point point(double arc) {
        return Point(O.x + cos(arc) * r , O.y + sin(arc) * r);
    }
    void input() {
        O.input() , scanf("%lf",&r);
    }
};
// 判定圆和圆之间的关系
// 内含，内切，相交，重合，外切，相离
int getCircleCircleIntersection(Circle C1 , Circle C2 , vector<Point>& sol) {
    double d = (C1.O - C2.O).len();
    if (dcmp(d) == 0) { //同心
        if (dcmp(C1.r - C2.r) == 0)//重合
            return -1;
        return 0;//内含
    }
    if (dcmp(C1.r + C2.r - d) < 0) return 0;//相离
    if (dcmp(fabs(C1.r - C2.r) - d) > 0) return 0;//内含
    double a = (C2.O - C1.O).angle();
    double p = (C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d);
    p = max(-1.0 , min(1.0 , p));
    double da = acos(p);
    Point P1 = C1.point(a - da) , P2 = C1.point(a + da);
    sol.push_back(P1);
    if (dcmp(da) == 0) return 1; //切
    sol.push_back(P2);
    return 2;
}

//以上是昂神的板子
int n;
Circle P[maxn];
int X[maxn],Y[maxn],R[maxn];
vector<Point> all,now;
int S[maxn],top,ans;
bool checked[maxn];
int main(){
    int i,j,k;
    scanf("%d",&n);
    REP(i,n) {
        scanf("%d%d%d",&X[i],&Y[i],&R[i]);
        X[i]*=10000;Y[i]*=10000;R[i]*=10000;
//        X[i]*=10;Y[i]*=10;R[i]*=10;
    }
    REP(i,n) P[i]=Circle(Point(X[i],Y[i]),R[i]);
    REP(i,n) if (!checked[i]){
        S[top++]=i;checked[i]=1;
        while (top){
            top--;
            REP(j,n) if (!checked[j]){
                int tmp=getCircleCircleIntersection(P[S[top]],P[j],now);
//                printf("check insert:%d %d\n",S[top],j);
                if (tmp==-1||tmp==0) continue;
                if (!checked[j]) S[top++]=j;
                checked[j]=1;
            }
        }ans++;
    }
//    printf("ans=%d\n",ans);
    REP(i,n){
        now.clear();
        REP(j,n) if (j!=i){
            getCircleCircleIntersection(P[i],P[j],now);
            getCircleCircleIntersection(P[i],P[j],all);
        }sort(now.begin(),now.end());
        now.erase(unique(now.begin(),now.end()),now.end());
        ans+=now.size();
    }
//    printf("ans=%d\n",ans);
    sort(all.begin(),all.end());
//    for (auto &now:all) printf("%.10lf %.10lf\n",now.x,now.y);puts("");
    all.erase(unique(all.begin(),all.end()),all.end());
//    for (auto &now:all) printf("%.10lf %.10lf\n",now.x,now.y);puts("");
    ans-=all.size();
    printf("%d\n",ans+1);
}
/*
3
3 -2 7
-1 2 5
-4 1 3
*/
