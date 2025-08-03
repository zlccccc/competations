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

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=2e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

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
}SET;
vector<pair<int,ll> > POP[maxn];
int S[maxn],A[maxn],top;
ll ans[maxn];
int main() {
    int n,i;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n+1) {
        while (top&&A[S[top]]>=A[i]) {
            POP[i].push_back(make_pair(A[S[top]],-(ll)A[S[top]]*(S[top-1])));
            // printf("%d : pop %d %d\n",i,S[top],A[S[top]]);
            top--;
        } S[++top]=i;
    }
    rFOR(i,1,n+1) {
        if (i<=n) ans[i]=SET.query(i);
        for (auto now:POP[i])
            SET.insPos(now.first,now.second);
        // printf("%lld ",ans[i]);
    }
    FOR(i,2,n) ans[i]=max(ans[i],ans[i-1]);
    FOR(i,1,n) printf("%lld\n",ans[i]);
}
/*
5
1 7 2 3 9
*/