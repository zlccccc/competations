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
const LL M=998244353;
// const LL M=1e9+7;
// ll M=1;
const LL maxn=2e6+107;
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

ll A[maxn];
ll C;
ll Sqrt(ll x) {
    if (x==0) return 0;
    if (x==1) return 1;
    ll ret=sqrt(x);
    while (ret*ret<x) ret++;
    while (ret*ret>x) ret--;
    return ret;
}
ll solve(ll x) {
    // printf("solve %lld\n",x);
    ll val=Sqrt(C/x);
    if (val<=x) return val;
    return C/x/x;
    // return max(C/x/x,Sqrt(C/x));
}
const ll MAX=2e6+2;
// C<=x^3: C/x/x; else sqrt(C/x)
ll f[maxn];
ll prefix[maxn];
ll solve(ll X,ll Y,int same=0) {
    ll id=lower_bound(f,f+MAX,Y,greater<ll>())-f; id--;
    ll val=min(X,Y);
    // printf("solve %lld %lld; %lld id=%lld; val=%lld\n",X,Y,prefix[min(val,MAX)]-prefix[id],id,val);
    if (val>=id) return ((prefix[min(val,MAX)]-prefix[id]+id*(Y%M)-id*(id+1)/2)%M+M)%M;
    else return (val*(Y%M)-(val+1)*val/2%M+M)%M;
}
int main() {
    int n,i;
    scanf("%d%lld",&n,&C);
    A[0]=A[n+1]=0;
    FOR(i,1,n) scanf("%lld",&A[i]);
    FOR(i,1,n) if (A[i-1]>0&&A[i]>0&&A[i]>solve(A[i-1])) return 0*puts("0");
    FOR(i,1,n) if (A[i-1]<=0&&A[i]==-1&&A[i+1]<=0) return 0*puts("-1");
    ll ans=1;
    f[0]=INFF;
    ll MX3=0; while (MX3*MX3*MX3<=C) MX3++; MX3--;
    FOR(i,1,MAX) f[i]=solve(i),prefix[i]=(max(0ll,C/i/i-i)+prefix[i-1])%M;
    // printf("%lld  %lld\n",prefix[MAX],prefix[MAX+1]);
    // FOR(i,1,100) printf("%lld(%lld) ",f[i],prefix[i]-prefix[i-1]);
    FOR(i,1,n) {
        if (A[i]==-1) {
            if (A[i-1]==0||A[i+1]==0) ans=(solve(max(A[i-1],A[i+1]))+1)%M*ans%M;
            else if (A[i-1]>0&&A[i+1]>0) {
                ans=ans*(min(solve(A[i-1]),solve(A[i+1]))%M+1)%M;
            } else {
                ll X=solve(A[i-1]),Y=solve(A[i+2]);
                if (X<Y) swap(X,Y);
                // A[i]<=A[i+1]
                // printf("  --- main solve %lld %lld: %lld %lld\n",X,Y,solve(X,Y),solve(Y,X));
                ll noww=solve(X,Y)+solve(Y,X); // 0
                noww+=min(MX3,min(X,Y));
                noww+=X+Y+1; // 0
                // printf("  ------multiply = %lld\n",noww);
                // {
                //     ll real=0,x,y;
                //     FOR(x,1,X) FOR(y,1,Y) if (C/x/y/min(x,y)>0) real++;
                //     real+=X+Y+1;
                //     printf(" ----- real=%lld\n",real);
                // }
                // noww+=1;
                noww%=M;
                ans=ans*noww%M;
                i++; // solved
            } i++;
        }
    }
    printf("%lld\n",ans);
}
/*

*/