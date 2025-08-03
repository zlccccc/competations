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
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k;
int x1,x2,y1,y2,r;
double dx,dy,R;
double get(int x,int y){
    return sqrt((double)x*x+(double)y*y);
}
int main(){
    scanf("%d%d%d%d%d",&r,&x1,&y1,&x2,&y2);
    if (x1==x2&&y1==y2) dx=0,dy=1,R=1.*r/2;
    else{
        R=get(y1-y2,x1-x2);
        if (R>r) {
            printf("%.10lf %.10lf %.10lf\n",1.*x1,1.*y1,1.*r);
            return 0;
        }dx=(x1-x2)/R;
        dy=(y1-y2)/R;
        R=(R+r)/2;
    }
//    printf("x,y=%lf %lf R=%lf\n",dx,dy,R);
    printf("%.10lf %.10lf %.10lf\n",x2+dx*R,y2+dy*R,R);
}
/*
*/
