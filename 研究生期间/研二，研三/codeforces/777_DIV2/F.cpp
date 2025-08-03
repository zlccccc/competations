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

int A[maxn];
int dp1[maxn],dp3[maxn],dp2[maxn][2];
//dp1/dp3: not contain A[i], minimum value
int solve(int n) {
    int i,pos=max_element(A+1,A+1+n)-A,ans=0;
    FOR(i,1,n) dp1[i]=dp3[i]=INF;
    dp1[1]=0;
    FOR(i,2,pos) {
        if (A[i-1]<A[i]) min_(dp1[i],dp1[i-1]);
        if (dp1[i-1]<A[i]) min_(dp1[i],A[i-1]);
    } dp3[n]=0;
    rFOR(i,pos,n-1) {
        if (A[i+1]<A[i]) min_(dp3[i],dp3[i+1]);
        if (dp3[i+1]<A[i]) min_(dp3[i],A[i+1]);
    }
    FOR(i,1,n) dp2[i][0]=INF,dp2[i][1]=-INF;
    // printf("pos=%d\n",pos);
    dp2[pos][0]=dp1[pos];
    FOR(i,pos+1,n) { //0:up; 1:down; save the (min,max) of other seq
        dp2[i][0]=dp1[i];
        if (A[i-1]>A[i]) min_(dp2[i][0],dp2[i-1][0]);//to-down
        if (dp2[i-1][0]<A[i]) max_(dp2[i][1],A[i-1]);//to-down
        if (dp2[i-1][1]>A[i]) min_(dp2[i][0],A[i-1]);//to-up
        if (A[i-1]<A[i]) max_(dp2[i][1],dp2[i-1][1]);//to-up
        if (dp2[i][1]>dp3[i]) ans++;
    }
    // FOR(i,1,n) printf("%10d%c",dp1[i]," \n"[i==n]);
    // FOR(i,1,n) printf("%10d%c",dp3[i]," \n"[i==n]);
    // FOR(i,1,n) printf("%10d%c",dp2[i][0]," \n"[i==n]);
    // FOR(i,1,n) printf("%10d%c",dp2[i][1]," \n"[i==n]);
    return ans;
}
int main() {
    int n,i; scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]); //ind=0: remove
    reverse(dp3+1,dp3+1+n);
    int ans=solve(n);
    reverse(A+1,A+1+n);
    ans+=solve(n);
    printf("%d\n",ans);
}
/*
*/