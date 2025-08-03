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
const LL M=199999;
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


// MD读错题了
int u[maxn],v[maxn],w[maxn],L[maxn];
unsigned int SA, SB, SC; int n, m, q, LIM;
unsigned int rng61(){
    SA ^= SA << 16;
    SA ^= SA >> 5;
    SA ^= SA << 1;
    unsigned int t = SA;
    SA = SB;
    SB = SC;
    SC ^= t ^ SA;
    return SC;
}

void gen(){
    scanf("%d%d%d%u%u%u%d", &n, &m, &q, &SA, &SB, &SC, &LIM);
    for(int i = 1; i <= m; i++){
        u[i] = rng61() % n + 1;
        v[i] = rng61() % n + 1;
        w[i] = rng61() % LIM;
        // printf("edge %d %d :%d\n",u[i],v[i],w[i]);
    }
    for(int i = 1; i <= q; i++){
        L[i] = rng61() % LIM;
    }
}

vector<pair<int,int> > edge[maxn];
priority_queue<pair<int,int> > Q;
int dis[maxn],mask[maxn];//dis:more; mask:id
vector<int> fin;//fin
int fa[maxn],sz[maxn];
int getfa(int x) {
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
};
int id[maxn];
vector<pair<int,ll> > P;
int main() {
    gen();
    int i;
    FOR(i,1,m) id[i]=i;
    FOR(i,1,n) fa[i]=i,sz[i]=1;
    sort(id+1,id+1+m,[](int x,int y) {
        return w[x]<w[y];
    });
    P.push_back(make_pair(0,0ll));
    P.push_back(make_pair(LIM,0ll));
    FOR(i,1,m) {
        int _id=id[i];
        // printf("_id=%d\n",_id);
        int x=getfa(u[_id]),y=getfa(v[_id]);
        if (x==y) continue;
        else {
            P.push_back(make_pair(w[_id],(ll)sz[x]*sz[y]));
            fa[x]=y; sz[y]+=sz[x];
        }
    } sort(P.begin(),P.end());
    ll out=0;
    rep(i,1,(int)P.size()) P[i].second+=P[i-1].second;
    // for (auto now:P) printf("%d %lld\n",now.first,now.second);
    FOR(i,1,q) {
        auto it=upper_bound(P.begin(),P.end(),make_pair(L[i],INFF));
        it--; out^=it->second;
        // printf("%lld ",it->second);
    }
    printf("%lld\n",out);
}
/*
20 20 5 480944053 701657892 339027200 2
5 7 5 480944053 701657892 339027200 1
*/