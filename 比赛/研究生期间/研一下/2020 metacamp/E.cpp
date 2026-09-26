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
const LL maxn=5e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

struct V{
    int mx1=0,mx2=0,mx3=0;
    void insert(int x) {
        if (x>mx1) swap(x,mx1);
        if (x>mx2) swap(x,mx2);
        if (x>mx3) swap(x,mx3);
    }
}A[maxn];//len1,len2,len3
vector<int> edge[maxn];
int Down[maxn];
void dfs1(int u,int fa){//需要好多次(findmaxlen) 
    int i; A[u]=V(); Down[u]=0;
    REP(i,(int)edge[u].size()) {
        int v=edge[u][i];
        if (v==fa) continue;
        dfs1(v,u);
        A[u].insert(A[v].mx1+1);
    }
    // printf("first %d: %d %d %d; top=%d\n",u,A[u].mx1,A[u].mx2,A[u].mx3);
}
void dfs2(int u,int fa) {
    int i; int nowmax=0; A[u].insert(Down[u]);
    REP(i,(int)edge[u].size()) {
        int v=edge[u][i];//left
        if (v==fa) continue;
        Down[v]=max(Down[v],nowmax+1);
        Down[v]=max(Down[v],Down[u]+1);
        nowmax=max(nowmax,A[v].mx1+1);
    }
    nowmax=0;
    rREP(i,(int)edge[u].size()) {
        int v=edge[u][i];//left
        if (v==fa) continue;
        Down[v]=max(Down[v],nowmax+1);
        nowmax=max(nowmax,A[v].mx1+1);
        dfs2(v,u);
    }
    // printf("id=%d: %d %d %d; top=%d\n",u,A[u].mx1,A[u].mx2,A[u].mx3,Down[u]);
}
int main() {
    int N,i; bool ok=0;
    while (~scanf("%d",&N)){
        if (ok) puts(""); ok=1;
        int ans=0,_;
        FOR(_,1,N) {
            int n; scanf("%d",&n);
            FOR(i,1,n) edge[i].clear();
            FOR(i,2,n) {
                int f; scanf("%d",&f);
                edge[f].push_back(i);
                edge[i].push_back(f);
            }
            int MAX=0;
            dfs1(1,0); dfs2(1,0);
            FOR(i,1,n) MAX=max(MAX,A[i].mx1+A[i].mx2+A[i].mx3);
            ans+=MAX*2;
        } printf("%d",ans);
    }
}
/*
4 5 2
1 2 3 4
3 4 2 1 3
2 3
1 1 1
1
1
1
2 2 1
1 2
2 1
2
3 2 1
1 2 3
2 3
1
2 2 1
1 2
1 2
1
*/