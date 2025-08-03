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
const LL maxn=2e5+107;
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

// simply choose LCA is the best
int choose[maxn];
set<int> S[maxn];//merging is easy to write
vector<int> edge[maxn];
void dfs(int x,int fa) {
    for (int y:edge[x]) {
        if (y==fa) continue;
        // printf("dfs: %d->%d\n",x,y);
        dfs(y,x);
        if (S[y].size()>S[x].size()) swap(S[x],S[y]);
        for (int v:S[y]) {
            if (S[x].count(v)) choose[x]=1;
            S[x].insert(v);
        } set<int>().swap(S[y]);
    } if (choose[x]) set<int>().swap(S[x]);
    // printf("%d:\n",x);
    // for (int v:S[x]) printf("%d ",v); puts("<- idx");
}
int main() {
    int n,m,i;
    scanf("%d",&n);
    FOR(i,1,n-1) {
        int x,y; scanf("%d%d",&x,&y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    } scanf("%d",&m);
    FOR(i,1,m) {
        int x,y; scanf("%d%d",&x,&y);
        if (x==y) choose[x]=1;//2 point
        else {
            S[x].insert(i);
            S[y].insert(i);
        }
    } dfs(1,0);
    int ans=0;
    FOR(i,1,n) if (choose[i]) ans++;
    printf("%d\n",ans);
    FOR(i,1,n) if (choose[i]) printf("%d ",i);
}
/*
*/