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

int n;
ll sum[maxn];
void update(int x,int pos,int val,int L,int R) {
    sum[x]+=val;
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,val,L,mid);
    if (mid<pos) update(x<<1|1,pos,val,mid+1,R);
}
int query(int x,ll val,int L,int R) {
    // printf("query %d %lld %d %d; sum=%lld\n",x,val,L,R,sum[x]);
    if (L==R) return L;
    int mid=(L+R)/2;
    if (sum[x<<1]<=val) return query(x<<1|1,val-sum[x<<1],mid+1,R);
    return query(x<<1,val,L,mid);
}
vector<pair<int,pii> > edge[maxn];
ll A[maxn];
int ans[maxn];
void dfs(int x,int fa,int depth) {
    // printf("dfs %d %d  %lld\n",x,fa,A[x]);
    ans[x]=min(depth,query(1,A[x],1,n));
    // ans[x]=query(1,A[x],1,n);
    for (auto p:edge[x]) {
        int v=p.first;
        if (v==fa) continue;
        int a=p.second.first,b=p.second.second;
        A[v]=a+A[x];
        update(1,depth,b,1,n);
        dfs(v,x,depth+1);
        update(1,depth,-b,1,n);
    }
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i;
        scanf("%d",&n);
        FOR(i,1,n) edge[i].clear();
        FOR(i,2,n) {
            int u=i,v,a,b;
            scanf("%d%d%d",&v,&a,&b);
            edge[u].push_back({v,{a,b}});
            edge[v].push_back({u,{a,b}});
        }
        dfs(1,0,1);
        FOR(i,2,n) printf("%d ",ans[i]-1); puts("");
    }
}