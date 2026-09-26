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
const LL M=998244353;
// ll M=1;
const LL maxn=1e4+107;
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

int U[407][407][2],D[407][407][2];
char s[407][407];
int main() {
    int n,m,i,j,k;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%s",s[i]+1);
    FOR(i,1,n) FOR(j,1,m) {
        k=i;
        while (s[k][j]=='.') k--; U[i][j][0]=i-k;
        if (s[k][j]=='m') k--;
        while (s[k][j]=='.') k--; U[i][j][1]=i-k;
        k=i;
        while (s[k][j]=='.') k++; D[i][j][0]=k-i;
        if (s[k][j]=='m') k++;
        while (s[k][j]=='.') k++; D[i][j][1]=k-i;
    }
    // puts("U");
    // FOR(i,1,n) FOR(j,1,m) printf("%d%c",U[i][j][0]," \n"[j==m]);
    // FOR(i,1,n) FOR(j,1,m) printf("%d%c",U[i][j][1]," \n"[j==m]);
    // puts("D");
    // FOR(i,1,n) FOR(j,1,m) printf("%d%c",D[i][j][0]," \n"[j==m]);
    // FOR(i,1,n) FOR(j,1,m) printf("%d%c",D[i][j][1]," \n"[j==m]);
    int ans=0;
    FOR(i,1,n-1) {
        FOR(j,1,m) {
            int o0=0;
            FOR(k,j+2,m) {
                int o1,o2,o3,o4; o0+=(s[i][k-1]=='m');
                if (s[i][k-1]=='#'||o0>1) break;
                REP(o1,2-o0) REP(o2,2-o0-o1) REP(o3,2-o0-o1-o2) REP(o4,2-o0-o1-o2-o3) {
                    int u=min(U[i][j][o1],U[i][k][o2]);
                    int d=min(D[i+1][j][o3],D[i+1][k][o4]);
                    if (u>1&&d>0) max_(ans,u*2+d*2+k-j-1);
                }
            }
        }
    }
    printf("%d\n",ans);
}
/*
*/