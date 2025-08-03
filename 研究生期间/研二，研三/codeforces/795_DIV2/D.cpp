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
typedef array<ll,3> arll3;
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

int A[maxn],fa[maxn],id[maxn];//id: topo
void buildtree(int n){
    static int S[maxn],top,tot,i;
    tot=top=0;
    FOR(i,1,n){
        int now=0;
        while (top&&A[S[top]]<A[i]){
            if (now) fa[now]=S[top],id[++tot]=now;//pop
            now=S[top];  top--;
        } S[++top]=i;
        if (now) fa[now]=S[top],id[++tot]=now;//pop
    } int now=0;
    while (top){
        if (now) fa[now]=S[top],id[++tot]=now;
        now=S[top]; top--;
    } fa[now]=0; id[++tot]=now;
    reverse(id+1,id+1+n);// 变成正的
    // FOR(i,1,n) printf("%d ",fa[i]);puts("");
    // FOR(i,1,n) printf("%d ",id[i]);puts("");
    // printf("tot=%d\n",tot);
}
int son[maxn][2];
arll3 val[maxn];
arll3 merge(arll3 x,arll3 y) {
    return {max(x[0],y[0]+x[2]),max(y[1],x[1]+y[2]),x[2]+y[2]};
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,i;
        scanf("%d",&n);
        FOR(i,1,n) scanf("%d",&A[i]);
        buildtree(n);
        bool ok=1;
        FOR(i,1,n) son[i][0]=son[i][1]=0;
        rFOR(i,1,n) {
            int x=id[i],f=fa[x];
            if (x<f) son[f][0]=x;
            else son[f][1]=x;

            int l=son[x][0],r=son[x][1];
            val[x]={max(0,A[x]),max(0,A[x]),A[x]};
            if (val[l][1]+val[r][0]>0) ok=0;
            if (l) val[x]=merge(val[l],val[x]);
            if (r) val[x]=merge(val[x],val[r]);
            // printf("x=%d; l,r=%d %d; value=%lld %lld %lld; ok=%d\n",x,l,r,val[i][0],val[i][1],val[i][2],ok);
        }
        if (ok) puts("YES");
        else puts("NO");
    }
}
/*
*/