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
const ll M=1e9+7;
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
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

int A[maxn];
LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m) {
    // printf("getans C(%d,%d)=%lld\n",n,m,fac[n]*inv[m]%M*inv[n-m]%M);
    if (n<0||m<0) return 0;
    if (n<m) return 0;
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
int main() {
    int i;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,i,j,x,y,p;
        scanf("%d%d%d%d%d",&n,&i,&j,&x,&y);
        assert(i<j); assert(x!=y);
        if (x>y) {
            swap(i,j); swap(x,y); i=n+1-i; j=n+1-j;
        }
        // printf("solve %d %d %d %d %d\n",n,i,j,x,y);
        ll ans=0;
        { // solve
            // printf("%d %d\n",C(y-x-1,j-i-1),C(x-1,i-1));
            if (y==n) {
                if (j!=n) ans=C(y-x-1,j-i-1)%M*C(x-1,i-1)%M;
            } else {
                FOR(p,i+1,j-1) {
                    ll nowadd=1,a=C(n-y-1,j-p-1),b=C(y-x-1,j-(n-y)-1-i),c=C(x-1,i-1);
                    mul_(nowadd,a);// right
                    mul_(nowadd,b);// left
                    mul_(nowadd,c);
                    // printf("mid p=%d: %lld * %lld * %lld\n",p,a,b,c);
                    add_(ans,nowadd);
                }
                FOR(p,j+1,n-1) {
                    // printf("p=%d: %lld * %lld * %lld\n",p,C(n-y-1,p-j-1),C(y-x-1,j-i-1),C(x-1,i-1));
                    add_(ans,C(n-y-1,p-j-1)*C(y-x-1,j-i-1)%M*C(x-1,i-1)%M);
                }
            }
        }
        printf("%lld\n",ans);
    }
}
/*
100
3 1 3 2 3
3 2 3 3 2
4 3 4 3 1
5 2 5 2 4
5 3 4 5 4
9 3 7 8 6
20 6 15 8 17

*/