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
const LL M=1e9+7;
const LL maxn=2e5+107;
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

ll f[1007][1007][2];
void init() {
    int i,x,j;
    f[0][0][0]=1;
    FOR(i,0,1000) FOR(x,0,1000) {
        // f[x,0] -> 3*[x,0]+1*[x+1,1]
        // f[x,1] -> 1*[x,0]+3*[x+1,1]
        // first
        // add_(f[i+1][x][0],3*f[i][x][0]%M);
        // add_(f[i+1][x+1][1],f[i][x][0]);
        // // second
        // add_(f[i+1][x][0],f[i][x][1]);
        // add_(f[i+1][x+1][1],3*f[i][x][1]%M);

        // f[i+1][x][0]=(3*f[i][x][0]+f[i][x][1])%M;
        // f[i+1][x+1][1]=(3*f[i][x][1]+f[i][x][0])%M;
        f[i+1][x][0]=(3*f[i][x][0]+f[i][x][1])%M;
        f[i+1][x+1][1]=(3*f[i][x][1]+f[i][x][0])%M;
    }
    // FOR(i,0,10) FOR(j,0,10) printf("(%lld,%lld)%c",f[i][j][0],f[i][j][1]," \n"[j==10]);
}
LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m) {
    if (n<m) return 0;
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
ll pw3[1000002];
int main() {
    int i;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
    pw3[0]=1;
    FOR(i,1,1000000) pw3[i]=pw3[i-1]*3%M;
    // init();
    int T,_; T=1;
    // scanf("%d",&T);
    FOR(_,1,T){
        int n,k,a,b,c,d; // 0-0; 0-1; 1-0; 1-1
        /*to solve the problem*/
        scanf("%d%d",&n,&k);
        ll Ans=0;
        FOR(b,0,n) {// 枚举b
            FOR(c,max(0,b-1),b) {
                d=k-b;
                a=n-b-c-d;
                if (c<0||a<0||d<0) continue;
                if (b==0&&(c||d)) continue;
                ll ans=pw3[a+d];
                // printf("f %d %d %d %d\n",a,b,c,d);
                if (d) mul_(ans,C(b+d-1,d));
                mul_(ans,C(c+a,a));
                add_(Ans,ans);
                // printf("ans += %lld %lld %lld\n",pw3[a+d],C(b+d-1,d),C(c+a,a));
            }
        }
        printf("%lld\n",Ans);
        // printf("dp %lld\n",(f[n][k][0]+f[n][k][1])%M);
    }
}
/*
100
0 0
0 1
1 1
1 0
1 3
3 1
3 0
4 2
4 3
998 244
*/