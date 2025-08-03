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

int vise[maxn],vis[maxn];
vector<pii> edge[maxn];
vector<int> ee;
void dfs(int x) {
    if (vis[x]) return; vis[x]=1;
    for (auto p:edge[x]) {
        int v=p.first,id=p.second;
        if (vise[id]) continue; vise[id]=1;
        ee.push_back(v);
        dfs(v);
        ee.push_back(x);
    }
}
vector<string> A,B;
vector<int> val[2];
int main() {
    int i,n,k;
    scanf("%d",&n);
    FOR(i,1,n*2) edge[i].clear();
    FOR(i,1,n) {
        int u,v; scanf("%d%d",&u,&v);
        edge[u].push_back({v,i});
        edge[v].push_back({u,i});
    }
    FOR(i,1,n*2) {
        ee.clear(); dfs(i);
        if (ee.size()==0) continue;
        if (ee.size()==2) return 0*puts("-1");
        // for (int v:ee) printf("%d ",v); puts("<- v");
        int sz=ee.size()/2,k;
        REP(k,sz) val[0].push_back(ee[k]);
        rrep(k,sz,sz*2) val[1].push_back(ee[k]);
        A.push_back("LR");
        REP(k,(sz-1)/2) A.push_back("UU"),A.push_back("DD");
        REP(k,sz/2) B.push_back("UU"),B.push_back("DD");
        if (!(sz&1)) A.push_back("LR");
        else B.push_back("LR");
    }
    printf("%d 2\n",n);
    puts("");
    REP(i,n) printf("%d %d\n",val[0][i],val[1][i]);
    puts("");
    for (auto s:A) cout<<s<<"\n";
    puts("");
    for (auto s:B) cout<<s<<"\n";
}
/*
*/