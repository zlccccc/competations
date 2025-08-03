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
const LL maxn=2e5+107;
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

int P;
const int MAX=27;
struct matrix{
    int A[MAX][MAX];
    matrix(){
        memset(A,0,sizeof(A));
    }
}base;
matrix mul(const matrix &A,const matrix &B){
    matrix C; int i,j,k;
    REP(i,MAX) REP(j,MAX) REP(k,MAX)
        C.A[i][j]=((LL)A.A[i][k]*B.A[k][j]+C.A[i][j])%P;
    return C;
}
matrix poww(matrix a,ll b) {
    matrix ret; int i; REP(i,MAX) ret.A[i][i]=1;
    for (;b;b>>=1ll,a=mul(a,a))
        if (b&1) ret=mul(ret,a);
    return ret;
}
int Sum[57];
int A[57];
int mx0,mx1,mx2,G;
inline int f(int x,int y,int z) {
    return x*G*G+y*G+z;
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,D,K;
        scanf("%d%d%d%d",&n,&K,&P,&G);
        //k-color; mod-g=0
        int ans=0;
        FOR(D,1,G) {
            int i,j,k;
            base=matrix();
            mx0=D-1;
            mx1=D-1; if (K<=1) mx1=0;
            mx2=D-1; if (K<=2) mx2=0;
            REP(i,MAX) base.A[i][i]=1; 
            FOR(i,0,mx0) {
                FOR(j,0,mx1) {
                    FOR(k,0,mx2) {
                        if (K>0) base.A[f(i,j,k)][f((i+1)%D,j,k)]++;
                        if (K>1) base.A[f(i,j,k)][f(i,(j+1)%D,k)]++;
                        if (K>2) base.A[f(i,j,k)][f(i,j,(k+1)%D)]++;
                    }
                }
            }
            matrix now=poww(base,n);
            // printf("%d : %d\n",D,now.A[0][0]);
            add_(ans,now.A[0][0],P);
        } printf("%d\n",ans);
    }
}
/*
*/