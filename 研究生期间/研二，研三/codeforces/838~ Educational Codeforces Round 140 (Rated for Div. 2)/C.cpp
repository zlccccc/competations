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
#include <unordered_set>
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
const LL maxn=4e5+107;
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

int A[107][107];
int B[107][107]; // limit not same
int R[107],L[107]; // to-right
inline int getfa(int x) { // R: same
    if (R[x]==x) return x;
    return R[x]=getfa(R[x]);
}
ll f[107][107][2];
// ll f[107];
int main() {
    int n; int i,j,k,l;
    scanf("%d",&n);
    FOR(i,1,n) R[i]=i;
    FOR(i,1,n) {
        FOR(j,i,n) {
            scanf("%d",&A[i][j]);
            if (A[i][j]==1) {
                while (getfa(i)!=getfa(j)) R[getfa(i)]=getfa(j);
            }
        }
    }
    FOR(i,1,n) if (A[i][i]==2) return 0*puts("0");
    FOR(i,1,n) FOR(j,i,n) FOR(k,i,j) if (A[i][j]==1) {
        if (A[i][k]==2||A[k][j]==2) return 0*puts("0");
        else A[i][k]=A[k][j]=1;
    }
    // FOR(i,1,n) R[i]=getfa(i);
    // FOR(i,1,n) FOR(j,i,n) if (getfa(i)==getfa(j)) {
    //     if (A[i][j]==2) return 0*puts("0");
    //     else A[i][j]=1;
    // }
    // FOR(i,1,n) FOR(j,i,n) FOR(k,i,j) if (A[i][k]==2||A[k][j]==2) {
    //     if (A[i][j]==1) return 0*puts("0");
    //     A[i][j]=2;
    // }
    // FOR(i,1,n) FOR(j,i,n) printf("%d%c",A[i][j]," \n"[j==n]);

    FOR(l,1,n) {
        FOR(i,1,n-l+1) {
            j=i+l-1; // 枚举第一个分界线
            if (i==j) f[i][j][1]=2; //same
            else {
                FOR(k,i+1,j) {
                    // printf("%d ->  %d -- %d -> %d: %d %d\n",i,k-1,k,j,A[i][k],A[k-1][j]);
                    // if (A[i][k]==1||A[k-1][j]==1) continue;
                    if (A[k-1][k]==1) continue;
                    if (A[k][j]==2||!f[k][j][1]) continue;
                    // i->k-1: same/notsame; k->j: same
                    add_(f[i][j][0],(ll)(f[i][k-1][0]+f[i][k-1][1])%M);
                }
                if (f[i][j-1][1]&&f[i+1][j][1]) f[i][j][1]=2;
                if (A[i][j]==1) f[i][j][0]=0;
                if (A[i][j]==2) f[i][j][1]=0;
            }
            // printf("%d->%d: (%d %d)\n",i,j,f[i][j][0],f[i][j][1]);
        }
    }
    printf("%lld\n",(f[1][n][0]+f[1][n][1])%M);
}
/*
*/