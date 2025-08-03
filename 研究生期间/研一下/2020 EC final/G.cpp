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

int rev[maxn*4];
int val[maxn*4][2];
// int sumv[maxn*4][2];
ll sum[maxn*4];
int downk[maxn*4][2];
void update(int x) {
    int l=x<<1,r=x<<1|1;
    rev[x]=0; downk[x][0]=downk[x][1]=0;
    val[x][0]=val[l][0]+val[r][0];
    val[x][1]=val[l][1]+val[r][1];
    // sumv[x][0]=sumv[l][0]+sumv[r][0];
    // sumv[x][1]=sumv[l][1]+sumv[r][1];
    sum[x]=sum[l]+sum[r];
}
void build(int x,int l,int r) {
    if (l==r) {val[x][0]=1; return;}
    int mid=(l+r)/2;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    update(x);
}
void upd(int x,int rev_,int val_0,int val_1) {//rev -> add
    if (rev_) {
        rev[x]^=1;
        swap(val[x][0],val[x][1]);
        // swap(sumv[x][0],sumv[x][1]);
        // swap(sum[x][0],sum[x][1]);
        swap(downk[x][0],downk[x][1]);
    }
    downk[x][0]+=val_0;
    downk[x][1]+=val_1;
    sum[x]+=(ll)val[x][0]*val_0;
    sum[x]+=(ll)val[x][1]*val_1;
}
ll update(int x,int l,int r,int op,int L,int R) {
    if (l<=L&&R<=r) {
        if (op==0) upd(x,1,0,0);
        if (op==1) upd(x,0,0,1);
        if (op==2) return sum[x];
        return 0;
    } int mid=(L+R)/2; ll ret=0;
    upd(x<<1,rev[x],downk[x][0],downk[x][1]);
    upd(x<<1|1,rev[x],downk[x][0],downk[x][1]);
    if (l<=mid) ret+=update(x<<1,l,r,op,L,mid);
    if (mid<r) ret+=update(x<<1|1,l,r,op,mid+1,R);
    update(x);
    return ret;
}
void print(int x,int l,int r) {
    if (l==r) return;
    int mid=(l+r)/2;
    upd(x<<1,rev[x],downk[x][0],downk[x][1]);
    upd(x<<1|1,rev[x],downk[x][0],downk[x][1]);
    print(x<<1,l,mid);
    print(x<<1|1,mid+1,r);
    update(x);
    printf("%d: [%d-%d]  sum=%lld; val=%d %d, downk=%d %d\n",x,l,r,
        sum[x],val[x][0],val[x][1],downk[x][0],downk[x][1]);
}
int A[maxn],pos[maxn];
ll Ans[maxn];
vector<pii> Q[maxn];
int main() {
    int n,i;
    scanf("%d",&n);
    FOR(i,1,n) {
        int x; scanf("%d",&x);
        A[i]=pos[x]; pos[x]=i;
    } int q; scanf("%d",&q);
    // FOR(i,1,n) printf("%d\n",A[i]);
    FOR(i,1,q) {
        int l,r;
        scanf("%d%d",&l,&r);
        Q[r].push_back(make_pair(l,i));
    } build(1,1,n);
    FOR(i,1,n) {
        update(1,A[i]+1,i,0,1,n);
        update(1,1,i,1,1,n);
        // print(1,1,n); puts("");
        for (pii p:Q[i]) Ans[p.second]=update(1,p.first,i,2,1,n);
    }
    FOR(i,1,q) printf("%lld\n",Ans[i]);
}
/*
owowohahah
wohahah
oohaha
hahaha
anmomomomomomo
abcdcdcdcdcdcd
*/