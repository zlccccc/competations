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
const LL M=998244353;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

// from (x,y) to (n,m):
// end at (n,m)
ll f[1007][1007][2];
int main() {
    int n,m,i,j;
    scanf("%d%d",&n,&m);
    ll invn=powMM(n,M-2),invm=powMM(m,M-2);
    rFOR(i,0,n) {
        rFOR(j,0,m) {
            //f(i,j,0)=(m-j)/m*f(i,j+1,1)+j/m*f(i,j,1)
            //f(i,j,1)=(n-i)/n*f(i+1,j,0)+i/n*f(i,j,0);
            // if (i==n&&j==m) continue;
            ll x=(m-j)*invm%M*f[i][j+1][1]%M;
            ll y=(n-i)*invn%M*f[i+1][j][0]%M;
            ll a=j*invm%M,b=i*invn%M;
            ll inv=powMM((M+1-a*b%M)%M,M-2);
            f[i][j][0]=(x+a*y+a+1)%M*inv%M;
            f[i][j][1]=(y+b*x+b+1)%M*inv%M;
            // printf("%d %d: %lld %lld %lld %lld %lld %lld\n",i,j,a,b,x,y,f[i][j][0],f[i][j][1]);
        }
    }
    // FOR(i,0,n) {
    //     FOR(j,0,m) printf("%lld ",f[i][j][0]); puts("");
    // }
    // FOR(i,0,n) {
    //     FOR(j,0,m) printf("%lld ",f[i][j][1]); puts("");
    // }
    ll invnm=powMM(n+m,M-2);
    ll ans=(n*invnm%M*f[1][0][0]+m*invnm%M*f[0][1][1])%M;
    printf("%lld\n",ans);
}
/*
2 2
*/