// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
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
#include <functional>
#include <random>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP_(I,N) for (int I=0;I<N;I++)
#define rREP_(I,N) for (int I=N-1;I>=0;I--)
#define rep_(I,S,N) for (int I=S;I<N;I++)
#define rrep_(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR_(I,S,N) for (int I=S;I<=N;I++)
#define rFOR_(I,S,N) for (int I=N;I>=S;I--)

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
// const LL M=1e9+7;
const LL M=998244353;
// ll M=1;
const LL maxn=1e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    ll az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));


vector<int> edge[maxn];
// int dis(int x,int y) { // todo
//     static int dis[maxn];
//     memset(dis,0,sizeof(dis));
// }
int ask(int x,int y) {
    printf("? %d %d\n",x,y);
    fflush(stdout);
    int ret; scanf("%d",&ret);
    if (ret<0) exit(0);
    return ret;
}
// initialize - id
bool vis[maxn];
vector<int> fid;
void dfs(int x) {
    fid.push_back(x); // to check dis
    for (int v:edge[x]) if (!vis[v]) {
        vis[v]=1; dfs(v);
    }
}
int dis[maxn];
int Ans[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,x;
        fflush(stdout);
        scanf("%d",&n);
        if (n&1) x=n; else x=n-1;
        printf("+ %d\n",n+1);
        fflush(stdout); scanf("%*d");
        if (x>=2) {
            printf("+ %d\n",x);
            fflush(stdout); scanf("%*d");
        }
        FOR_(i,1,n) edge[i].clear();
        FOR_(i,1,n) vis[i]=0; fid.clear();
        FOR_(i,1,n) {
            edge[i].push_back(n+1-i);
            if (i<x) edge[i].push_back(x-i);
        }
        vis[n]=1; dfs(n);
        // for (int v:fid) printf("%d ",v); puts("<- v (pos)");
        int root=1,nxt=1,len=0;
        FOR_(i,1,n) if (i!=root) {
            int now=ask(root,i);
            if (now>=len) nxt=i,len=now;
        } root=nxt;
        dis[root]=0;
        FOR_(i,1,n) if (i!=root) dis[i]=ask(root,i);
        printf("!");
        FOR_(i,1,n) Ans[i]=fid[dis[i]];
        FOR_(i,1,n) printf(" %d",Ans[i]);
        reverse(fid.begin(),fid.end());
        FOR_(i,1,n) Ans[i]=fid[dis[i]];
        FOR_(i,1,n) printf(" %d",Ans[i]);
        puts("");
        int Ans=0;
        fflush(stdout); scanf("%d",&Ans);
        assert(Ans==1);
    }
}
/*
3
6
1 1
1 3 4 3 1
4 3 1 2 5


6
1 1
3
2
1
4
1
4
1
2
3
5


5
7
*/