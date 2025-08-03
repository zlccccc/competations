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
const LL maxn=5e5+107;
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

struct node{
    int lv,rv,l_len,r_len,maxlen_0,maxlen_1,same,tag=0;
    node() {
        lv=rv=0;
        same=1;
        l_len=r_len=1;
        maxlen_0=1; maxlen_1=0;
        tag=0;
    }
    void rev() {
        tag^=1;
        lv^=1; rv^=1;
        swap(maxlen_0,maxlen_1);
    }
}T[maxn<<2];
node merge(node x,node y) {
    node ret;
    ret.lv=x.lv;
    ret.rv=y.rv;
    ret.l_len=x.l_len+x.same*(int)(x.rv==y.lv)*y.l_len;
    ret.r_len=y.r_len+y.same*(int)(x.rv==y.lv)*x.r_len;
    ret.maxlen_0=max(x.maxlen_0,y.maxlen_0);
    ret.maxlen_1=max(x.maxlen_1,y.maxlen_1);
    ret.same=x.same&y.same;
    ret.tag=0;
    if (x.rv==y.lv) {
        if (x.rv==0) ret.maxlen_0=max(ret.maxlen_0,x.r_len+y.l_len);
        if (x.rv==1) ret.maxlen_1=max(ret.maxlen_1,x.r_len+y.l_len);
    } else ret.same=0;
    return ret;
}
void update(int x,int l,int r,int L,int R) {
    // printf("update %d %d %d\n",x,L,R);
    // printf("solve x=%d; l=%d(%d); r=%d(%d); maxlen=%d; same=%d; tag=%d\n",x,T[x].lv,T[x].l_len,T[x].rv,T[x].r_len,T[x].maxlen_1,T[x].same,T[x].tag);
    if (l<=L&&R<=r) {
        T[x].rev();
        return;
    }
    int mid=(L+R)/2;
    if (T[x].tag) T[x<<1].rev(),T[x<<1|1].rev(),T[x].tag=0;
    if (l<=mid) update(x<<1,l,r,L,mid);
    if (mid<r) update(x<<1|1,l,r,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
node query(int x,int l,int r,int L,int R) {
    // printf("L,R=%d %d\n",L,R);
    // printf("solve x=%d; l=%d(%d); r=%d(%d); maxlen=%d; same=%d; tag=%d\n",x,T[x].lv,T[x].l_len,T[x].rv,T[x].r_len,T[x].maxlen_1,T[x].same,T[x].tag);
    if (l<=L&&R<=r) return T[x];
    int mid=(L+R)/2;
    if (T[x].tag) T[x<<1].rev(),T[x<<1|1].rev(),T[x].tag=0;
    node ret; ret.maxlen_0=ret.maxlen_1=0;
    if (l<=mid&&mid<r) ret=merge(query(x<<1,l,r,L,mid),query(x<<1|1,l,r,mid+1,R));
    else if (l<=mid) ret=query(x<<1,l,r,L,mid);
    else if (mid<r) ret=query(x<<1|1,l,r,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
    // printf("x=%d; l=%d(%d); r=%d(%d); maxlen=%d; same=%d\n",x,ret.lv,ret.l_len,ret.rv,ret.r_len,ret.maxlen_1,ret.same);
    return ret;
}
char s[maxn];
int main() {
    int n,q;
    scanf("%d%d",&n,&q);
    scanf("%s",s+1);
    FOR_(i,1,n) update(1,i,i,1,n);
    FOR_(i,1,n) update(1,i,i,1,n);
    FOR_(i,1,n) if (s[i]=='1') update(1,i,i,1,n);
    FOR_(i,1,q) {
        int c,l,r;
        scanf("%d%d%d",&c,&l,&r);
        if (c==1) update(1,l,r,1,n);
        else printf("%d\n",query(1,l,r,1,n).maxlen_1);
    }
}
/*
7 100
1101110
2 1 7
2 2 4
1 3 6
2 5 6
1 4 7
2 1 7


7 100
1010101
1 4 7
2 1 2
2 1 3
*/