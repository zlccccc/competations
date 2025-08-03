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

int fa[maxn];
inline int getfa(int x) { //left
    // if (!x) return x;
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}

vector<pii> E[maxn];
ll A[maxn],B[maxn]; // A/B: sum; C:inib
int n;
queue<pii> Q; // check
void check(int l,int r) {
    // printf("solve %d %d: %d %d\n",l,r,getfa(l-1),getfa(r));
    if (getfa(l-1)==getfa(r)) return; // merged
    if (A[getfa(l-1)]||A[getfa(r)]) return; // must zero
    Q.push({l,r});
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,m,i;
        scanf("%d%d",&n,&m);
        FOR(i,1,n) scanf("%lld",&A[i]);
        FOR(i,1,n) scanf("%lld",&B[i]),A[i]-=B[i];
        FOR(i,1,n) A[i]+=A[i-1];
        FOR(i,1,n) fa[i]=i;
        FOR(i,1,n) E[i].clear();
        FOR(i,1,m) {
            int l,r;
            scanf("%d%d",&l,&r);
            check(l,r);
            E[r].push_back({l,r});
            E[l-1].push_back({l,r});
        }
        while (Q.size()) {
            auto p=Q.front(); Q.pop();
            int l=p.first,r=p.second;
            // printf("solve %d %d\n",l,r);
            vector<int> chk;
            for (int k=r;k>=l;k=getfa(k)) {
                fa[k]=k-1; chk.push_back(k);
            }
            for (int k:chk) for (auto p:E[k]) check(p.first,p.second);
        }
        FOR(i,1,n) A[i]=A[getfa(i)];
        bool ans=1;
        FOR(i,1,n) if (A[i]) ans=0;
        if (ans) puts("YES");
        else puts("NO");
    }
}
/*
5 4
4 3 2 1
*/