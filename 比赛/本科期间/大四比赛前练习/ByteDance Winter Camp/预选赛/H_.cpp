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
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
 
const __int128 inf=(__int128)1<<125;
__int128 dis[107][107],D[207][107];//count
__int128 pw2[207],base;
int acc[maxn];
int main() {
    int T,_; scanf("%d",&T);
    pw2[0]=1; int i;
    FOR(i,1,127) pw2[i]=pw2[i-1]*2;
    FOR(_,1,T){
        int i,j,k; base=pw2[102];
        scanf("%d%d%d",&n,&m,&k);
        FOR(i,1,n) acc[i]=0;
        FOR(i,1,n) FOR(j,1,n) dis[i][j]=inf;
        dis[1][1]=0;
        FOR(i,1,m){
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            min_(dis[u][v],w*base);
            min_(dis[v][u],w*base);
        } while (k--) scanf("%d",&i),acc[i]=1;
        FOR(k,1,n) FOR(i,1,n) FOR(j,1,n)
            min_(dis[i][j],dis[i][k]+dis[k][j]);
        // FOR(i,1,n) {FOR(j,1,n) printf("%f ",(double)dis[i][j]/base);puts("");}
        __int128 ans=inf; int ans2=0;//不算这个
        FOR(i,1,n) D[0][i]=dis[1][i];//不算这个
        FOR(k,0,102) {//already
            FOR(i,1,n) D[k+1][i]=inf;
            if (D[k][n]<ans) ans=D[k][n],ans2=0;
            if (D[k][n]==ans) max_(ans2,k+acc[n]);
            // printf("k=%d; %f(%f)  %d\n",k,(double)ans/base,(double)D[k][n]/base,ans2);
            // FOR(i,1,n) printf("%f ",(double)D[k][i]/base); puts("");
            FOR(i,1,n) if (acc[i]) FOR(j,1,n) if (i!=j){
                min_(D[k+1][j],D[k][i]+dis[i][j]/pw2[k+1]);
                if (acc[j]&&D[k][i]+dis[i][j]/pw2[k]<ans) ans=D[k][i]+dis[i][j]/pw2[k];
                if (acc[j]&&D[k][i]+dis[i][j]/pw2[k]==ans) ans2=40000;//INFINITE!
            }
        } printf("%.10f",(double)((__float128)ans/base));
        if (ans2>=32767) puts(" Burst!");//101
        else printf(" %d\n",ans2);
    }
}
/*
*/