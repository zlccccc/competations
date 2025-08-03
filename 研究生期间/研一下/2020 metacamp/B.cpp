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
const LL maxn=2e5+107;
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

int A[maxn];
struct V{
    int mx1=0,mx2=0,mx3=0;
    void insert(int x) {
        if (x>mx1) swap(x,mx1);
        if (x>mx2) swap(x,mx2);
        if (x>mx3) swap(x,mx3);
    }
}T[maxn*4];
V merge(V x, V y) {
    x.insert(y.mx1);
    x.insert(y.mx2);
    x.insert(y.mx3);
    return x;
}
void build(int x,int l,int r) {
    if (l==r) {T[x]=V(); T[x].insert(A[l]); return;}
    int mid=(l+r)/2;
    build(x<<1,l,mid); build(x<<1|1,mid+1,r);
    T[x]=merge(T[x<<1],T[x<<1|1]);
    // printf("%d-%d: %d %d %d\n",l,r,T[x].mx1,T[x].mx2,T[x].mx3);
}
V query(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) return T[x];
    V ret; int mid=(L+R)/2;
    if (l<=mid) ret=merge(ret,query(x<<1,l,r,L,mid));
    if (mid<r) ret=merge(ret,query(x<<1|1,l,r,mid+1,R));
    return ret;
}
int main() {
    int n,w,i; bool ok=0;
    while (~scanf("%d%d",&n,&w)){
        if (ok) puts(""); ok=1;
        FOR(i,1,n) scanf("%d",&A[i]);
        build(1,1,n);
        // printf("f: %d %d %d\n",T[1].mx1,T[1].mx2,T[1].mx3);
        FOR(i,1,n-w+1) {
            printf("%d",query(1,i,i+w-1,1,n).mx3);
            if (i!=n-w+1) printf(" ");
        }
    }
}
/*
*/