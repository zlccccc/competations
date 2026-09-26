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
#include <functional>
#include <random>
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
// const LL M=585698298;
// const LL M=998244353;
const LL M=1e9+7;
// ll M=1;
const LL maxn=2e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

vector<int> edge[maxn];
int dist[maxn],B2[maxn]; // b2: two b item
int P[maxn],B[maxn]; // p,b; todo bfs b
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,m,i;
        scanf("%d%d",&n,&m);
        int p,b,x;
        scanf("%d%d",&p,&b);
        FOR(i,1,n) P[i]=B[i]=0;
        FOR(i,1,p) scanf("%d",&x),P[x]=1;
        FOR(i,1,b) scanf("%d",&x),B[x]=1;
        FOR(i,1,n) edge[i].clear();
        FOR(i,1,m) {
            int u,v; scanf("%d%d",&u,&v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        queue<int> Q;
        FOR(i,1,n) dist[i]=INF;
        Q.push(1); dist[1]=0;
        while (Q.size()) {
            int x=Q.front(); Q.pop();
            for (int v:edge[x]) {
                if (dist[v]!=INF) continue;
                dist[v]=dist[x]+1;
                if (B[v]) Q.push(v); // cannot move immediately
            }
        }
        FOR(i,1,n) B2[i]=0;
        FOR(i,1,n) if (B[i]) { // two B
            for (int v:edge[i]) if (B[v]) B2[i]=1;
        }
        int c1=0,c2=0;
        FOR(i,1,n) if (P[i]) { // two B
            bool b1=0,b2=0;
            for (int v:edge[i]) {
                if (B[v]) b1=1;
                if (B2[v]) b2=1;
            }
            if (b2) c2++;
            else if (b1) c1++;
        }
        bool ans=0;
        FOR(i,1,n) if (P[i]&&dist[i]!=INF) { // two B
            bool b1=0,b2=0;
            for (int v:edge[i]) {
                if (B[v]) b1=1;
                if (B2[v]) b2=1;
            }
            if (b2) c2--;
            else if (b1) c1--;
            if (c2||dist[i]-1<=c1) ans=1;
            if (b2) c2++;
            else if (b1) c1++;
        }
        if (ans) puts("YES"); else puts("NO");
    }
}
/*
*/