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

struct node{
    LL x,y,c;
}A[maxn],pre,now;
int n;
vector<LL> vx,vy;
LL cntx[maxn],cnty[maxn];
LL basex[maxn],basey[maxn],all;
int main() {
    int i;
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%I64d%I64d%I64d",&A[i].x,&A[i].y,&A[i].c);
        vx.push_back(A[i].x);vy.push_back(A[i].y);
    }sort(vx.begin(),vx.end());
    vx.erase(unique(vx.begin(),vx.end()),vx.end());
    sort(vy.begin(),vy.end());
    vy.erase(unique(vy.begin(),vy.end()),vy.end());
    if (vx.size()*vy.size()!=n) return 0*puts("0");//not
    FOR(i,1,n){
        int idx=lower_bound(vx.begin(),vx.end(),A[i].x)-vx.begin();
        int idy=lower_bound(vy.begin(),vy.end(),A[i].y)-vy.begin();
        basex[idx]+=A[i].c;
        basey[idy]+=A[i].c;
        all+=A[i].c;
    }
    LL gx;gx=basex[0];
    REP(i,vx.size()) gx=gcd(gx,basex[i]);
    REP(i,vx.size()) basex[i]/=gx;
    LL gy;gy=basey[0];
    REP(i,vy.size()) gy=gcd(gy,basey[i]);
    REP(i,vy.size()) basey[i]/=gy;
    LL g=A[1].c;
    FOR(i,1,n) g=gcd(g,A[i].c);
//    REP(i,vx.size()) printf("%d ",basex[i]);puts(" <- basex");
//    REP(i,vy.size()) printf("%d ",basey[i]);puts(" <- basey");
//    puts("OK2");
    FOR(i,1,n){
        int idx=lower_bound(vx.begin(),vx.end(),A[i].x)-vx.begin();
        int idy=lower_bound(vy.begin(),vy.end(),A[i].y)-vy.begin();
        if (A[i].c!=basex[idx]*basey[idy]*g) return 0*puts("0");
    }LL ans=0;
    for (i=1;(LL)i*i<=g;i++) if (g%i==0){
        ans++;
        if (i!=g/i) ans++;
    }printf("%I64d\n",ans);
    return 0;
}
/*
2 2 3 3
+-++++
*/
