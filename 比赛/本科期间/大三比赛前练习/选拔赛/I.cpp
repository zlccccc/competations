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
const LL maxn=5e5+7;
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

LL f[27][2][2];
int value_i[27];
int value_j[27];
int limit[27];
LL calc(int x,int flagi,int flagj){
//    printf("%d %d %d\n",x,flagi,flagj);
    if (x==0) return 1;
    if (f[x][flagi][flagj]!=-1)
        return f[x][flagi][flagj];
    LL ret=0;int i,j,maxi=9,maxj=9;
    if (flagi) maxi=min(maxi,value_i[x]);
    if (flagj) maxj=min(maxj,value_j[x]);
    FOR(i,0,maxi) {
        FOR(j,0,maxj) {
            if ((i+j)%10==limit[x]){
//                printf("%d %d (%d)\n",i,j,x);
                ret+=calc(x-1,flagi&&(i==maxi),flagj&&(j==maxj));
            }
        }
    }f[x][flagi][flagj]=ret;
    return ret;
}
LL solve(LL x,LL y,LL k){
    if (x<0||y<0) return 0;
    memset(value_i,0,sizeof(value_i));
    memset(value_j,0,sizeof(value_j));
    memset(limit,0,sizeof(limit));
    int length=0,L=0;
    while (x) value_i[++L]=x%10,x/=10;
    length=max(length,L);L=0;
    while (y) value_j[++L]=y%10,y/=10;
    length=max(length,L);L=0;
    while (k) limit[++L]=k%10,k/=10;
    if (L>length) return 0;
    memset(f,0xff,sizeof(f));
    return calc(length,1,1);
}
LL Solve(LL l,LL r,LL k){
//    printf("%lld %lld %lld\n",solve(r,r,k),solve(l-1,r,k),solve(l-1,l-1,k));
    LL ret=solve(r,r,k);
//    dbgln(ret);
    ret-=solve(l-1,r,k)*2;
//    dbg(l);dbg(r);dbg(k);
//    dbgln(ret);
    ret+=solve(l-1,l-1,k);
//    printf("%lld %lld %lld\n",solve(r,r,k),solve(l-1,r,k),solve(l-1,l-1,k));
//    printf("%lld  %lld\n",solve(r,r,k)-2*solve(l-1,r,k)+solve(l-1,l-1,k),ret);
    return ret;
}
int main() {
    int i,j,n,T;
    scanf("%d",&T);
    while (T--){
        LL l,r,k;
        scanf("%lld%lld%lld",&l,&r,&k);
        static int x=0;
        LL i,j;
//        FOR(i,0,10){
//            FOR(j,0,10){
////////                if (Solve(i,j,k)) printf("%lld %lld: %lld\n",i,j,Solve())
//////                if (solve(i,j,k)-solve(i-1,j,k)) printf("solve: %lld %lld : %lld\n",i,j,solve(i,j,k)-solve(i-1,j,k));
//////                printf("solve: %lld %lld : %lld\n",i,j,solve(i,j,k));
//            }
////            if (Solve(i,i,k)) printf("solve: %lld %lld\n",i,Solve(i,i,k));
//        }
        printf("Case #%d: %lld\n",++x,Solve(l,r,k));
    }
}
/*
*/
