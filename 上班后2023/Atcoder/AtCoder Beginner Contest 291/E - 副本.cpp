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
typedef array<int,2> ar2;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

vector<int> edge[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,A,B,C;
        scanf("%d%d%d%d",&n,&A,&B,&C);
        FOR_(i,1,n) edge[i].clear();
        FOR_(i,2,n) {int p; scanf("%d",&p); edge[p].push_back(i);}
        vector<int> sz(n+1);
        //dp[root][cntB][cntC][isroot]
        vector<vector<vector<ar2>>> dp(n+1);
        function<void(int)> dfs=[&](int x) { // o: choose
            if (edge[x].size()==0) {
                dp[x]=vector<vector<ar2>>(2,vector<ar2>(2,{0,0}));
                dp[x][0][0][0]=dp[x][0][1][1]=1;
            } else {
                dp[x]=vector<vector<ar2>>(2,vector<ar2>(1,{0,0}));
                dp[x][0][0][0]=dp[x][1][0][0]=1;
            }
            for (int v:edge[x]) {
                dfs(v);
                vector<vector<ar2>> nxt(dp[x].size()+dp[v].size()-1,
                                        vector<ar2>(dp[x][0].size()+dp[v][0].size()-1,{0,0}));
                REP_(i_a,(int)dp[x].size()) REP_(i_b,(int)dp[x][0].size()) {
                    REP_(j_a,(int)dp[v].size()) REP_(j_b,(int)dp[x][1].size()) {
                        add_(nxt[i_a+j_a][i_b+j_b][0],(ll)dp[x][i_a][i_b][0]*(dp[v][j_a][j_b][0]+dp[v][j_a][j_b][1])%M);
                        add_(nxt[i_a+j_a][i_b+j_b][1],(ll)dp[x][i_a][i_b][1]*dp[v][j_a][j_b][0]%M);
                    }
                }
                vector<vector<ar2>>().swap(dp[v]);
                // while (nxt.size()&&nxt.back()==ar2{0,0}) nxt.pop_back();
                dp[x].swap(nxt);
            }
            // printf("dfs %d\n",x);
            // for (auto v:dp[x]) printf("(%d,%d) ",v[0],v[1]); puts("<-");
        };
        dfs(1);
        // root is X: 
        if (C&1) puts("No");
        else if (dp[1][C/2][B-C/2][0]) puts("Yes");
        else if (dp[1][C/2][B-C/2+1][1]) puts("Yes");
    }
}
/*
*/