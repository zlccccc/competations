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
#include <unordered_set>
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
const LL maxn=1e6+107;
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
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
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

// 是否可以从x出,从x回
// 是的话down=0,否则down=id
vector<int> edge[maxn];
vector<int> newe[maxn];
void addedge(int x,int y) {
    // printf("%d - %d\n",x,y);
    newe[x].push_back(y);
    newe[y].push_back(x);
}
bool vis[maxn];
void output_dfs(int x) {
    if (vis[x]) return; vis[x]=1;
    printf("%d ",x);
    for (int v:newe[x]) output_dfs(v);
}
vector<int> dfs(int x,int fa) {
    int s=0,t=0;
    vector<int> tmp;
    for (int v:edge[x]) {
        if (v==fa) continue;
        vector<int> val=dfs(v,x);
        // printf("dfs %d -> %d",x,v); for (int v:val) printf("(%d) ",v); puts("");
        if (!val.size()) tmp.push_back(v);
        else {if (!s) s=v; t=v;}
        for (int id:val) addedge(x,id);
    }
    if (s&&(newe[x].size()==0)) addedge(x,s);
    for (int v:tmp) {
        if (s) addedge(s,v); s=v;
        if (s&&(newe[x].size()==0)) addedge(x,s);
    }

    if (newe[x].size()>=3) {puts("No"); exit(0);}
    if (newe[x].size()==2) {
        addedge(s,t);
        if (fa) {puts("No"); exit(0);}
        puts("Yes");
        output_dfs(x);
        // puts("output");
        // printf("x=%d\n",x);
        exit(0);
    }
    // if (t) return {t};// s==t
    if (s) return {s};
    return {};
}
int main() {
    int n;
    scanf("%d",&n);
    FOR_(i,1,n-1) {
        int x,y;
        scanf("%d%d",&x,&y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    int root=1;
    FOR_(i,1,n) if (edge[i].size()!=1) root=i;
    vector<int> ret=dfs(root,0);
    // for (int v:ret) printf("v=%d ",v);
    if (ret.size()==2) addedge(ret[0],ret[1]);
    else if (ret.size()==1) addedge(root,ret[0]);
    puts("Yes");
    output_dfs(1);
}
/*
16
1 2
2 3
1 9
1 10
1 11
2 8
2 4
3 7
3 5
3 6
10 12
6 13
3 14
12 15
15 16

9
1 2
2 3
2 4
2 5
3 6
3 7
3 8
8 9
*/