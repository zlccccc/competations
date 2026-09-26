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

int n,k;
int A[207],id[207];
int s[207];
int f[207][207]; // sum=n^2; *n (one-check)
bool mark[207];
vector<int> ans[207];
int norm(int x,int y) {
    return (x%y+y)%y;
}
int main() {
    int n,k;
    scanf("%d%d",&n,&k);
    FOR_(i,1,n) scanf("%d",&A[i]);
    FOR_(i,1,k) scanf("%d",&s[i]),id[i]=i;
    sort(id+1,id+1+k,[&](int i,int j){return s[i]>s[j];});
    // FOR_(i,1,k) printf("%d ",id[i]); puts("<- id");
    // REP_(_,10) {
        // random_shuffle(A+1,A+1+n);
        memset(mark,0,sizeof(mark));
        FOR_(i,2,k) {
            // need!
            int id=::id[i];
            REP_(x,s[id]+1) REP_(y,s[id]) f[x][y]=-1;
            f[0][0]=0;
            FOR_(j,1,n) if (!mark[j]) {
                rREP_(x,s[id]) rREP_(y,s[id]) {
                    if (f[x][y]!=-1&&f[x+1][norm(y+A[j],s[id])]==-1)
                        f[x+1][norm(y+A[j],s[id])]=j;
                }
            }
            if (f[s[id]][0]) {
                for (int i=s[id],k=0;i;k=norm(k-A[f[i][k]],s[id]),i--) {
                    // printf("i=%d; k=%d; f[i][k]=%d, A=%d\n",i,k,f[i][k],A[f[i][k]]);
                    ans[id].push_back(A[f[i][k]]),mark[f[i][k]]=1;
                }
            } else assert(0);
            // printf("solve id=%d\n",id);
            // for (int v:ans[id]) printf("%d ",v); puts("<- v");
        }
        int all=0;
        FOR_(j,1,n) if (!mark[j]) all=(all+A[j])%s[id[1]],ans[id[1]].push_back(A[j]);
        all=(s[id[1]]-all)%s[id[1]]+s[id[1]];
        ans[id[1]].push_back(all);
        printf("%d\n",all);
        FOR_(i,1,k) {for (int v:ans[i]) printf("%d ",v); puts("");}
    // }
}