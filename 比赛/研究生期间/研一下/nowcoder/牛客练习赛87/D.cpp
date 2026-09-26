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
const LL maxn=1e6+107;
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

vector<ll> v;
int f[maxn];
LL fac[10000002];//Factorial
ll solve(int n,int m) {//m连续
    if (m>n) return 0;
    // if (!m) return fac[n];
    // if (m==1) return fac[n-m+1];
    return fac[n-m+1]*2%M;
}
int main() {
    int i,j,n=20;
    f[1]=1;
    FOR(i,2,n) {
        // FOR(j,1,i-1) f[i]-=f[j]*(i-j+1);
        f[i]=1;
        FOR(j,1,i-1) f[i]-=f[j]*(i-j+1);
        // printf("%d ",f[i]);
    }
    fac[0]=1;
    FOR(i,1,10000000) fac[i]=i*fac[i-1]%M;
    //m>=n/2: 总共一组容斥
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,m; scanf("%d%d",&n,&m);
        ll ans=0;
        if (m==0) ans=fac[n];//1,0
        else if (n==m) ans=0;
        else if (n==m+1) {
            if (n>=2) ans=2;
            else ans=0;
        } else {
            add_(ans,solve(n,m));
            add_(ans,M-solve(n,m+1));
            add_(ans,M-solve(n,m+1));
            add_(ans,solve(n,m+2));
            // printf("fir %d %d   %lld %lld %lld\n",m,ans,solve(n,m),solve(n,m+1),solve(n,m+2));
        }
        ans=M-ans; add_(ans,fac[n]);
        printf("%lld\n",ans);
    }
}
/*
100
4 2
3 1
3 2
3 3
5 2
*/