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

vector<int> V[maxn];
// swap-value: only!
int n,m;
int ax[5]={0,0,1,-1,0},ay[5]={1,-1,0,0,0};
int ban(int x,int y) {
    // printf("ban %d %d\n",x,y);
    if (x<1||x>n||y<1||y>m) return 0;
    int i;
    if (V[x][y]==1) return 0;
    REP(i,4) if (V[x][y]>V[x+ax[i]][y+ay[i]]) return 0;
    return 1;
}
vector<pii> NotOK;
int main() {
    int i,j;
    scanf("%d%d",&n,&m);
    V[0].resize(m+2,INF);
    FOR(i,1,n) {
        V[i].resize(m+2,INF);
        FOR(j,1,m) scanf("%d",&V[i][j]);
    } V[n+1].resize(m+2,INF);
    int o,oo;
    FOR(i,1,n) FOR(j,1,m) if (ban(i,j)) NotOK.push_back({i,j});
    if (NotOK.size()==0) return 0*puts("0");
    if (NotOK.size()>6) return 0*puts("2");
    set<ar4> ans;
    for (auto p:NotOK) {
        REP(o,5) {
            int x=p.first+ax[o],y=p.second+ay[o];
            if (x<1||x>n||y<1||y>m) continue;
            // printf("x,y=%d %d\n",x,y);
            FOR(i,1,n) FOR(j,1,m) {
                bool okay=1;
                swap(V[x][y],V[i][j]);
                for (auto p:NotOK) if (ban(p.first,p.second)) okay=0;
                REP(oo,5) if (ban(x+ax[oo],y+ay[oo])) okay=0;
                REP(oo,5) if (ban(i+ax[oo],j+ay[oo])) okay=0;
                swap(V[x][y],V[i][j]);
                ar4 ins={i,j,x,y};
                if (make_pair(ins[0],ins[1])>make_pair(ins[2],ins[3])) swap(ins[0],ins[2]),swap(ins[1],ins[3]);
                if (okay) ans.insert(ins);
            }
        }
    }
    if (ans.size()) printf("1 %d\n",ans.size());
    else puts("2");
}
/*
*/