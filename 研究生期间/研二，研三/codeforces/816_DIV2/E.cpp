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
const LL maxn=1e5+107;
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

int n,m,k;
ll dis[maxn];
bool vis[maxn];
vector<pii> edge[maxn];
void mindis(int n) {
    int i;
    priority_queue<pair<ll,int> > Q;
    FOR(i,1,n) if (dis[i]!=INFF) Q.push(make_pair(-dis[i],i));
    FOR(i,1,n) vis[i]=0;
    while (Q.size()) {
        int x=Q.top().second; Q.pop();
        if (vis[x]) continue; vis[x]=1;
        for (auto p:edge[x]) {
            if (dis[p.first]>p.second+dis[x]) {
                dis[p.first]=p.second+dis[x];
                Q.push(make_pair(-dis[p.first],p.first));
            }
        }
    }
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
}S;
void fly(int n) {
    int i;
    S.clear();
    FOR(i,1,n) S.insPos(2*i,-dis[i]-(ll)i*i);
    FOR(i,1,n) dis[i]=-S.query(i)+(ll)i*i;
}
int main() {
    int n,m,k,i;
    memset(dis,0x3f,sizeof(dis));
    scanf("%d%d%d",&n,&m,&k);
    FOR(i,1,m) {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    memset(dis,0x3f,sizeof(dis));
    dis[1]=0;
    mindis(n);
    while (k--) {
        fly(n);
        mindis(n);
    }
    // printf("%lld\n",dis[n]);
    FOR(i,1,n) printf("%lld ",dis[i]);
}
/* 
1 4
*/