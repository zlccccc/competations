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

int A[maxn],B[maxn];
void solve(int n) {
    int i,j;
    REP(j,n) scanf("%d",&B[j]);
    reverse(B,B+n);
    // REP(j,n) REP(i,n) if (((i+j)&j)==j) A[i]^=B[j];
    REP(j,n) REP(i,n) if ((i&j)==0) A[i]^=B[j];
    REP(i,n) printf("%d ",A[i]);
    puts("");
    // REP(j,n) {
    //     printf("j=%d\n",j);
    //     // REP(i,n) if (((i+j)&j)==j) printf("%d ",i); puts("<- i");
    //     REP(i,n) if ((i&j)==0) printf("%d ",i); puts("<- i");
    // }
}
int val[maxn];
int main() {
    int i,j;
    int n,m=0; scanf("%d",&n);
    // solve(n);
    while ((1<<m)<n) m++;
    REP(i,n) scanf("%d",&A[i]); // i&j==0
    // reverse(A,A+(1<<m));
    // int all=A[0];
    // rREP(i,n) A[i]^=A[0]; // XOR(i&j!=0)
    REP(i,m) {//less
        REP(j,n) if ((j>>i)&1) A[j]^=A[j^(1<<i)];
    }
    REP(i,m) {//more
        REP(j,n) if (!((j>>i)&1)) A[j]^=A[j^(1<<i)];
    }
    // REP(i,(1<<m)) printf("%d ",A[i]); puts("<- A");
    reverse(A,A+n);
    REP(i,n) printf("%d ",A[i]);
}
/* 
3
1 2 3

10
346484077 532933626 858787727 369947090 299437981 416813461 865836801 141384800 157794568 691345607

10
725081944 922153789 481174947 427448285 516570428 509717938 855104873 280317429 281091129 1050390365
346484077 532933626 858787727 369947090 299437981 416813461 865836801 141384800 157794568 691345607

*/