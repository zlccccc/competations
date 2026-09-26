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
const LL maxn=2e6+7;
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

LL F[107];int n;
int A[107],B[107];
int mark[107];
bool okay;
void dfs(int id){
    if (!okay) return;
    if (F[id]<0){
        if (F[id]<-INFF/10) okay=0;
        if (mark[id]==n) okay=0;
        LL t=F[id]; F[id]=0;
        F[A[id]]+=t; F[B[id]]+=t;
        mark[id]++;
        dfs(A[id]); dfs(B[id]);
    }
}
int G[107];
void solve(){
    static int x=0;
    int i;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d%d",&A[i],&B[i]);
    FOR(i,1,n) scanf("%d",&G[i]);
    LL l=0,r=INFF;
    while (l+1<r){
        LL mid=(l+r)/2;
        FOR(i,1,n) F[i]=G[i],mark[i]=0;
        F[1]-=mid;
        okay=1;dfs(1);
        if (okay) l=mid;
        else r=mid;
    }printf("Case #%d: %lld\n",++x,l);
}
int main() {
    int T;
    scanf("%d",&T);
    while (T--) solve();
    return 0;
}
/*
*/
