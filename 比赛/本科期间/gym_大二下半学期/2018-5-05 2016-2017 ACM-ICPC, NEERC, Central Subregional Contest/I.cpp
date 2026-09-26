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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
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

inline int dcmp(double x){
    return (x>eps)-(x<-eps);
}
struct Point{
    double x,y;
    Point(double _x=0,double _y=0):x(_x),y(_y){}
    double operator ^(const Point &R)const{
        return x*R.y-y*R.x;
    }
    void input() {
        scanf("%lf%lf",&x,&y);
    }
    bool operator == (const Point& R) const {
        return dcmp(x - R.x) == 0 && dcmp(y - R.y) == 0;
    }
    Point operator -(const Point &R)const{
        return Point(x-R.x,y-R.y);
    }
    double operator %(const Point &R)const{
        return x*R.x+y*R.y;
    }
    double len(){
        return sqrt(*this % *this);
    }
}A[maxn];
double DistanctPointToLine(Point P,Point A,Point B){
    Point v=B-A;
    return (v^(P-A))/v.len();
}
double DistancePointToSegment(Point P,Point A,Point B){
    if (A==B) return (P-A).len();
    Point v1=B-A,v2=P-A,v3=P-B;
    if (dcmp(v1%v2)<0) return v2.len();
    if (dcmp(v1%v3)>0) return v3.len();
    return fabs(v1^v2)/v1.len();
}
double DistanceSegmentToSegment(Point A1,Point A2,Point B1,Point B2){
    double ret=INF;
    ret=min(ret,DistancePointToSegment(A1,B1,B2));
    ret=min(ret,DistancePointToSegment(A2,B1,B2));
    ret=min(ret,DistancePointToSegment(B1,A1,A2));
    ret=min(ret,DistancePointToSegment(B2,A1,A2));
    return ret;
}
int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,m,k,i;
    scanf("%d%d%d",&n,&m,&k);
    if (n<k+m-4) return 0*puts("-1");
    if (n>k+m-2) return 0*puts("-1");
    if (k<3||m<3) return 0*puts("-1");
    FOR(i,1,n) A[i].input(),A[i+n+n]=A[i+n]=A[i];
    m--;k--;
    double ans=INF;
    FOR(i,n+1,n+n){
        if (n==k+m) ans=min(ans,(A[i]-A[i-m]).len());
        else if (n==k+m-1){
            ans=min(ans,DistancePointToSegment(A[i],A[i-m],A[i-m+1]));
            ans=min(ans,DistancePointToSegment(A[i],A[i-k],A[i-k+1]));
        }else{
            ans=min(ans,DistanceSegmentToSegment(A[i],A[i+1],A[i-m+1],A[i-m+2]));
            ans=min(ans,DistanceSegmentToSegment(A[i],A[i+1],A[i-k+1],A[i-k+2]));
        }
    }reverse(A+1,A+1+n+n+n);
    FOR(i,n+1,n+n){
        if (n==k+m) ans=min(ans,(A[i]-A[i-m]).len());
        else if (n==k+m-1){
            ans=min(ans,DistancePointToSegment(A[i],A[i-m],A[i-m+1]));
            ans=min(ans,DistancePointToSegment(A[i],A[i-k],A[i-k+1]));
        }else{
            ans=min(ans,DistanceSegmentToSegment(A[i],A[i+1],A[i-m+1],A[i-m+2]));
            ans=min(ans,DistanceSegmentToSegment(A[i],A[i+1],A[i-k+1],A[i-k+2]));
        }
    }
    printf("%.3f\n",ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
/*
4 4 4 0 0 1 1 2 1 1 0
*/
