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
// const LL M=998244353;
ll M=1;
const LL maxn=3e5+107;
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

int T;
int n,m;
const int MAX=28;
struct matrix{
    int A[MAX][MAX];
    matrix(){
        memset(A,0,sizeof(A));
    }
}base,init,tmp;
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
ll mat[3][3],v[3];
int main() {
    int n;
    scanf("%d%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld",&n,&v[0],&v[1],&v[2],
            &mat[0][0],&mat[0][1],&mat[1][0],&mat[1][2],&mat[2][0],&mat[2][1],&M);
    int a,b,c,x,y,z;
    REP(a,3) REP(b,3) REP(c,3) {
        int O=a*9+b*3+c*1;
        init.A[0][O]=v[a]*v[b]%M*v[c]%M;
        REP(x,3) REP(y,3) REP(z,3) {
            int P=x*9+y*3+z*1;
            base.A[P][O]=mat[a][x]*mat[b][y]%M*mat[c][z]%M;
            // printf("%d -> %d: %d\n",P,O,base.A[P][O]);
        }
    }
    base.A[27][27]=1;
    base.A[0*9+1*3+2*1][27]=1;
    matrix ans=mul(init,poww(base,n));
    // REP(i,n) base=mul(base,)
    printf("%d\n",ans.A[0][27]);
}
/*
*/