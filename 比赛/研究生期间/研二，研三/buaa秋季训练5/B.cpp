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

typedef array<int,3> ar3;

vector<ar3> edge[maxn];
priority_queue<pair<ll,pii> > Q;
bool vis[maxn*4];
ll dis[maxn];
void update(int x,int l,int r,ll dist,int L,int R) {
    if (vis[x]) return;
    if (L==R) {
        vis[x]=1;
        // printf("dfs %d %d: dist=%lld\n",l,r,dist);
        dis[L]=dist;
        for (auto e:edge[L]) {
            // printf("push %d %lld %d %d\n",L,-e[0]-dis[L],e[1],e[2]);
            Q.push({-e[0]-dis[L],{e[1],e[2]}});
        }
        return;
    }
    int mid=(L+R)/2;
    if (l<=mid) update(x<<1,l,r,dist,L,mid);
    if (mid<r) update(x<<1|1,l,r,dist,mid+1,R);
    vis[x]=vis[x<<1]&vis[x<<1|1];
}
int main() {
    int n,m,i;
    scanf("%d%d",&n,&m);
    FOR(i,1,m) {
        int l,r,x,y;
        scanf("%d%d%d%d",&l,&r,&x,&y);
        edge[x].push_back({y,l,r});
    }

    Q.push({0,{1,1}});
    memset(dis,0xff,sizeof(dis));
    while (Q.size()) {
        auto e=Q.top(); Q.pop();
        update(1,e.second.first,e.second.second,-e.first,1,n);
    }
    FOR(i,1,n) printf("%lld\n",dis[i]);
}
/*
*/