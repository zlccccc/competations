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
}cx,c_x,cy,c_y;

int solve(){
    int n,i;
    scanf("%d",&n);
    int ans=-1;
    LL wsum=0,wxsum=0,wysum=0;
    bool havepos=0;
    FOR(i,1,n){
        LL xl,xr,yl,yr,x,y,w;
        scanf("%lld%lld%lld%lld%lld",&xl,&xr,&yl,&yr,&w);
        if (ans!=-1) continue;
        xl*=2;xr*=2;yl*=2;yr*=2;
        x=(xl+xr)/2;y=(yl+yr)/2;
        if (!w&&!havepos) continue; havepos=1;
        wsum+=w; wxsum+=x*w; wysum+=y*w;
        if (cx.size()&&cx.query(wsum)>=wxsum) ans=i;
        cx.insPos(xl,wxsum-xl*wsum);
        if (c_x.size()&&-c_x.query(wsum)<=wxsum) ans=i;
        c_x.insPos(-xr,-(wxsum-xr*wsum));

        if (cy.size()&&cy.query(wsum)>=wysum) ans=i;
        cy.insPos(yl,wysum-yl*wsum);
        if (c_y.size()&&-c_y.query(wsum)<=wysum) ans=i;
        c_y.insPos(-yr,-(wysum-yr*wsum));
    }printf("%d\n",ans);
    return 0;
}
int main() {
    int T=1;
//    scanf("%d",&T);
    while (T--) solve();
}
/*
4
1 4 1 4 1
2 5 2 5 1
4 7 4 7 2
2 5 1 5 1
*/
