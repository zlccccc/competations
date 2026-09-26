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
const LL M=998244353;
const LL maxn=4e5+7;
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
void check(int n,int k,int x) {
    int i,j,cnt=0;
    FOR(i,1,n) {
        FOR(j,i+1,n) if (A[j]-A[i]>=x) cnt++;
    } if (cnt!=k) printf("no! cnt=%d; k=%d\n",cnt,k);
    // assert(cnt==k);
}
void solve(int n,int k,int x) {
    int i;
    k=n*(n-1)/2-k;//smaller than
    FOR(i,1,n) {
        if (k<(i-1)) break;
        A[i]=1; k-=i-1;
    } int pos=i;
    FOR(i,1,k) A[i]=x;
    A[pos]=x+1;
    FOR(i,pos+1,n) A[i]=x*(i-1)+1;
    // printf("k=%d\n",k);
}
void doit(int n,int k,int x) {
    int i;
    solve(n,k,x);
    FOR(i,1,n) printf("%d ",A[i]);
    check(n,k,x);
}
int main() {
    int n,k,x;
    scanf("%d%d%d",&n,&k,&x);
    doit(n,k,x);
    // int i,j;
    // FOR(i,1,10) {
    //  FOR(j,1,i*(i-1)/2) {
    //      doit(i,j,1000);
    //  }
    // }
}
/*
7 2 1
*******

10 2 1
****0*****
*/