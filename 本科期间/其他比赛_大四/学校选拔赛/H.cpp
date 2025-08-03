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

vector<int> edge[maxn];
int dfn[maxn],rid[maxn],id[maxn],tot;
pii P[maxn];
int A[maxn];
void update(int x,int val,int l,int r) {
    if (l==r) {
        P[x]=make_pair(A[id[l]],id[l]);
        // printf("update:id=%d\n",id[l]);
        return;
    }
    int mid=(l+r)/2;
    if (val<=mid) update(x<<1,val,l,mid);
    if (mid<val) update(x<<1|1,val,mid+1,r);
    P[x]=min(P[x<<1],P[x<<1|1]);
    // printf("%d-%d: %d %d\n",l,r,P[x].first,P[x].second);
}
pii query(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) return P[x];
    int mid=(L+R)/2; pii ret=make_pair(INF+1,0);
    if (l<=mid) ret=min(ret,query(x<<1,l,r,L,mid));
    if (mid<r) ret=min(ret,query(x<<1|1,l,r,mid+1,R));
    return ret;
}
void dfs(int x,int fa) {
    dfn[x]=++tot; id[tot]=x;
    for (int v:edge[x]) if (v!=fa){
        dfs(v,x);
    } rid[x]=tot;
}
int main() {
    int n,m,i;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    A[0]=INF;
    FOR(i,1,n) if (A[i]==0) A[i]=INF;
    FOR(i,1,n-1) {
        int u,v; scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    } dfs(1,0);
    FOR(i,1,n) update(1,i,1,n);
    scanf("%d",&m);
    FOR(i,1,m) {
        int a,c; scanf("%d%d",&a,&c);
        pii now=query(1,dfn[a],rid[a],1,n);
        // printf("val? l,r=%d %d %d %d\n",dfn[a],rid[a],now.first,now.second);
        int id=now.second;
        if (A[id]<1e6) printf("%d\n",id);
        else puts("-1");
        A[id]-=c; if (A[id]<=0) A[id]=INF;
        update(1,dfn[id],1,n);
    }
}
/*
*/