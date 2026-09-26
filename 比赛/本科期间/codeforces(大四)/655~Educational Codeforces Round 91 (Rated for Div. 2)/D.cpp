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

ll getval(ll x,ll k,ll y,ll length,bool alllower) {//alllower: can delete all
    ll ans=length/k*x+(length%k)*y;
    if (length<k) {
        if (!alllower) {
            puts("-1");
            exit(0);
        }
    } else {
        ans=min(ans,y*(length-k)+x);//use y more
    } if (alllower) {
        ans=min(ans,y*length);
    } //all_lower
    return ans;
}
int A[maxn],B[maxn];
int main() {
    int n,m,x,k,y;
    scanf("%d%d%d%d%d",&n,&m,&x,&k,&y);
    int i;
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,m) scanf("%d",&B[i]);
    int le=0,ri=1;
    ll ans=0;
    FOR(i,1,m+1) {
        int low=n,high=1;
        while (A[ri]!=B[i]&&ri<=n) min_(low,A[ri]),max_(high,A[ri]),ri++;
        if (A[ri]!=B[i]&&i!=m+1) return 0*puts("-1");
        int cmplow=INF,cmphigh=0;
        if (le!=0) min_(cmplow,A[le]),max_(cmphigh,A[le]);
        if (ri!=n+1) min_(cmplow,A[ri]),max_(cmphigh,A[ri]);
        //remove this
        if (ri!=le+1) {
            ll now=getval(x,k,y,ri-1-le,(high<cmphigh));
            ans+=now;
            // printf("calculate %d %d %d ,len=%d,low=%d, pos=%d-%d; now=%lld\n",x,k,y,ri-1-le,(high<cmphigh),le+1,ri-1,now);
        } le=ri; ri++;
    } printf("%lld\n",ans);
}
/*
5 0
1000 2 3
3 1 4 5 2

5 2
5 2 1000
3 1 4 5 2
3 2

4 0
5 2 4
4 3 1 2
2 4 3 1
*/