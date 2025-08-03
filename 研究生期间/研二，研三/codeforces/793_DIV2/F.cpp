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

int n;
ll cnt[maxn],sum[maxn];
inline int lowbit(int x) {return x&-x;}
void update(int x,ll k,ll val) {
    k%=M; val%=M; val+=M; val%=M; val*=k; val%=M;
    for (;x<=n;x+=lowbit(x)) add_(cnt[x],k),add_(sum[x],val);
}
pll query(int x) {
    pll ret={0,0};
    for (;x;x-=lowbit(x)) add_(ret.first,cnt[x]),add_(ret.second,sum[x]);
    return ret;
}
pll query(int l,int r) {
    pll pl=query(l-1),pr=query(r);
    return {pr.first-pl.first,pr.second-pl.second};
}
ll A[maxn],B[maxn];
vector<ll> Val;
int idx[maxn];
vector<pii> Q[maxn];
int ans[maxn];
int main() {
    int q,i;
    scanf("%d",&n);
    scanf("%d",&q);
    FOR(i,1,n) scanf("%lld",&A[i]);
    FOR(i,1,n) scanf("%lld",&B[i]);
    FOR(i,1,n) A[i]=A[i+1]-A[i],B[i]+=B[i-1],Val.push_back(B[i]);
    sort(Val.begin(),Val.end());
    Val.erase(unique(Val.begin(),Val.end()),Val.end());
    FOR(i,1,n) idx[i]=lower_bound(Val.begin(),Val.end(),B[i])-Val.begin()+1;
    // (A[i]-A[i-1])*abs(val-\sum(B[i]))
    FOR(i,1,q) {
        int l,r; scanf("%d%d",&l,&r);
        assert(B[r]-B[l-1]==0);
        Q[l-1].push_back({i,r});
        Q[r].push_back({i,r});
    }
    FOR(i,1,n) {
        update(idx[i],A[i],B[i]);
        for (auto p:Q[i]) {
            int id=p.first,r=p.second;
            int now=0; pll pp;
            pp=query(idx[r]);
            add_(now,(M+(pp.first*(B[r]%M)-pp.second)%M)%M);
            pp=query(idx[r],n);
            add_(now,(M-(pp.first*(B[r]%M)-pp.second)%M)%M);
            if (i==r) add_(ans[id],now); else add_(ans[id],M-now);
        }
    }
    FOR(i,1,q) printf("%d\n",ans[i]);
}
/*
*/