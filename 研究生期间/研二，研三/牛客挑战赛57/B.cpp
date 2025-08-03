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

ll A[107][107];
void solve(int n,int m,ll ans) {
    int tot=0;
    int i,j,x,y;
    FOR(i,1,n) FOR(j,1,m) A[i][j]=++tot;
    FOR(i,1,n) FOR(j,1,m) A[i][j]=A[i][j]^A[i-1][j]^A[i][j-1]^A[i-1][j-1];
    FOR(i,1,n) FOR(j,1,m) FOR(x,i,n) FOR(y,j,m) {
        if ((A[x][y]^A[i-1][j-1]^A[i-1][y]^A[x][j-1])==ans)
            printf("ans=%lld; %d %d %d %d\n",ans,i,j,x,y);
    }
}
int n,m;
ll ans=0;
pll getpos(ll x) {
    // printf("getpos %lld\n",x);
    return make_pair((x-1)/m+1,(x-1)%m+1);
}
int main() {
    int i,x;
    scanf("%d",&n);
    scanf("%d",&m);
    if (n==1&&m==1) {printf("1\n1 1 1 1\n"); return 0;}
    ll now=(ll)n*m,ans=0;
    while (now) ans=ans*2+1,now>>=1;
    printf("%lld\n",ans);
    // solve(n,m,ans);
    pii px=getpos(ans/2),py=getpos(ans/2+1);
    if (abs(px.second-py.second)+abs(px.first-py.first)==1) printf("%d %d %d %d\n",px.first,px.second,py.first,py.second);
    else printf("%d %d %d %d\n",px.first,(m+1)/2,py.first,(m+1)/2);
}
/*
1000000 99999999
*/