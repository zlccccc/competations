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

void solve(int x,int k) {
    int i;
    set<string> S; string str;
    REP(i,x) str+=((char)i+'a');
    S.insert(str);
    FOR(i,1,k) {
        set<string> nxt;
        for (auto s:S) {
            string t=s; int l=s.length(),x,y;
            REP(x,l) rep(y,x+1,l) {
                swap(t[x],t[y]);
                // printf("%s->%s",s,t);
                nxt.insert(t);
                swap(t[x],t[y]);
            }
        }
        S.swap(nxt); nxt.clear();
        printf("%d ",(int)S.size());
    }
    puts("  <- solve");
}
ll fac[maxn],inv[maxn];
LL C(int n,int m) {
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
ll C_(int n,int m) {
    ll ret=1; int i;
    FOR(i,n-m+1,n) ret=ret*i%M;
    return ret*inv[m]%M;
}
ll f[407][207],g[407][207];
ll ans[407];
int main() {
    int n,k,i,j;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
    // solve(1,7);
    // solve(2,7);
    // solve(3,7);
    // solve(4,7);
    // solve(5,7);
    // solve(6,7);
    // solve(7,7);
    FOR(i,0,200) f[2][i]=1;
    FOR(i,3,400) {//not unique
        f[i][0]=1;
        FOR(j,1,200) f[i][j]=(f[i-1][j-1]*(i-1)+f[i-1][j])%M;
    }
    FOR(i,1,10) {FOR(j,1,10) printf("%-10lld ",f[i][j]); puts("");}
    scanf("%d%d",&n,&k);
    ans[0]=1;//not change
    FOR(j,1,k) {
        if (j>=2) ans[j]=ans[j-2];
        for (i=0;i<=min(n,2*j);i++) {
            add_(ans[j],C_(n,i)*g[i][j]%M);
        }
    }
    FOR(j,1,k) printf("%lld ",ans[j]);
}
/*
*/