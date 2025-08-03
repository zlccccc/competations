#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
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

int fa[3007];
int getfa(int x) {
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
int c[3007],p[3007],r[3007];
pii dis[3007][3007];
int A[3007][3];
set<pii> Q; // (dis,i,j)
int main() {
    int n,m,k,i,j;
    scanf("%d%d",&n,&k);
    FOR(i,1,k) c[i]=0;
    FOR(i,k+1,n) scanf("%d",&c[i]);
    FOR(i,1,n) scanf("%d%d%d",&A[i][0],&A[i][1],&A[i][2]);
    FOR(i,1,n) {
        FOR(j,1,n) {
            REP(k,3) dis[i][j].first+=(A[i][k]-A[j][k])*(A[i][k]-A[j][k]);
            dis[i][j].second=j;
        }
        sort(dis[i]+1,dis[i]+1+n);
    }
    int o;
    FOR(i,1,n) fa[i]=i;
    FOR(i,1,n) p[i]=1;
    FOR(o,2,n) {
        int minv=INF,x=0,y=0;
        FOR(i,1,n) {
            while (getfa(i)==getfa(dis[i][p[i]].second)) p[i]++;
            // printf("%d - p=%d\n",i,p[i]);
            if (dis[i][p[i]].first<minv) x=i,y=dis[i][p[i]].second,minv=dis[i][p[i]].first;
        }
        fa[getfa(x)]=getfa(y);
        r[o]=min(INF,r[o-1]+minv);
        // printf("%d-%d: %d\n",x,y,minv);
    }
    int ans=INF;
    // FOR(i,1,n) printf("%d ",c[i]); puts("<- c");
    // FOR(i,1,n) printf("%d ",r[i]); puts("<- r");
    // FOR(i,0,n) printf("%d ",c[i]+r[n-i+1]); puts("<- all");
    FOR(i,1,n) ans=min(ans,c[i]+r[n-i+1]);
    printf("%d\n",ans);
}
/*
*/