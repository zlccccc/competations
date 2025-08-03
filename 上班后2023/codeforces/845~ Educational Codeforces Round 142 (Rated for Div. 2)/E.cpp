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
// const LL M=585698298;
// const LL M=998244353;
const LL M=1e9+7;
// ll M=1;
const LL maxn=1.2e6+107;
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

int Div[107],Cnt[107];
int Last[107];
ll Ans[maxn],Val[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        int n,m1,m2,D=0;
        scanf("%d%d%d",&n,&m1,&m2);
        memset(Div,0,sizeof(Div));
        memset(Cnt,0,sizeof(Cnt));
        for (int i=2;i*i<=m1||i*i<=m2;i++) {
            if (m1%i==0||m2%i==0) {
                Div[++D]=i;
                while (m1%i==0) m1/=i,Cnt[D]++;
                while (m2%i==0) m2/=i,Cnt[D]++;
            }
        }
        if (m1>m2) swap(m1,m2);
        if (m1!=1) Div[++D]=m1,Cnt[D]=1;
        if (m1==m2&&m1!=1) Cnt[D]++,m2=1;
        if (m2!=1) Div[++D]=m2,Cnt[D]=1;
        int i,k;
        // FOR(i,1,D) printf("%d(%d) ",Div[i],Cnt[i]); puts("<- divisor");
        // 筛法: f[k*i]位置
        // x*y=divisor;  ceil[n/minpos]<y<=n;
        memset(Ans,-1,sizeof(Ans));
        Last[1]=1; Val[0]=Ans[0]=1;
        FOR(k,1,D) {
            Last[k+1]=Last[k]*(Cnt[k]+1);
            rep(i,Last[k],Last[k+1]) {
                Val[i]=Val[i-Last[k]]*Div[k];
                if (Val[i]<=n) Ans[i]=Val[i];
            }
        }
        FOR(k,1,D) {
            REP(i,Last[D+1]) {
                if (Val[i]%Div[k]==0) max_(Ans[i],Ans[i-Last[k]]);
            }
        }
        // REP(i,Last[D+1]) printf("%lld ",Val[i]); puts("<- val");
        // REP(i,Last[D+1]) printf("%lld ",Ans[i]); puts("<- ans");
        int ans0=0,ans1=0;
        REP(i,Last[D+1]) if (Ans[i]!=-1&&Val[i]/Ans[i]<=n) ans0++,ans1^=Val[i]/Ans[i];
        printf("%d %d\n",ans0,ans1);
    }
}
/*
*/