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

int n,m;
int ans=0,cnt=0;
char str[1007][1007];
inline int getid(int x,int y) {
    return x+(y-1)*n;
}
int main() {
    int q,i,j;
    scanf("%d%d%d",&n,&m,&q);;
    FOR(i,1,n) scanf("%s",str[i]+1);
    FOR(i,1,n) FOR(j,1,m) str[i][j]=(str[i][j]=='*');
    FOR(i,1,n) FOR(j,1,m) cnt+=str[i][j];
    FOR(i,1,n) FOR(j,1,m) ans+=(str[i][j]!=(getid(i,j)<=cnt));
    // FOR(i,1,n) FOR(j,1,m) printf("%d%c",str[i][j]," \n"[j==m]);
    // FOR(i,1,n) FOR(j,1,m) printf("%d%c",getid(i,j)," \n"[j==m]);
    // printf("cnt=%d\n",cnt);
    // printf("%d\n",ans);
    while (q--) {
        scanf("%d%d",&i,&j);
        int x,y;
        if (str[i][j]==1) y=(cnt+n-1)/n,x=cnt-(y-1)*n;
        else y=(cnt+n-1+1)/n,x=cnt+1-(y-1)*n;
        ans-=(str[i][j]!=(getid(i,j)<=cnt));
        ans-=(str[x][y]!=(getid(x,y)<=cnt));
        cnt-=str[i][j]; str[i][j]^=1; cnt+=str[i][j];
        // printf("x=%d; y=%d\n",x,y);
        ans+=(str[i][j]!=(getid(i,j)<=cnt));
        ans+=(str[x][y]!=(getid(x,y)<=cnt));
        printf("%d\n",ans/2);
    }
}
/*
*/