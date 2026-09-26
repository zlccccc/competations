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
const LL maxn=2e6+107;
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

int A[maxn],mask[maxn];
bool mark[maxn];
vector<int> f[maxn*2];
int sz[maxn][2]; // last,val; okay-ids
ar2 val[maxn][2];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,k;
        scanf("%d%d",&n,&k);
        REP_(i,n*2+2) f[i].clear();
        REP_(i,n) scanf("%d",&A[i]),A[i]^=1,mask[i]=0,mark[i]=0;
        rrep_(i,1,n) A[i]^=A[i-1];
        // REP_(i,n) printf("%d ",A[i]); puts("<- A");
        REP_(i,n+1) sz[i][0]=sz[i][1]=INF;
        sz[0][0]=0; // okay!
        REP_(i,gcd(n,k)) { // gcd(n,k)
            assert(!mark[i]);
            vector<int> cur;
            for (int o=i;!mark[o];o=(o+k)%n) cur.push_back(o),mark[o]=1;
            for (int use_0=0;use_0<=1;use_0++) { // use_cur[0]: use the first value
                int cnt=0,prev=use_0,p=0;
                for (int _=1;_<(int)cur.size();_++) {
                    int now=A[cur[_]]^prev;
                    if (now) {
                        f[i*2|use_0].push_back(cur[_]);
                        cnt++; prev=1;
                        if (cur[_]>=n-k) p++; // change 0-pos
                    } else prev=0;
                }
                if (use_0) {
                    f[i*2|use_0].push_back(cur[0]);
                    if (cur[0]==0) p++;
                    if (cur[0]>=n-k) p++; // p:0位置被修改了几次
                }
                if (prev&&cur[0]==0) p++; // from last position
                if ((prev^use_0)!=A[cur[0]]) { // prev:last-operation
                    if (cur[0]!=0) continue; // not right!
                }
                // puts("");
                // puts("solve current");
                // for (int v:cur) printf("%d ",v); puts("<- cur");
                // printf("p=%d; (from last)=%d; use_cur[0]=%d\n",p,prev,use_0);
                // for (int v:f[i*2|use_0]) printf("%d ",v); puts("<- v");
                // // cur: 修改了几次0,p=?
                p=p&1;
                for (int o=0;o<=1;o++) if (sz[i][o]!=INF) {
                    if (sz[i+1][o^p]>=sz[i][o]+(int)f[i*2|use_0].size()) {
                        sz[i+1][o^p]=sz[i][o]+(int)f[i*2|use_0].size();
                        val[i+1][o^p]={i*2|use_0,o}; // f
                        // printf("t=%d %d: %d %d\n",i+1,o^p,i*2|use_0,o);
                    }
                }
            }
        }
        // printf("sz = %d %d; A=%d\n",sz[gcd(n,k)][0],sz[gcd(n,k)][1],A[0]);
        if (sz[gcd(n,k)][A[0]]!=INF) {
            vector<int> ans;
            int cur=A[0];
            for (int t=gcd(n,k);t;t--) {
                // printf("t=%d; o=%d; f[v]; %d %d\n",t,o,val[t][cur][0],val[t][cur][1]);
                for (int v:f[val[t][cur][0]]) ans.push_back(v);
                cur=val[t][cur][1];
            }
            assert(ans.size()==sz[gcd(n,k)][A[0]]);
            printf("%d\n",(int)ans.size());
            for (int v:ans) printf("%d ",v); puts("");
        } // 0被用到的次数是0
        else puts("-1");
    }
}
/*
10
6 2
0 0 0 0 1 1
6 4
1 1 1 1 1 1
6 4
0 1 1 0 1 1
6 4
1 1 1 1 0 0
6 4
0 0 1 1 0 0
5 2
0 0 0 0 0
5 3
0 0 0 0 0
6 4
1 1 1 1 1 1
10 6
1 0 1 0 1 0 1 0 1 0
*/