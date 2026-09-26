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

int A[57][57],val[57][57];
int MAX[57][57];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        int n,m,i,j,x,y;
        scanf("%d%d",&n,&m);
        FOR(i,1,n) FOR(j,1,m) scanf("%d",&A[i][j]);
        memset(MAX,0x3f,sizeof(MAX));
        FOR(i,1,n) FOR(j,1,m) {
            FOR(x,0,n) FOR(y,0,m) val[x][y]=-INF;
            FOR(x,i,n) FOR(y,j,m) val[x][y]=A[x][y];
            FOR(x,i,n) FOR(y,j,m) max_(val[x][y],val[x][y-1]);
            FOR(x,i,n) FOR(y,j,m) max_(val[x][y],val[x-1][y]);
            FOR(x,i,n) FOR(y,j,m) min_(MAX[x-i+1][y-j+1],val[x][y]);
        }
        int ans=n*m;
        FOR(i,1,n) FOR(j,1,m) if (MAX[i][j]==MAX[n][m]) {
            // printf("%d-%d: %d\n",i,j,MAX[i][j]);
            min_(ans,i*j);
        }
        printf("%d\n",ans);
    }
}
/*
*/