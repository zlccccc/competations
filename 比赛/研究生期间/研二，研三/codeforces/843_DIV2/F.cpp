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
// const LL M=998244353;
// const LL M=998244353;
ll M=1;
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

int f[maxn],f2[maxn],f4[maxn]; // f:block for size=k; g:4 times
vector<int> minsize;
void solve(int op) {
    int n;
    scanf("%d",&n);
    int l=lower_bound(minsize.begin(),minsize.end(),n)-minsize.begin();
    if (op==1) {
        int i,j;
        int x=l/2,y=l-x,tot=x*y-n;
        printf("%d %d\n",x,y);
        FOR(i,1,x) {
            FOR(j,1,y) {
                if (tot) printf("."),tot--;
                else printf("#");
            }
            puts("");
        }
        return;
    }
    // printf("l=%d\n",l);
    ll ans=0;
    for (int x=l/2;x*(l-x)>=n&&x>=1;x--) {
        int y=l-x,div=x*y-n;
        // printf("x,y=%d %d div=%d; f4[div]=%d; f2[div]=%d; f[div]=%d\n",x,y,div,f4[div],f2[div/2],f[div/4]);
        // printf("x=%d; y=%d; div=%d\n",x,y,div);
        add_(ans,f4[div]);
        if (x!=y) add_(ans,f4[div]); // rotate
        //     if (div%2==0) add_(ans,M-f2[div/2]); // calculated 2 times
        // } else if (x==y&&div%4==0) add_(ans,M-f[div/4]); // one
    }
    printf("%d %lld\n",l*2,ans);
}
int _f[1007][1007]; // length,minlength
void init() {
    const int MAX=1000;
    int i;
    minsize.push_back(0); // 0
    minsize.push_back(0); // 1
    FOR(i,1,MAX) {
        minsize.push_back(i*i);
        minsize.push_back(i*(i+1));
    }
    // int kl=0,mx=0;
    // rep(i,2,minsize.size()) {
    //     int l=i; int kl=0;
    //     for (int x=i/2;x*(l-x)>minsize[i-1]&&i>=1;x--) {
    //         kl++;
    //         // printf("l=%d: %d %d sz=%lld > %lld\n",l,x,l-x,minsize[i],minsize[i-1]);
    //     }
    //     max_(mx,kl);
    // }
    // printf("mx=%d\n",mx);
    // REP(i,20) printf("%d(%d) ",minsize[i],i); puts("");

    // max-sumsize=MAX
    for (int i=0;i<=MAX;i++) _f[0][i]=1;
    for (int i=1;i<=MAX;i++) { // length, lastlength
        for (int j=1;j<=i;j++) // lastlength
            add_(_f[i][j],_f[i-j][j]); // max-length >= j
        for (int j=i;j>=0;j--)
            add_(_f[i][j],_f[i][j+1]); // last-length
        f[i]=_f[i][0];
    }
    f2[0]=f4[0]=1;
    for (int t=0;t<2;t++) {
        for (int i=MAX;i>=0;i--) {
            for (int j=1;j<=i;j++) add_(f2[i],(ll)f[j]*f2[i-j]%M);
        }
    }
    for (int t=0;t<4;t++) {
        for (int i=MAX;i>=0;i--) {
            for (int j=1;j<=i;j++) add_(f4[i],(ll)f[j]*f4[i-j]%M);
        }
    }
    // FOR(i,1,100) printf("%d ",f[i]); puts("<- f");
    // FOR(i,1,100) printf("%d ",f2[i]); puts("<- f2");
    // FOR(i,1,100) printf("%d ",f4[i]); puts("<- f4");
}
int main() {
    int T,_,op; T=1;
    scanf("%d%d",&T,&op);
    if (op==2) scanf("%lld",&M);
    init();
    FOR(_,1,T) solve(op);
}
/*
100 2
1000000007
1
2
7
200000
*/