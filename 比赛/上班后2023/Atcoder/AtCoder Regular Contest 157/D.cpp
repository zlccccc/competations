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
const LL maxn=4e6+107;
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

char s[2007][2007];
int Cnt[2007][2007];
int Cx[2007],Cy[2007];
int Cntx[maxn],Cnty[maxn],px[maxn],py[maxn];
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    FOR_(i,1,n) scanf("%s",s[i]+1);
    int CNT=0;
    FOR_(i,1,n) FOR_(j,1,m) {
        if (s[i][j]=='Y') Cnt[i][j]=1,CNT++,Cx[i]++,Cy[j]++;
        Cnt[i][j]+=Cnt[i-1][j]+Cnt[i][j-1]-Cnt[i-1][j-1];
    }
    FOR_(i,1,n) Cx[i]+=Cx[i-1],Cntx[Cx[i]]++,px[Cx[i]]=i;
    FOR_(i,1,m) Cy[i]+=Cy[i-1],Cnty[Cy[i]]++,py[Cy[i]]=i;
    // FOR_(i,1,CNT) printf("%d ",Cntx[i]); puts("<- x");
    // FOR_(i,1,CNT) printf("%d ",Cnty[i]); puts("<- y");
    int ans=0;
    // if (CNT==2) ans=powMM(2,n+m-2);
    FOR_(h,1,CNT/2) {
        int w=CNT/2/h;
        if (h*w*2!=CNT) continue;
        int now=1;
        FOR_(i,1,h-1) mul_(now,Cntx[i*w*2]);
        FOR_(i,1,w-1) mul_(now,Cnty[i*h*2]);
        if (!now) continue;
        FOR_(i,1,h) FOR_(j,1,w) {
            int lx=px[(i-1)*w*2],ly=py[(j-1)*h*2],rx=px[i*w*2],ry=py[j*h*2];
            if (Cnt[rx][ry]-Cnt[lx][ry]-Cnt[rx][ly]+Cnt[lx][ly]!=2)
                now=0;
            if (!now) break;
        }
        add_(ans,now);
        // printf("h,w=%d,%d; now=%d\n",h,w,now);
    }
    printf("%d\n",ans); 
}
/*
2 2
YY
YY
*/