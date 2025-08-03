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

char str[2007][2007];
int value[2007][2007];
int LU[2007][2007],LD[2007][2007];
// int U[2007][2007],D[2007][2007];
int main() {
    // int i; FOR(i,31,46) solve(i);
    int i,j;
    int n,m; scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%s",str[i]+1);
    //f(i,j):{i+j-d to i+j+d;}
    FOR(i,1,n) FOR(j,1,m) {
        // if (str[i][j]==str[i-1][j]) U[i][j]=U[i-1][j]+1;
        // else U[i][j]=1;
        if (str[i][j]==str[i-1][j-1]) LU[i][j]=LU[i-1][j-1]+1;
        else LU[i][j]=1;
    }
    rFOR(i,1,n) FOR(j,1,m) {
        // if (str[i][j]==str[i+1][j]) D[i][j]=D[i+1][j]+1;
        // else D[i][j]=1;
        if (str[i][j]==str[i+1][j-1]) LD[i][j]=LD[i+1][j-1]+1;
        else LD[i][j]=1;
    }
    ll ans=0;
    FOR(i,1,n) FOR(j,1,m) {
        value[i][j]=min(LU[i][j],LD[i][j]);
        if (j<=1||str[i][j]!=str[i][j-1]) min_(value[i][j],1);
        else min_(value[i][j],value[i][j-1]+1);
        if (j<=2||str[i][j]!=str[i][j-2]) min_(value[i][j],1);
        else min_(value[i][j],value[i][j-2]+1);
        ans+=value[i][j];
    }
    // puts("LU");
    // FOR(i,1,n) FOR(j,1,m) printf("%d%c",LU[i][j]," \n"[j==m]);
    // puts("LD");
    // FOR(i,1,n) FOR(j,1,m) printf("%d%c",LD[i][j]," \n"[j==m]);
    // FOR(i,1,n) FOR(j,1,m) printf("%d%c",value[i][j]," \n"[j==m]);
    printf("%lld\n",ans);
}
/*

*/