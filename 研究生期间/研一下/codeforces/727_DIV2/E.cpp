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

multiset<pair<int,int> > sx,sy;//value
int A[maxn][2],B[maxn][2];//right-position
void doit(multiset<pii> &S,int k,int rpos,int l,int r) {
    while (S.size()&&S.begin()->first<l) {
        A[S.begin()->second][k]=rpos;
        S.erase(S.begin());
    } while (S.size()&&S.rbegin()->first>r) {
        A[S.rbegin()->second][k]=rpos;
        auto it=S.end(); it--; S.erase(it);
    }
}
int R[maxn][2];//next->k is okay
int main() {
    int n,i;
    scanf("%d%*d",&n);
    sx.insert(make_pair(0,0)); sy.insert(make_pair(0,0));
    B[0][0]=n; B[0][1]=n;
    FOR(i,1,n) {
        int k; scanf("%d",&k);
        sx.insert(make_pair(k,i));
        sy.insert(make_pair(k,i));
        int l,r;
        scanf("%d%d",&l,&r);
        if (l<=k&&k<=r) B[i][0]=n; else B[i][0]=i-1;
        doit(sx,0,i-1,l,r);
        scanf("%d%d",&l,&r);
        if (l<=k&&k<=r) B[i][1]=n; else B[i][1]=i-1;
        doit(sy,1,i-1,l,r);
    } doit(sx,0,n,-1,-1);
    doit(sy,1,n,-1,-1);
    int rx=n+1,ry=n+1;//minimize position
    B[n+1][0]=B[n+1][1]=n+1;
    R[n+1][0]=R[n+1][1]=n+1;
    rFOR(i,1,n) {
        if (i<n) {
            B[i][0]=min(B[i][0],B[i+1][0]);
            B[i][1]=min(B[i][1],B[i+1][1]);
        } int nxtrx=rx,nxtry=ry;
        if (ry-1<=min(B[i][0],A[i-1][1])) nxtrx=i,R[i][0]=ry-1;
        if (rx-1<=min(B[i][1],A[i-1][0])) nxtry=i,R[i][1]=rx-1;
        rx=nxtrx; ry=nxtry;
    }
    // FOR(i,1,n) printf("%d ",A[i][0]); puts("<- 0");
    // FOR(i,1,n) printf("%d ",A[i][1]); puts("<- 1");
    // FOR(i,1,n) printf("%d ",B[i][0]); puts("<- B0");
    // FOR(i,1,n) printf("%d ",B[i][1]); puts("<- B1");
    // FOR(i,1,n) printf("%d ",R[i][0]); puts("<- R0");
    // FOR(i,1,n) printf("%d ",R[i][1]); puts("<- R1");
    int mark;
    if (R[1][0]) mark=0;
    else if (R[1][1]) mark=1;
    else return 0*puts("No");
    puts("Yes");
    FOR(i,1,n) {
        int k=R[i][mark];
        while (i<=k) i++,printf("%d ",mark);
        mark^=1; i--;
    }
    // FOR(i,1,n) printf("%d%c",Ans[i]," \n"[i==n]);
}
/*
*/
