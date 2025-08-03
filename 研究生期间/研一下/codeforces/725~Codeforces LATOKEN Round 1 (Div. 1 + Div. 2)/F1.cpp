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

vector<int> edge[maxn];
int dfn[maxn],low[maxn],tot;
bool vis[maxn];//instack
int S[maxn],top;
int id[maxn],cnt;
void tarjan(int x,int fa) {
    low[x]=dfn[x]=++tot;
    S[++top]=x;
    vis[x]=1;
    for(int v:edge[x]) {
        if(!dfn[v]) {
            tarjan(v,x);
            low[x]=min(low[x],low[v]);
        } else if(vis[v])
            low[x]=min(low[x],dfn[v]);
    }
    if(low[x]==dfn[x]) {
        cnt++;
        while(1) {
            int now=S[top--];
            vis[now]=0; id[now]=cnt;
            if(now==x) break;
        }
    }
}
int n,m;
char s[maxn],str[maxn];
int A[maxn],idx[maxn];//idx:down-idx
inline int getid(int x,int y) {
    return x*(m+1)+y;
}
int C0=0;
int du[maxn];
int main() {
    int i,j;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) {
        scanf("%s",str+1);
        FOR(j,1,m) s[getid(i,j)]=str[j];
    }
    FOR(i,1,m) scanf("%d",&A[i]);
    FOR(j,1,m) rFOR(i,1,n) {
        idx[getid(i,j)]=idx[getid(i+1,j)];
        if (s[getid(i,j)]=='#'&&A[j]) idx[getid(i,j)]=++C0,A[j]--;
        // printf("chk %d %d: %c; id=%d, C0=%d\n",i,j,s[getid(i,j)],idx[getid(i,j)],C0);
    }
    FOR(j,1,m) rFOR(i,1,n) if (s[getid(i,j)]=='#'&&idx[getid(i,j)]!=idx[getid(i+1,j)]) {
        int x=idx[getid(i,j)];
        if (idx[getid(i+1,j)]) edge[x].push_back(idx[getid(i+1,j)]);
        if (idx[getid(i,j+1)]) edge[x].push_back(idx[getid(i,j+1)]);
        if (idx[getid(i,j-1)]) edge[x].push_back(idx[getid(i,j-1)]);
        if (idx[getid(i-1,j)]&&idx[getid(i-1,j)]!=idx[getid(i,j)]) edge[x].push_back(idx[getid(i-1,j)]);
        // printf("solve %d ",x);
        // for (int v:edge[x]) printf("%d ",v); puts("<- edge");
    }
    FOR(i,1,C0) if (!dfn[i]) tarjan(i,0);
    // FOR(i,1,n) FOR(j,1,m) printf("%2d%c",idx[getid(i,j)]," \n"[j==m]); puts("<- first id");
    FOR(i,1,n) FOR(j,1,m) idx[getid(i,j)]=id[idx[getid(i,j)]];
    // FOR(i,1,n) FOR(j,1,m) printf("%2d%c",idx[getid(i,j)]," \n"[j==m]);
    FOR(i,1,C0) {
        // for (int v:edge[i]) printf("%d->%d: %d->%d\n",i,v,id[i],id[v]);
        for (int v:edge[i]) if (id[v]!=id[i]) du[id[v]]++;
    }
    int ans=0;
    FOR(i,1,cnt) if (du[i]==0) ans++;
    printf("%d\n",ans);
}
/*
*/