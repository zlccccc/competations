// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
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
#include <functional>
#include <random>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP_(I,N) for (int I=0;I<N;I++)
#define rREP_(I,N) for (int I=N-1;I>=0;I--)
#define rep_(I,S,N) for (int I=S;I<N;I++)
#define rrep_(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR_(I,S,N) for (int I=S;I<=N;I++)
#define rFOR_(I,S,N) for (int I=N;I>=S;I--)

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
// const LL M=1e9+7;
const LL M=998244353;
// ll M=1;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

int V[maxn];
int MAX[maxn*4],MIN[maxn*4];
void build(int x,int l,int r){
    if (l==r) {MAX[x]=MIN[x]=V[l]; return;}
    int mid=(l+r)/2;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
    MAX[x]=max(MAX[x<<1],MAX[x<<1|1]);
}
pii merge(pii x,pii y) {
    return {min(x.first,y.first),max(x.second,y.second)};
}
pii query(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) return {MIN[x],MAX[x]};
    int mid=(L+R)/2;
    pii ret={INF,-INF};
    if (l<=mid) ret=merge(ret,query(x<<1,l,r,L,mid));
    if (mid<r) ret=merge(ret,query(x<<1|1,l,r,mid+1,R));
    return ret;
}
int A[maxn],B[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,x1,y1,x2,y2;
        scanf("%d%d%d%d%d",&n,&x1,&y1,&x2,&y2);
        FOR_(i,1,n) scanf("%d",&A[i]);
        FOR_(i,1,n) scanf("%d",&B[i]);
        FOR_(i,1,n) {if (A[i]==0) A[i]=-1; A[i]+=A[i-1];}
        FOR_(i,1,n) {if (B[i]==0) B[i]=-1; B[i]+=B[i-1];}
        // pii fa={INF,-INF};
        FOR_(i,1,n) V[i]=-A[i-1];
        build(1,1,n);
        set<int> pool,SA,SB;
        FOR_(i,-n-1,n+1) pool.insert(i);
        FOR_(i,x1,n) {
            int l=max(1,i-y1+1),r=i-x1+1;
            pii val=query(1,l,r,1,n);
            val.first+=A[i]; val.second+=A[i];
            // fa=merge(fa,val);
            while (val.first<=val.second) {
                int v=*(pool.lower_bound(val.first));
                if (v<=val.second) SA.insert(v),pool.erase(v);
                else break;
            }
            // printf("x1; %d: %d %d\n",i,val.first,val.second);
        }
        FOR_(i,-n-1,n+1) pool.insert(i);
        // pii fb={INF,-INF};
        FOR_(i,1,n) V[i]=-B[i-1];
        build(1,1,n);
        FOR_(i,x2,n) {
            int l=max(1,i-y2+1),r=i-x2+1;
            pii val=query(1,l,r,1,n);
            val.first+=B[i]; val.second+=B[i];
            // fb=merge(fb,val);
            while (val.first<=val.second) {
                int v=*(pool.lower_bound(val.first));
                if (v<=val.second) SB.insert(v),pool.erase(v);
                else break;
            }
            // printf("x2; %d: %d %d\n",i,val.first,val.second);
        }
        // printf("%d -> %d; %d -> %d\n",fa.first,fa.second,fb.first,fb.second);
        // for (int v:SA) printf("%d ",v); puts("<-SA");
        // for (int v:SB) printf("%d ",v); puts("<-SB");
        bool ok=0;
        for (int v:SA) if (SB.count(-v)) ok=1;
        if (ok) puts("YES");
        else puts("NO");
    }
}
/*
5
5 4 5 1 3
1 1 1 1 1
0 0 0 0 1
*/