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

int T[maxn*4],sum[maxn*4];
void update(int x,int L,int R) {
    if (T[x]) sum[x]=0;
    else {
        if (L==R) sum[x]=1;
        else sum[x]=sum[x<<1]+sum[x<<1|1];
    }
}
void update(int x,int l,int r,int val,int L,int R) {
    if (l<=L&&R<=r) {
        T[x]+=val;
        update(x,L,R);
        return;
    } int mid=(L+R)/2;
    if (l<=mid) update(x<<1,l,r,val,L,mid);
    if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
    update(x,L,R);
    // if (x==1) printf("update %d (%d-%d) %d %d %d; sum=%d\n",x,l,r,val,L,R,sum[x]);
}
int A[maxn],pre[maxn],id[maxn];
int main() {
    int n,i; ll ans=0;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) pre[i]=id[A[i]],id[A[i]]=i;
    FOR(i,1,n) {
        update(1,i,i,0,1,n);
        update(1,pre[i]+1,i,1,1,n);
        int p=pre[pre[i]];
        if (p) update(1,pre[p]+1,p,-1,1,n);
        if (pre[p]) update(1,pre[pre[p]]+1,pre[p],1,1,n);
        ans+=sum[1];
        // printf("i=%d: %d\n",i,sum[1]);
    } printf("%lld\n",ans);
}
/*
3 100
4 2 6
3 1
1 2
100 0
1 6
1 7 
*/