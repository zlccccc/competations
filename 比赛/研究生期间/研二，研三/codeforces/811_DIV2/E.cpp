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

typedef array<ll,4> ar4;
// prefmax,sufmax,sum,max
vector<ar4> Q[1<<19|7];
ar4 merge(ar4 x,ar4 y) {
    ar4 ret;
    ret[0]=max(x[0],x[2]+y[0]);
    ret[1]=max(x[1]+y[2],y[1]);
    ret[2]=x[2]+y[2];
    ret[3]=max(max(x[3],y[3]),x[1]+y[0]);
    return ret;
}
int A[1<<18|7];
void solve(int x,int l,int r) {
    if (l+1==r) {
        Q[x].push_back({max(0,A[l]),max(0,A[l]),A[l],max(0,A[l])});
        return;
    }
    int mid=(l+r)/2;
    solve(x<<1,l,mid); solve(x<<1|1,mid,r);
    int len=(r-l)>>1,i;
    Q[x].resize(len<<1);
    // printf("solve %d %d %d; len=%d\n",x,l,r,len);
    REP(i,len) {
        Q[x][i]=merge(Q[x<<1][i],Q[x<<1|1][i]);
        Q[x][i|len]=merge(Q[x<<1|1][i],Q[x<<1][i]);
    }
    vector<ar4>().swap(Q[x<<1]);
    vector<ar4>().swap(Q[x<<1|1]);
}
int all=0;
int main() {
    int n,i;
    scanf("%d",&n); n=1<<n;
    REP(i,n) scanf("%d",&A[i]);
    solve(1,0,n);
    // REP(i,n) printf("%d ",Q[1][i][3]);
    int q; scanf("%d",&q);
    REP(i,q) {
        int now; scanf("%d",&now);
        all^=1<<now;
        printf("%lld\n",Q[1][all][3]);
    }
}