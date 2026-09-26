#include <bits/stdc++.h>
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
typedef array<int,3> ar3;
typedef array<int,4> ar4;
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

int A[maxn];
int MAX[maxn*4],MIN[maxn*4],Pos[maxn];
void build(int x,int L,int R) {
    MAX[x]=MIN[x]=A[L]; Pos[A[L]]=L;
    if (L==R) return;
    int mid=(L+R)/2;
    build(x<<1,L,mid); build(x<<1|1,mid+1,R);
    MAX[x]=max(MAX[x<<1],MAX[x<<1|1]);
    MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
}
pii merge(pii l,pii r) {
    return make_pair(min(l.first,r.first),max(l.second,r.second));
}
inline pii query(int x,int l,int r,int L,int R) {
    // printf("query %d %d %d %d %d\n",x,l,r,L,R);
    if (l<=L&&R<=r) return make_pair(MIN[x],MAX[x]);
    pii ret=make_pair(INF,-INF);
    int mid=(L+R)/2;
    if (l<=mid) ret=merge(ret,query(x<<1,l,r,L,mid));
    if (mid<r) ret=merge(ret,query(x<<1|1,l,r,mid+1,R));
    return ret;
}
int n;
int query(int l,int r) {
    // printf("Query %d %d\n",l,r);
    if (l==r) return 0;
    if (l+1==r) return 1;
    pii Q=query(1,l,r,1,n);
    int x=Pos[Q.first],y=Pos[Q.second];
    if (x>y) swap(x,y);
    // printf("min and max pos = %d %d\n",x,y);
    return query(l,x)+1+query(y,r);
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i;
        scanf("%d",&n);
        FOR(i,1,n) scanf("%d",&A[i]);
        build(1,1,n);
        printf("%d\n",query(1,n));
    }
}
/*
*/