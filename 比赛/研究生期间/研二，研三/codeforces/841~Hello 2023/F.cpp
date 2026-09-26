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
const LL maxn=2e5+107;
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

vector<int> e[maxn];
vector<vector<pii>> sub[maxn];
// pii sub[maxn][32]; // value
int sz[maxn],fa[maxn];
int A[maxn];
int main() {
    int T,_; T=1;
    // scanf("%d",&T);
    FOR(_,1,T){
        int n,k;
        scanf("%d",&n);
        int i;
        FOR(i,1,n) scanf("%d",&A[i]);
        FOR(i,1,n) e[i].clear();
        FOR(i,2,n) scanf("%d",&fa[i]),e[fa[i]].push_back(i);
        FOR(i,1,n) sz[i]=1;
        rFOR(i,2,n) sz[fa[i]]+=sz[i];
        function<void(int)> dfs=[&](int x) {
            int a,b;
            vector<pii> s(32,{-1,0});
            sub[x].push_back(s);
            REP(a,32) sub[x][0][a]={-1,0};
            sub[x][0][A[x]]={0,0};
            if (e[x].size()) {
                for (int v:e[x]) {
                    vector<pii> nxt(32,{-1,0});
                    dfs(v);
                    // v0,a0,v1,a1,v2,a2,v3,a3...
                    REP(a,32) REP(b,32) {
                        if (sub[v][sub[v].size()-1][a^b].first!=-1&&
                            sub[x][sub[x].size()-1][b].first!=-1) {
                            nxt[a]={a^b,0};
                            break;
                        }
                    }
                    sub[x].push_back(nxt); // self:zero-time
                }
            }
            if (!(sz[x]&1)) sub[x][sub[x].size()-1][0]={0,2};
        };
        dfs(1);
        if (sub[1][sub[1].size()-1][0].first==-1) {puts("-1"); continue;}
        vector<int> ans;
        function<void(int,int)> dfs2=[&](int x,int p) {
            // printf("dfs2 %d %d  %d,%d\n",x,p,sub[x][sub[x].size()-1][p].first,sub[x][sub[x].size()-1][p].second);
            if (sub[x][sub[x].size()-1][p].second) {
                ans.push_back(x);
                ans.push_back(x);
                return;
            }
            int subp=p; int i;
            rREP(i,e[x].size()) {
                int v=e[x][i];
                // printf("i=%d; sub.size=%d fir=%d  sz=%d\n",i,sub[x].size(),sub[x][i+1][subp].first,sub[x][i+1].size());
                dfs2(v,sub[x][i+1][subp].first);
                subp^=sub[x][i+1][subp].first;
            }
        };
        dfs2(1,0);
        // FOR(i,1,n) {
        //     int a;
        //     REP(a,32) if (sub[i][a].first!=-1) {
        //         printf("%d %d: %d %d\n",i,a,sub[i][a].first,sub[i][a].second);
        //     }
        // }
        if (sub[1][sub[1].size()-1][0].second!=2) ans.push_back(1);
        printf("%d\n",ans.size());
        for (int v:ans) printf("%d ",v); puts("");
    }
}
/*
*/