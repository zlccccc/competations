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

//r to rmax;
int ans=0;
int val[maxn],lz[maxn<<2];
pair<int,int> T[maxn<<2];
pii merge(pii A,pii B) {
    pii ret=min(A,B);
    if (A.first==B.first) ret.second=A.second+B.second;
    return ret;
}
void update(int x,int y) {
    T[x].first+=y; lz[x]+=y;
}
void pushdown(int x) {
    if (lz[x]) {
        update(x<<1,lz[x]);
        update(x<<1|1,lz[x]);
        lz[x]=1;
    }
}
void update(int x,int pos,int L,int R) {
    if (L==R) {T[x].second++; return;}
    int mid=(L+R)/2;
    pushdown(x);
    if (pos<=mid) update(x<<1,pos,L,mid);
    else update(x<<1|1,pos,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
void query(int x,int l,int r,int val,int L,int R) {
    if (l<=L&&R<=r) { return;}
    int mid=(L+R)/2;
    pushdown(x);
    if (l<=mid) ret=max(ret,query(x<<1,l,r,L,mid));
    if (mid<r) ret=max(ret,query(x<<1|1,l,r,mid+1,R));
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
int getpos(int x,int val,int L,int R) {
    if (L==R) return L;
    int mid=(L+R)/2;
    if (MIN[x<<1]<val) return getpos(x<<1,val,L,mid);
    return getpos(x<<1|1,val,mid+1,R);
}
int main() {
    int n,q;
    scanf("%d%d",&n,&q);
    FOR(i,1,n) {
        scanf("%d",&val[i]);
        update(1,i,1,n);
    }
    FOR(i,1,q) {
        int pos,x; scanf("%d%d",&pos,&x);
        //remove x;
        int vpos=query(1,val[pos],1,n);
        if (vpos==pos) ans--;//x updates
        val[pos]=1e7;
        update(pos,x);
        int rpos=query(1,x,1,n);
        if (rpos)
    }
}
/*
*/