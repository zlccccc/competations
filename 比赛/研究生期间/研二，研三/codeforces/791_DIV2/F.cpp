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

int ban[17],mask[17];
int Ans[50007][1024]; // 1024:ban
int main() {
    int n,m;
    int i,j,k;
    scanf("%d%d",&n,&m);
    FOR(i,1,m) {
        int u,v; scanf("%d%d",&u,&v);
        ban[u]|=1<<v;
        ban[v]|=1<<u;
    }
    mask[0]=0; //lt
    rep(i,1,10) mask[i]=mask[i-1]|(1<<(i-1));
    FOR(i,1,n) {
        if (i==1) {
            FOR(j,0,9) {
                Ans[i][ban[j]&mask[j]]+=1;
            }
        } else {
            REP(k,1024) if (Ans[i-1][k]) { // 后面不能接
                FOR(j,0,9) if (!((k>>j)&1)) { // not ban
                    add_(Ans[i][(ban[j]&mask[j])|(k&ban[j])],Ans[i-1][k]);
                }
            }
        }
    }
    int ans=0;
    REP(k,1024) add_(ans,Ans[n][k]);
    printf("%d\n",ans);
}
/*
*/