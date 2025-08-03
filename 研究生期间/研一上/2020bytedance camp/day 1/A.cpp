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
const LL maxn=1007+107;
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

int A[maxn],pos[maxn];
set<int> edge[maxn];
bool mark[maxn],okay;
int S[maxn],top;
void dfs(int x) {
    S[top++]=x; mark[x]=1;
    if (A[x]==S[0]) {okay=1; return;}
    for (int v:edge[x]) {
        if (!mark[v]) dfs(v);
        if (okay) return;
    } top--;
}
vector<pii> ans;
int main() {
    int n,i,j;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]),pos[A[i]]=i;
    int m; scanf("%d",&m);
    FOR(i,1,m) {
        int u,v; scanf("%d%d",&u,&v);
        edge[u].insert(v);
        edge[v].insert(u);
    }
    FOR(i,1,n) {
        int MAX=0;
        FOR(j,1,n) if (A[j]!=j&&(!MAX||edge[MAX].size()>edge[j].size())) MAX=j;
        FOR(j,1,n) mark[j]=0; top=0; okay=0;
        if (!MAX) break;
        dfs(MAX); top--;
        // printf("doit %d ",MAX); puts("");
        rFOR(j,1,top) {
            ans.push_back(make_pair(S[j-1],S[j]));
            swap(A[S[j-1]],A[S[j]]);
            // printf("swap %d %d\n",S[j-1],S[j]);
        } for (auto now:edge[MAX]) edge[now].erase(MAX);
        // FOR(j,1,n) printf("%d ",A[j]); puts("");
        edge[MAX].clear();
    }
    FOR(i,1,n) {
        if (A[i]!=i) return 0*puts("-1");
    }
    printf("%d\n",(int)ans.size());
    for (auto now:ans) printf("%d %d\n",now.first,now.second);
}
/*
4
3 4 2 1
4
1 2
2 3
3 4
4 1

4
1 3 4 2
2
2 1
2 3
*/