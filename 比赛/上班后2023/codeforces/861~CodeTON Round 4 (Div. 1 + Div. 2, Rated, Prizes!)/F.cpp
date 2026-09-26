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
const LL maxn=2e5+107;
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
typedef array<int,2> ar2;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

int n,m,MAX;
ll sum[maxn<<2]; int lz[maxn<<2]; // lz:set-val
void build(int x,int L,int R) {
    if (L==R) {sum[x]=0,lz[x]=-1; return;}
    int mid=(L+R)/2;
    sum[x]=0; lz[x]=-1; // lz:pushdown
    build(x<<1,L,mid); build(x<<1|1,mid+1,R); 
}
void upd(int x,int val,int l,int r) {
    sum[x]=val*(r-l+1); lz[x]=val;
}
void pushdown(int x,int L,int mid,int R) {
    if (lz[x]!=-1) upd(x<<1,lz[x],L,mid),upd(x<<1|1,lz[x],mid+1,R),lz[x]=-1;
}
void pushup(int x,int L,int mid,int R) {
    sum[x]=sum[x<<1]+sum[x<<1|1];
}
int getval(int x,int p,int L,int R) {
    if (L==R) return sum[x];
    int mid=(L+R)/2,ret;
    pushdown(x,L,mid,R);
    if (p<=mid) ret=getval(x<<1,p,L,mid);
    if (mid<p) ret=getval(x<<1|1,p,mid+1,R);
    pushup(x,L,mid,R);
    return ret;
}
void update(int x,int p,int val,int L,int R) {
    if (L==R) {sum[x]+=val,lz[x]=-1; return;}
    int mid=(L+R)/2;
    pushdown(x,L,mid,R);
    if (p<=mid) update(x<<1,p,val,L,mid);
    if (mid<p) update(x<<1|1,p,val,mid+1,R);
    pushup(x,L,mid,R);
}
void set_same(int x,int l,int r,int val,int L,int R) {
    if (l<=L&&R<=r) {upd(x,val,L,R); return;}
    int mid=(L+R)/2;
    pushdown(x,L,mid,R);
    if (l<=mid) set_same(x<<1,l,r,val,L,mid);
    if (mid<r) set_same(x<<1|1,l,r,val,mid+1,R);
    pushup(x,L,mid,R);
}
int find_nxt_non_w(int x,int p,int w,int L,int R) {
    if ((ll)w*(R-L+1)==sum[x]) return -1;
    if (L==R) return L;
    int mid=(L+R)/2,ret=-1;
    pushdown(x,L,mid,R);
    if (p<=mid) ret=find_nxt_non_w(x<<1,p,w,L,mid);
    if (ret==-1) ret=find_nxt_non_w(x<<1|1,p,w,mid+1,R);
    pushup(x,L,mid,R);
    return ret;
}
int find_prev_non_w(int x,int p,int w,int L,int R) {
    if ((ll)w*(R-L+1)==sum[x]) return -1;
    if (L==R) return L;
    int mid=(L+R)/2,ret=-1;
    pushdown(x,L,mid,R);
    if (mid<p) ret=find_prev_non_w(x<<1|1,p,w,mid+1,R);
    if (ret==-1) ret=find_prev_non_w(x<<1,p,w,L,mid);
    pushdown(x,L,mid,R);
    return ret;
}
void add(int x) {
    int y=find_nxt_non_w(1,x,m-1,1,MAX);
    if (y!=x) set_same(1,x,y-1,0,1,MAX);
    update(1,y,1,1,MAX);
    // FOR_(i,1,MAX) printf("%d ",getval(1,i,1,MAX)); printf(" add %d\n",x);
}
void del(int x) {
    int y=find_nxt_non_w(1,x,0,1,MAX); // add
    if (y!=x) set_same(1,x,y-1,m-1,1,MAX);
    update(1,y,-1,1,MAX);
    // FOR_(i,1,MAX) printf("%d ",getval(1,i,1,MAX)); printf(" del %d\n",x);
}
int A[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int q;
        scanf("%d%d%d",&n,&m,&q); MAX=n+21;
        FOR_(i,1,n) scanf("%d",&A[i]);
        build(1,1,MAX);
        FOR_(i,1,n) add(A[i]);
        vector<int> ans;
        FOR_(i,1,q) {
            int x,y;
            scanf("%d%d",&x,&y);
            del(A[x]); add(A[x]=y);
            int now=find_prev_non_w(1,MAX,0,1,MAX);
            // if (getval(1,now,1,MAX)!=1) now++;
            if (sum[1]!=1) now++;
            ans.push_back(now);
        }
        for (int v:ans) printf("%d ",v); puts("");
    }
}