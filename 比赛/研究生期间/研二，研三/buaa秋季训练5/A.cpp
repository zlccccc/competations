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

char s[maxn];
ll f[maxn],g[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        int n,i,j;
        ll ans=0;
        scanf("%s",s+1);
        n=strlen(s+1);
        // ll div4=powMM(4,M-2),mul=1;
        // FOR(i,1,n) FOR(j,i,n) {
        //     printf("%d - %d : %lld\n",i,j,powMM(2,i-1)*powMM(10,j-i)%M*powMM(2,n-j)%M);
        //     add_(ans,(s[i]-'0')*powMM(2,i-1)%M*powMM(10,j-i)%M*powMM(2,max(0,n-j-1))%M);
        // }
        // rFOR(i,1,n) {
        //     mul=(mul*5%M+M-1)%M;
        //     add_(ans,mul*div4%M*(s[i]-'0')%M);
        // }
        // mul_(ans,powMM(2,n-1));
        // f[n+1]=0; g[n+1]=1;
        f[n]=s[n]-'0'; g[n]=1;
        rFOR(i,1,n-1) {
            g[i]=(g[i+1]*10+f[i+1])%M;
            f[i]=((g[i+1]*10+f[i+1])*(s[i]-'0')+f[i+1])%M;
        }
        // FOR(i,1,n) printf("%lld ",f[i]); puts("<- f");
        // FOR(i,1,n) printf("%lld ",g[i]); puts("<- g");
        printf("%lld\n",f[1]);
    }
}
/*
*/