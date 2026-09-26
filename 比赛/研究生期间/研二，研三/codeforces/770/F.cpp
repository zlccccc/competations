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

int mod;
int p[maxn];
int A[maxn],CNT=0;
char op[2];
void solve(int x,int val) {
    if (A[x]) CNT--;
    if (op[0]=='A') add_(A[x],val,mod); else add_(A[x],mod-val,mod);
    if (A[x]) CNT++;
}
int main() {
    int n,q,i,k;
    scanf("%d%d%d",&n,&q,&mod);
    p[1]=1%mod;
    FOR(i,2,n) p[i]=(p[i-1]+p[i-2])%mod;
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) scanf("%d",&k),add_(A[i],mod-k,mod);
    rFOR(i,2,n) add_(A[i],mod-A[i-1],mod),add_(A[i],mod-A[i-2],mod);
    // FOR(i,1,n) printf("%d ",A[i]); puts("<- A");
    FOR(i,1,n) if (A[i]) CNT++;
    FOR(i,1,q) {
        int l,r;
        scanf("%s%d%d",op,&l,&r);
        solve(l,1);
        if (r+1<=n) solve(r+1,mod-p[r-l+2]);
        if (r+2<=n) solve(r+2,mod-p[r-l+1]);//p[r-l+1]-p[r-l]
        if (CNT) puts("NO");
        else puts("YES");
        // int j;
        // FOR(j,1,n) printf("%d ",A[j]); puts("<- A");
        // FOR(j,2,n) add_(A[j],A[j-1],mod),add_(A[j],A[j-2],mod);
        // FOR(j,1,n) printf("%d ",A[j]); puts("<- A, initial");
        // rFOR(j,2,n) add_(A[j],mod-A[j-1],mod),add_(A[j],mod-A[j-2],mod);
        // FOR(j,1,n) printf("%d ",A[j]); puts("<- A, back");
    }
}
/*
5 3 10
2 5 0 3 5
3 5 8 2 5
B 2 3
B 3 4
A 1 2

3 5 3
2 2 1
0 0 0
A 1 1
A 1 3
A 1 3
B 1 1
B 2 2
A 3 3

*/