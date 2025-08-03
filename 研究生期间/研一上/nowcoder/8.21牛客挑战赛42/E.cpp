
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
const LL M=1e9+7;
const LL maxn=1e6+107;
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

/* 维护上半凸壳 */
// 最大值,query的k要求>0
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
}S[maxn];
int n;
inline int lowbit(int x) {return x&-x;}
//h[i]^2+h[j]^2-2h[i]h[j]+cost[k-1]-cost[i]
void update(int x,ll l,ll r) {
    for (;x<=n;x+=lowbit(x)) {
        S[x].insPos(2*l,-r);//2xy-val
    }
}
ll query(int x,ll y,ll t) {
    ll ret=INFF;
    for (;x;x-=lowbit(x)) {
        if (S[x].size()) {
            min_(ret,t-S[x].query(y));
        }
    } return ret;
}
ll h[maxn],cost[maxn],now[maxn];//cost
ll A[maxn];//A
int main() {
    int m,i;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%lld",&h[i]);
    FOR(i,1,n) scanf("%lld",&cost[i]),cost[i]+=cost[i-1];
    FOR(i,1,n) {
        if (i!=1) {
            now[i]=query(i-1,h[i],cost[i-1]+h[i]*h[i]);
        } update(i,h[i],now[i]-cost[i]+h[i]*h[i]);
    } ll lastans=0;
    FOR(i,1,m) {
        ll x,y; scanf("%lld%lld",&x,&y);
        x=((x^lastans)%n+n)%n+1;
        if (x==1) lastans=0;
        else lastans=query(x-1,y,cost[x-1]+y*y);
        printf("%lld\n",lastans);
    }
}
/*
6 1
1 0 0 1 1 1

6 2
1 0 0 1 1 1
*/