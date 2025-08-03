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
// const LL M=998244353;
// ll M=1;
const LL maxn=107;
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

int n,ans;
int nxt[87][27];
int val[87];
int ask(int len) {
    int nxtpos=0;
    int C=0,t;
    while (nxtpos!=n+1) {
        REP(t,len) nxtpos=nxt[nxtpos][val[t]];
        if (nxtpos!=n+1) C++;
    } if (C<=1) return 0;
    ans=max(ans,C*len);
    // REP(t,len) printf("%d ",val[t]); printf(" C=%d ",C); puts("<-t");
    return C;
}
char str[maxn];
void dfs(int i,int pos,int r) { // brute-force for sequence
    if (pos==r) return;
    val[i]=str[pos]-'a';
    ask(i+1);
    dfs(i+1,pos+1,r);
    dfs(i,pos+1,r);
}

int p[maxn];
int main() {
    int i,k;
    scanf("%s",str);
    n=strlen(str);
    REP(k,26) p[k]=nxt[n+1][k]=nxt[n][k]=n+1;
    rREP(i,n) {
        p[str[i]-'a']=i+1;
        REP(k,26) nxt[i][k]=p[k];
    }
    {
        vector<vector<int>> dp(n+1,vector<int>(n+1,0));
        int a,i,j;
        rep(a,1,n) { // TT,TTT
            rep(i,0,a+1) rep(j,a,n+1) {
                dp[i][j]=0;
                if (i&&j!=a&&str[i-1]==str[j-1]) max_(dp[i][j],dp[i-1][j-1]+2);
                if (i) max_(dp[i][j],dp[i-1][j]);
                if (j!=a) max_(dp[i][j],dp[i][j-1]);
            }
            max_(ans,dp[a][n]);
            // printf("a=%d: dp[a][n]=%d\n",a,dp[a][n]);
        }
    }
    {
        vector<vector<vector<int>>> dp(n+1,vector<vector<int>>(n+1,vector<int>(n+1,0)));
        int a,b,i,j,k;
        rep(a,1,n) rep(b,a+1,n) { // TT,TTT
            rep(i,0,a+1) rep(j,a,b+1) rep(k,b,n+1) {
                dp[i][j][k]=0;
                if (i&&j!=a&&k!=b&&str[i-1]==str[j-1]&&str[j-1]==str[k-1])
                    max_(dp[i][j][k],dp[i-1][j-1][k-1]+3);
                if (i) max_(dp[i][j][k],dp[i-1][j][k]);
                if (j!=a) max_(dp[i][j][k],dp[i][j-1][k]);
                if (k!=b) max_(dp[i][j][k],dp[i][j][k-1]);
                cnt++;
            }
            max_(ans,dp[a][b][n]);
        }
    }
    // printf("ans=%d\n",ans);
    for (int i=0;i<n;i=min(n,i+16)) dfs(0,i,min(n,i+16));
    dfs(0,max(0,n-16),n);
    printf("%d\n",ans);
}
/*
*/