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
const int maxn=2e5+107;
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

struct Node {
    int l=0,r=0,lz=-1,MAX=INF;
}T[maxn*64];
// struct Node {
//     int l,r; int lz,MAX;
//     Node() {lz=-1; MAX=INF; l=r=0;}
// }T[maxn*64];
int tot=0;
void Setval(int &x,int val,int L,int R) {
    if (!x) x=++tot;
    T[x].lz=val; T[x].MAX=val+R;
}
void pushdown(int &x,int L,int mid,int R) {
    if (T[x].lz!=-1) {
        Setval(T[x].l,T[x].lz,L,mid);
        Setval(T[x].r,T[x].lz,mid+1,R);
        T[x].lz=-1;
    }
}
void pushup(int &x,int L,int mid,int R) {
    T[x].MAX=max(T[T[x].l].MAX,T[T[x].r].MAX);
    T[x].lz=-1;
}
void dfs(int &x,int L,int R) {
    if (!x) return;
    // if (L==R) {printf("%d(%d;%d) ",T[x].MAX,T[x].lz,L); return;}
    int mid=(L+R)/2;
    pushdown(x,L,mid,R);
    dfs(T[x].l,L,mid);
    dfs(T[x].r,mid+1,R);
    pushup(x,L,mid,R);
}
void update(int &x,int l,int r,int val,int L,int R) {
    if (!x) x=++tot;
    if (l<=L&&R<=r) {Setval(x,val,L,R); return;}
    int mid=(L+R)/2;
    pushdown(x,L,mid,R);
    if (l<=mid) update(T[x].l,l,r,val,L,mid);
    if (mid<r) update(T[x].r,l,r,val,mid+1,R);
    pushup(x,L,mid,R);
}
int query(int x,int val,int L,int R) {
    if (!x) return L;
    if (L==R) return L;
    int mid=(L+R)/2;
    pushdown(x,L,mid,R);
    if (T[T[x].l].MAX<val) return query(T[x].r,val,mid+1,R);
    return query(T[x].l,val,L,mid);
    pushup(x,L,mid,R);
}
int main() {
    int root=0;
    int n;
    scanf("%d",&n);
    FOR_(i,1,n) {
        int l,r;
        scanf("%d%d",&l,&r);
        int now=query(root,l,1,INF); // lower_bound_id
        // printf("now=%d; set %d->%d : %d\n",now,now,now+r-l,l-now);
        update(root,now,now+r-l,l-now,1,INF);
        // dfs(root,1,INF); puts("");
    }
    printf("%d\n",query(root,INF,1,INF)-1);
}
/*
*/