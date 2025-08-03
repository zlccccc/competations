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

int n,m,k;
vector<pair<int,pii> > Q;
int V[1007][1007],U[1007][1007],R[1007][1007];
bool check(int val) {
    int i,j;
    FOR(i,1,n) FOR(j,1,m) V[i][j]=0;
    for (auto now:Q) if (now.first<=val)
        V[now.second.first][now.second.second]=1;
    FOR(i,1,n) FOR(j,1,m) if (V[i][j]) U[i][j]=U[i-1][j]+1; else U[i][j]=0;
    FOR(i,1,n) FOR(j,1,m) if (U[i][j]>=k) R[i][j]=R[i][j-1]+1; else R[i][j]=0;
    // printf("val=%d\n",val);
    // FOR(i,1,n) FOR(j,1,m) printf("%d%c",V[i][j]," \n"[j==m]);
    // FOR(i,1,n) FOR(j,1,m) printf("%d%c",U[i][j]," \n"[j==m]);
    // FOR(i,1,n) FOR(j,1,m) printf("%d%c",R[i][j]," \n"[j==m]);
    FOR(i,1,n) FOR(j,1,m) if (R[i][j]>=k) return 1;
    return 0;
}
int main() {
    int q,i;
    scanf("%d%d%d%d",&n,&m,&k,&q);
    while (q--) {
        int x,y,t;
        scanf("%d%d%d",&x,&y,&t);
        Q.push_back({t,{x,y}});
    }
    int l=-1,r=INF;
    while (l+1<r) {
        int mid=(r-l)/2+l;
        if (check(mid)) r=mid;
        else l=mid;
    }
    if (r==INF) puts("-1");
    else printf("%d\n",r);
}
/*
2 3 2 5
2 1 0
2 2 0
1 2 0
1 3 0
2 3 0
*/