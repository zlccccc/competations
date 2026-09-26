// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
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
#define REP_(I,N) for (int I=0;I<N;I++)
#define rREP_(I,N) for (int I=N-1;I>=0;I--)
#define rep_(I,S,N) for (int I=S;I<N;I++)
#define rrep_(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR_(I,S,N) for (int I=S;I<=N;I++)
#define rFOR_(I,S,N) for (int I=N;I>=S;I--)

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
// const LL M=1e9+7;
const LL M=998244353;
// ll M=1;
const LL maxn=5e5+107;
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
typedef array<int,2> ar2;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

const int MAX=7;
struct matrix{
    int A[MAX][MAX];
    matrix() {
        memset(A,0,sizeof(A));
    }
};
matrix mul(const matrix &A,const matrix &B){
    matrix C; int i,j,k;
    REP(i,MAX) REP(j,MAX) REP(k,MAX)
        C.A[i][j]=((LL)A.A[i][k]*B.A[k][j]+C.A[i][j])%M;
    return C;
}
matrix poww(matrix a,ll b) {
    matrix ret; int i; REP(i,MAX) ret.A[i][i]=1;
    for (;b;b>>=1ll,a=mul(a,a))
        if (b&1) ret=mul(ret,a);
    return ret;
}

// n个数字,m个未知数; X->X+N有值
bool gauss(int A[17][17],int X[17],int n,int m,int N) {
    int i,j,k;
    REP(i,n) {
        if (!A[i][i]){
            int id=i;
            rep(j,i+1,m) if (A[j][i]) {id=j;break;}
            if (!A[id][i]) continue;
            if (id!=i)
                {rep(j,i,n) swap(A[i][j],A[id][j]); swap(X[i],X[id]);}
        }if (!A[i][i]) continue;
        int rev=powMM(A[i][i],(int)M-2),las=min(n,i+N+1);
        rep(k,i+1,las) if (A[k][i]) {
            int R=(LL)A[k][i]*rev%M;
            X[k]=(X[k]-(LL)R*X[i])%M;
            rrep(j,i,las)
                A[k][j]=(A[k][j]-(LL)R*A[i][j])%M;
        }
    }
    rREP(i,n){
        X[i]=(LL)X[i]*powMM(A[i][i],(int)M-2)%M;
        REP(j,i)
            X[j]=(X[j]-(LL)A[j][i]*X[i])%M;
        (X[i]<0)&&(X[i]+=M);
    }
    return 1;
}
int A[17][17],X[17];
int main() {
    int inv6=powMM(6,M-2);
    // p: f[x]->f[0],f[-1],...,f[-5]
    matrix base;
    FOR_(i,0,5) add_(base.A[i][0],inv6);
    FOR_(i,0,4) add_(base.A[i][i+1],1);
    add_(base.A[6][0],1);
    add_(base.A[6][6],1);
    // f[x]=f[y]*base[y][x]+f[6][x];
    int n;
    scanf("%d",&n);
    matrix f=poww(base,n); // base->0,-1...-5
    // from base to (0,-1,-2...-5)

    int N=0;
    matrix g=poww(base,1e9-6); // -6
    A[N][0]=1; X[0]=0; N++; // f[0]=0;
    rFOR_(x,1,5) {
        g=mul(g,base);
        // f[1e9-x]
        add_(A[N][x],1); X[N]=g.A[6][0];
        FOR_(y,0,5) add_(A[N][y],M-g.A[y][0]);
        N++;
    }
    // REP_(x,N) {
    //     FOR_(y,0,5) printf("%d ",A[x][y]); printf(" = %d\n",X[x]);
    // }
    bool ok=gauss(A,X,N,6,6);
    // printf("ok=%d\n",ok);
    int ans=f.A[6][0];
    // FOR_(x,0,6) printf("%d ",f.A[x][0]); puts("<- f");
    // FOR_(x,0,5) printf("%d ",X[x]); puts("<- X");
    FOR_(x,0,5) add_(ans,(ll)X[x]*f.A[x][0]%M);
    printf("%d\n",ans);
}
/*
*/