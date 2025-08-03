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
const LL maxn=1.2e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

int P[507],f[507];
int val[507*507];
int S1[507*507],S2[507*507];//F-not same
int C[507][507];
int main() {
    int i,j,k,mod,n;
    scanf("%d%d",&n,&mod);
    val[0]=1; S1[0]=S2[0]=1;
    FOR(i,2,n) {
        FOR(j,1,i*(i-1)/2) S1[j]=(S1[j-1]+val[j])%mod;
        FOR(j,1,i-1) val[j]=S1[j];
        FOR(j,i,i*(i-1)/2) val[j]=(S1[j]-S1[j-i]+mod)%mod;
        FOR(j,1,i*(i-1)/2+i+2) S1[j]=(S1[j-1]+val[j])%mod;//S1
        FOR(j,1,i*(i-1)/2+i+2) S2[j]=(S2[j-1]+(ll)val[j]*j)%mod;//S2
        FOR(k,0,i*(i-1)/2) {
            // FOR(j,1,i) {
            //     ll now=(ll)S1[k]*val[k+j+1]%mod;
            //     f[i]=(f[i]+(ll)(i-j+1)*now)%mod;//first;
            // }
            // 
            // ll noww=0;
            // FOR(j,1,i) noww+=(i-j+1)*val[k+j+1]%mod;//second
            // FOR(j,k+2,k+i+1) noww+=(i-j+k+2)*val[j]%mod;//third
            ll now=((i+k+2)*((ll)S1[k+i+2]-S1[k+1]+mod)+mod-(S2[k+i+2]-S2[k+1]))%mod;//final
            // printf("noww; %lld %lld\n",noww,now%mod);
            f[i]=(f[i]+(ll)S1[k]*now)%mod;//first; second
            //sum[(i+1-j)*val[k+j+1]]
        }
    }
    P[0]=1;
    FOR(i,1,n) P[i]=(ll)P[i-1]*i%mod;
    // FOR(j,1,n) FOR(i,0,j) printf("%-4d%c",C[i][j]," \n"[i==j]);
    // FOR(j,1,n) FOR(i,0,j) printf("%-4d%c",pC[i][j]," \n"[i==j]);
    C[0][0]=1;
    FOR(j,1,n) {
        C[0][j]=1;
        FOR(i,1,j) C[i][j]=(C[i-1][j-1]+C[i][j-1])%mod;
    }
    // FOR(j,1,n) printf("%d ",f[j]); puts("<- f[j]");
    ll ans=0;
    FOR(i,0,n-1) {
        ans=(ans+(ll)f[n-i-1]*P[i]%mod*C[i][n])%mod;
    } 
    printf("%lld\n",ans);
}
/*
10 403458273
400647286
*/