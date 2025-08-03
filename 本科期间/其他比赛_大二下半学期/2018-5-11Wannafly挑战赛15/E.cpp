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

LL P,Q;
struct node{
    LL x,y;
}p[maxn];
int main() {
    int n,i;
    scanf("%d%lld%lld",&n,&P,&Q);
    REP(i,n) scanf("%lld%lld",&p[i].x,&p[i].y);
    sort(p,p+n,[](node &A,node &B){
        return A.x*P-A.y*Q<B.x*P-B.y*Q;
    });
//    puts("");
//    REP(i,n) printf("%lld %lld  %lld\n",p[i].x,p[i].y,p[i].x*P-p[i].y*Q);
    REP(i,n-1){
        p[i].x-=p[i+1].x;
        p[i].y-=p[i+1].y;
        if (p[i].y<0) {
            p[i].x=-p[i].x;
            p[i].y=-p[i].y;
        }
        if (p[i].y==0) p[i].x=1;
        else if (p[i].x==0) p[i].y=1;
        else{
            LL g=gcd(abs(p[i].x),abs(p[i].y));
            p[i].x/=g;
            p[i].y/=g;
        }
    }
//    puts("");
//    REP(i,n-1) printf("%lld %lld\n",p[i].y,p[i].x);
    sort(p,p+n-1,[](node &A,node &B){
        return (__int128)abs((A.y*Q-A.x*P))*abs(B.x)<(__int128)abs((B.y*Q-B.x*P))*abs(A.x);
    });
    printf("%lld/%lld",p[0].y,p[0].x);
}
/*
10 15698 17433
112412868 636515040
122123982 526131695
58758943 343718480
447544052 640491230
162809501 315494932
870543506 895723090
1 1
2 2
3 0
0 1
*/
