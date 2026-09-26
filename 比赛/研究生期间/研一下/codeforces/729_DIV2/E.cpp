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
int Prefix[507*507];//F-not same
int C[507][507];
int main() {
    int i,j,k,mod,n;
    scanf("%d%d",&n,&mod);
    val[0]=1; Prefix[0]=1;
    FOR(i,2,n) {
        FOR(j,1,i*(i-1)/2) Prefix[j]=(Prefix[j-1]+val[j])%mod;
        FOR(j,1,i-1) val[j]=Prefix[j];
        FOR(j,i,i*(i-1)/2) val[j]=(Prefix[j]-Prefix[j-i]+mod)%mod;
        FOR(j,1,i*(i-1)/2) Prefix[j]=(Prefix[j-1]+val[j])%mod;//Prefix
        // FOR(j,0,i*(i-1)/2) printf("%-4d ",val[j]); puts("<- val");
        // FOR(j,0,i*(i-1)/2) printf("%-4d ",Prefix[j]); puts("<- Prefix");
        FOR(j,1,i) {
            // ll f1,f2;
            ll nowsum=0;
            // FOR(f1,0,i*(i-1)/2)
            //     FOR(f2,f1+j+1,i*(i-1)/2) nowsum+=val[f1]*val[f2]%mod;
            // nowsum%=mod;
            // printf("nowsum=v1 %lld\n",nowsum); nowsum=0;
            FOR(k,0,i*(i-1)/2) {
                ll now=(ll)Prefix[k]*val[k+j+1]%mod;
                nowsum+=now;
            } nowsum%=mod;
            // printf("%d %d: %lld\n",i,j,nowsum);
            f[i]=(f[i]+(ll)(i-j+1)*nowsum)%mod;//first; second
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
5 403458273

*/