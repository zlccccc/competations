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

int h;
int fa[maxn],val[maxn];
int getfa(int x) {
    if (fa[x]==x) return x;
    int xf=getfa(fa[x]);
    if (fa[x]!=xf) val[x]=(val[x]+val[fa[x]])%h;
    fa[x]=xf; return xf;
}
bool merge(int u,int v,int chk) { // val[u]-val[v]=chk
    int x=getfa(u),y=getfa(v);
    // printf("merge %d %d; check=%d; x,y=%d %d; val=%d %d\n",u,v,chk,x,y,val[u],val[v]);
    if (x==y) {
        return chk==(val[v]-val[u]+h)%h;
    } else {
        fa[y]=x; val[y]=(chk-val[v]+h)%h;
        return 1;
    }
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,m,i,j;
        scanf("%d%d%d",&n,&m,&h);
        vector<vector<int>> A(n+1,vector<int>(m+1));
        vector<int> prex(n+1),prey(m+1);
        FOR(i,1,n) FOR(j,1,m) scanf("%d",&A[i][j]);
        FOR(i,1,n+m) fa[i]=i,val[i]=0;
        int ans=1;
        FOR(i,1,n) FOR(j,1,m) if (A[i][j]!=-1) {
            ans&=merge(i,j+n,A[i][j]);
            // // printf("i,j=%d %d\n",i,j);
            // // printf("1 ans=%d\n",ans);
            // if (prex[i]) ans&=merge(prex[i]+n,j+n,(A[i][j]-A[i][prex[i]]+h)%h);
            // prex[i]=j;
            // // printf("2 ans=%d\n",ans);
            // if (prey[j]) ans&=merge(prey[j],i,(A[i][j]-A[prey[j]][j]+h)%h);
            // prey[j]=i;
            // // printf("3 ans=%d\n",ans);
        }
        if (!ans) puts("0");
        else {
            int cnt=0;
            FOR(i,1,n+m) if (getfa(i)==i) cnt++;
            printf("%lld\n",powMM(h,cnt-1));
        }
    }
}
/*
1
4 5 1024
1 -1 -1 -1 -1
-1 -1 -1 1000 -1
-1 -1 -1 -1 69
420 -1 -1 999 -1


1
4 4 100
1 2 3 4
5 6 7 8
10 11 12 13
-1 -1 -1 -1
*/