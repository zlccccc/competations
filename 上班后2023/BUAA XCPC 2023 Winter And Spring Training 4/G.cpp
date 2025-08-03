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
// const LL M=998244353;
const LL M=1e9+7;
// ll M=1;
const LL maxn=2e5+107;
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
 
int A[maxn];
int F[maxn][31];
int Cnt[31][31];
long double p[31][31];
int Rnk[31];
long double ans[31];
int id[31];
int main() {
    int n,m,i,j;
    scanf("%d%d",&m,&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    // FOR(i,1,n) A[i]=1;
    FOR(i,1,m) {
        memset(Rnk,0x3f,sizeof(Rnk));
        FOR(j,1,30) scanf("%d",&F[i][j]);
        // FOR(j,1,30) F[i][j]=j;
        // random_shuffle(F[i]+1,F[i]+31);
        FOR(j,1,30) Rnk[F[i][j]]=min(Rnk[F[i][j]],j);
        int x,y;
        FOR(x,1,n) FOR(y,1,n) if (Rnk[x]<=Rnk[y]) Cnt[x][y]+=1;
    }
    int x,y;
    FOR(x,1,n) FOR(y,1,n) {
        if (Cnt[x][y]==m) p[x][y]=1e-6;
        else if (Cnt[x][y]==0) p[x][y]=1e6;
        else p[x][y]=1.*(m-Cnt[x][y])/Cnt[x][y];
    }
    memset(Rnk,0x3f,sizeof(Rnk));
    // FOR(i,1,30) FOR(j,1,30) printf("%d%c",Cnt[i][j]," \n"[j==30]);
    int prev=0;
    FOR(i,1,30) {
        int next=F[1][i];
        if (Rnk[next]==INF) {
            if (!prev) ans[next]=1;
            else ans[next]=ans[prev]*A[prev]/A[next]*p[prev][next];
            Rnk[next]=min(Rnk[next],i);
            // printf("solve %d %d  %Lf\n",prev,next,ans[F[0][i]]);
            prev=next;
        }
    }
    long double all=0;
    FOR(i,1,n) all+=ans[i];
    FOR(i,1,n) ans[i]/=all;
    FOR(i,1,n) printf("%.100Lf ",ans[i]);
}
/*
*/