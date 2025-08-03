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

bool Q;
struct Line {
    mutable LL a,b,k;
    bool operator<(const Line &o)const {
        return Q?k<o.k:a<o.a;
    }
};
struct convexHull:public multiset<Line> {
    LL div(LL a,LL b) {
        return a/b-((a^b)<0&&a%b);
    }
    bool getK(iterator x,iterator y) {
        if (y==end()) {x->k=INFF; return 0;}
        if (x->a==y->a) x->k=x->b>y->b?INFF:-INFF;
        else x->k=div(y->b-x->b,x->a-y->a);
        return x->k>=y->k;
    }
    void insPos(LL a,LL b) {
        auto z=insert({a,b,0}); auto y=z++,x=y;
        while (getK(y,z)) z=erase(z);
        if (y!=begin()&&getK(--x,y)) getK(x,erase(y));
        while ((y=x)!=begin()&&(--x)->k>=y->k)
            getK(x,erase(y));
    }
    LL query(LL x) {
        assert(size());
        Q=1; auto now=lower_bound({0,0,x}); Q=0;
        return now->a*x+now->b;
    }
}CH;
typedef pair<LL,int> pii;
vector<pii> queries;
LL F[maxn],now;
LL A[maxn],B[maxn];
LL ans[maxn];
void solve(){
    int i,n,m;
    scanf("%d%d",&n,&m);
    FOR(i,1,n-1) scanf("%lld",&A[i]);A[n]=0;
    FOR(i,1,n-2) scanf("%lld",&B[i]);B[n]=B[n-1]=0;
    rFOR(i,1,n-3) B[i]+=B[i+1];F[0]=INFF;
    FOR(i,1,n-1) F[i]=A[n-i]+B[n-i];
//    FOR(i,2,n-1) F[i]=min(F[i],F[i-1]);
    CH.clear();
    FOR(i,1,n-1) CH.insPos(-i,-F[i]);
    queries.clear();
    FOR(i,1,m){
        LL d;
        scanf("%lld",&d);
        printf("%lld%c",-CH.query(d)," \n"[i==m]);
//        queries.push_back(make_pair(d,i));
    }
//    sort(queries.begin(),queries.end());
    now=n-1;
//    FOR(i,1,n-1) printf("%lld ",F[i]);puts(" <- F");
//    for (auto q:queries){
//        while (now>1&&F[now-1]<=q.first+F[now]) now--;
//        printf("%lld : %lld\n",q.first,now);
//        ans[q.second]=F[now]+now*q.first;
//    }FOR(i,1,m) printf("%lld%c",ans[i]," \n"[i==m]);
}
int main() {
    int i,j,k;
    int T;
    scanf("%d",&T);
    while (T--) solve();
    return 0;
}
/*

*/
