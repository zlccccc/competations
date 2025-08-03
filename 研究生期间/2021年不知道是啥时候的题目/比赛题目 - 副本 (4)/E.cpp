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

ll Val[maxn];
ll MIN[maxn*4],MAX[maxn*4];
void build(int x,int l,int r) {
    if (l==r) {MIN[x]=MAX[x]=Val[l]; return;}
    int mid=(l+r)/2;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
    MAX[x]=max(MAX[x<<1],MAX[x<<1|1]);
}
ll _MIN,_MAX;
void query(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) {
        min_(_MIN,MIN[x]);
        max_(_MAX,MAX[x]);
        return;
    }
    int mid=(L+R)/2;
    if (l<=mid) query(x<<1,l,r,L,mid);
    if (mid<r) query(x<<1|1,l,r,mid+1,R);
}
ll A[maxn],B[maxn];
int main() {
    int i,n,q;
    scanf("%d%d",&n,&q);
    FOR(i,1,n) scanf("%lld",&A[i]);
    FOR(i,1,n) scanf("%lld",&B[i]);
    // FOR(i,1,n) A[i]=0,B[i]=1e9;
    FOR(i,1,n) Val[i]=B[i]-A[i];
    FOR(i,1,n) Val[i]+=Val[i-1];
    build(1,1,n);

    FOR(i,1,q) {
        int l,r; scanf("%d%d",&l,&r);
        _MIN=INFF; _MAX=-INFF;
        query(1,l,r,1,n);
        if (_MIN<Val[l-1]) puts("-1");
        else if (Val[r]!=Val[l-1]) puts("-1");
        else printf("%lld\n",_MAX-Val[l-1]);
    }
}
/*
8 5
0 0 0 0 0 0 0 0
2 2 1 9 4 1 5 8
2 6
1 7
2 4
7 8
5 8
*/