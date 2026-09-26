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
const LL M=998244353;
const LL maxn=1.2e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

typedef pair<ll,int> pli;
vector<int> edge[maxn];
int A[maxn];
int mask[maxn];
pli dfs(int x,int col) {
    if (mask[x]!=-1) {
        if (mask[x]!=col) return make_pair(0,1);
        else return make_pair(0,0);
    } pli ret(A[x],0);
    mask[x]=col;
    for (int v:edge[x]) {
        pli now=dfs(v,col^1);
        ret.first-=now.first;
        ret.second|=now.second;
    } return ret;
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,m;
        int i,x;
        scanf("%d%d",&n,&m);
        FOR(i,1,n) edge[i].clear(),mask[i]=-1;
        FOR(i,1,n) A[i]=0;
        FOR(i,1,n) scanf("%d",&x),A[i]-=x;
        FOR(i,1,n) scanf("%d",&x),A[i]+=x;
        FOR(i,1,m) {
            int u,v; scanf("%d%d",&u,&v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        } bool okay=1;
        FOR(i,1,n) if (mask[i]==-1) {
            pli now=dfs(i,0);
            if (now.second&&now.first%2) okay=0;
            if (!now.second&&now.first) okay=0;
        } if (okay) puts("YES");
        else puts("NO");
    }
}
/*
*/