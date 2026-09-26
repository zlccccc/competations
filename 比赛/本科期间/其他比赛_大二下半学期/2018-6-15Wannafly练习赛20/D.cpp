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

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1<<24|7;
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

double dis[maxn];
vector<pair<double,double> > points;
double ans=0;
inline double dist(double a,double b){
    return sqrt(a*a+b*b);
}
void dfs(int x){
    int i;
    REP(i,points.size()){
        double distance=dis[x]+abs(points[i].first-points[x].first)+abs(points[i].second-points[x].second);
        if (i>3&&x>3) distance=dis[x]+dist(points[i].first-points[x].first,points[i].second-points[x].second);
        if (distance+eps<dis[i]){
//            printf("%d -> %d %f\n",i,x,distance);
            dis[i]=distance;
            dfs(i);
        }
    }
}
int main() {
    int m,i;
    int T=1;
    scanf("%d",&T);
    while (T--){
        double xa,xb,ya,yb,P,Q,R;
        scanf("%lf%lf%lf%lf",&xa,&ya,&xb,&yb);
        scanf("%lf%lf%lf",&P,&Q,&R);
        points.clear();
        points.push_back(make_pair(xa,ya));
        points.push_back(make_pair(xb,ya));
        points.push_back(make_pair(xa,yb));
        points.push_back(make_pair(xb,yb));
        double ans=abs(xa-xb)+abs(ya-yb);
        double _x,_y;
        if (Q&&P) {
            _y=(R-P*xa)/Q; points.push_back(make_pair(xa,_y));
            _y=(R-P*xb)/Q; points.push_back(make_pair(xb,_y));
            _x=(R-Q*ya)/P; points.push_back(make_pair(_x,ya));
            _x=(R-Q*yb)/P; points.push_back(make_pair(_x,yb));
        }REP(i,points.size()) dis[i]=INF;
//        for (auto now:points) printf(" %f %f\n",now.first,now.second);
        dis[0]=0; dfs(0);
//        printf("%.3f\n",ans);
        printf("%.3f\n",dis[3]);
    }
}
/*
2
2 0 -1 1 1.0 1.0 1.0
-2 3 4 -1 1.0 -0.1 0.47
*/
