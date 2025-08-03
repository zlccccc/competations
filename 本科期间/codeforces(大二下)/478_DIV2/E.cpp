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
#include <iomanip>
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
const LL maxn=4e5+7;
const double pi=acos(-1.0);
const double eps=1e-10;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

//#define double long double
inline int dcmp(double x) {
    return (x > eps) - (x < -eps);
}
struct Point {
    double x , y;
    Point (double x = 0 , double y = 0) : x(x) , y(y) {}
    void input() {
//        cin>>x>>y;
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
}P[maxn],nowpos;
double theta;
int n,m;
int main() {
    int i;
    int n,q;
//    printf("%f\n",sin(pi/3));
    scanf("%d%d",&n,&q);
    REP(i,n) P[i].input();
    Point middle;
    {//get_middle
        double all=0;
        rep(i,2,n) {
            double now=(P[i-1]-P[0])^(P[i]-P[0]);
            middle=middle+(P[i-1]+P[i])*now;
            all=all+now;
        }middle=middle/all;
        middle=(middle+P[0])/3;
    }nowpos=middle;
//    printf("%f %f\n",middle.x,middle.y);
    int nowpin=1;theta=pi/2;
    REP(i,q){
        int op;
        scanf("%d",&op);
        if (op==1){
            int f,t;
            scanf("%d%d",&f,&t);
            f--;t--;
            nowpin^=f;
            int id=nowpin;
            Point Div=middle-P[id];

            double alpha=Div.angle()+theta-pi/2;
            Point Add=Point(Div.len()*cos(alpha),Div.len()*sin(alpha));
            Point ans=nowpos-Add;

            theta=-Div.angle();
            nowpos=ans+Point(0,-Div.len());
            nowpin^=t;
        }else{
            int v;
            scanf("%d",&v);v--;
            Point Div=middle-P[v];
            double alpha=Div.angle()+theta-pi/2;
            Point Add=Point(Div.len()*cos(alpha),Div.len()*sin(alpha));
            Point ans=nowpos-Add;
            printf("%.10f %.10f\n",ans.x,ans.y);
//            cout<<fixed<<setprecision(10)<<ans.x<<" "<<ans.y<<"\n";
//            printf("alpha=%f\n",alpha/pi*180);
        }
//        printf("theta=%f\n",theta/pi*180);
//        printf("middle=%f %f\n",nowpos.x,nowpos.y);puts("");
    }
    return 0;
}
/*

*/
