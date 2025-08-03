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
vector<int> inside[maxn];
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
            inside[cnt].push_back(now);
            if(now==x) break;
        }
    }
}
int n,m;
bool mark[maxn]; //vis
char s[maxn],str[maxn];
int A[maxn],idx[maxn],idy[maxn];//idx:down-idx
inline int getid(int x,int y) {
    if (x<1||x>n||y<1||y>m) return 0;
    return (x-1)*m+y;
}
void dfs(int x,int y) {
    if (mark[getid(x,y)]) return;
    mark[getid(x,y)]=1;
    if (s[getid(x-1,y)]=='#') dfs(x-1,y);
    if (s[getid(x,y-1)]=='#') dfs(x,y-1);
    if (s[getid(x,y+1)]=='#') dfs(x,y+1);
    if (x!=n) dfs(x+1,y);
}
int C0=0,C1=0,C2=0;
int du[maxn];
int mrk[maxn],L[maxn],R[maxn];
vector<int> P[maxn];
int main() {
    int i,j;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) {
        scanf("%s",str+1);
        FOR(j,1,m) s[getid(i,j)]=str[j];
    }
    FOR(i,1,m) scanf("%d",&A[i]);
    FOR(j,1,m) rFOR(i,1,n) {
        if (s[getid(i,j)]=='#'&&A[j]) dfs(i,j),A[j]--;
        // printf("chk %d %d: %c; id=%d, C0=%d\n",i,j,s[getid(i,j)],idx[getid(i,j)],C0);
    }
    FOR(j,1,m) rFOR(i,1,n) {
        idx[getid(i,j)]=idx[getid(i+1,j)];
        if (s[getid(i,j)]=='#'&&mark[getid(i,j)]) idx[getid(i,j)]=++C0;
        // printf("chk %d %d: %c; id=%d, C0=%d\n",i,j,s[getid(i,j)],idx[getid(i,j)],C0);
    }
    FOR(j,1,m) rFOR(i,1,n) if (s[getid(i,j)]=='#'&&idx[getid(i,j)]!=idx[getid(i+1,j)]) {
        int x=idx[getid(i,j)];
        if (idx[getid(i+1,j)]) edge[x].push_back(idx[getid(i+1,j)]);
        if (idx[getid(i,j+1)]) edge[x].push_back(idx[getid(i,j+1)]);
        if (idx[getid(i,j-1)]) edge[x].push_back(idx[getid(i,j-1)]);
        if (s[getid(i-1,j)]=='#'&&idx[getid(i-1,j)]!=idx[getid(i,j)]) edge[x].push_back(idx[getid(i-1,j)]);
        // printf("solve %d ",x);
        // for (int v:edge[x]) printf("%d ",v); puts("<- edge");
    }
    // FOR(i,1,n) FOR(j,1,m) printf("%2d%c",mark[getid(i,j)]," \n"[j==m]); puts("<- id mask");
    // FOR(i,1,n) FOR(j,1,m) printf("%2d%c",idx[getid(i,j)]," \n"[j==m]); puts("<- first id");
    // printf("%d\n",C1); //first
    FOR(i,1,C0) if (!dfn[i]) tarjan(i,0);
    // FOR(i,1,n) FOR(j,1,m) printf("%2d%c",id[idx[getid(i,j)]]," \n"[j==m]); puts("<- first dfn id");
    FOR(i,1,n) FOR(j,1,m) idx[getid(i,j)]=id[idx[getid(i,j)]];
    // FOR(i,1,n) FOR(j,1,m) printf("%2d%c",idx[getid(i,j)]," \n"[j==m]);
    FOR(i,1,C0) {
        // for (int v:edge[i]) printf("%d->%d: %d->%d\n",i,v,id[i],id[v]);
        for (int v:edge[i]) if (id[v]!=id[i]) du[id[v]]++;
    }
    FOR(i,1,C0) edge[i].clear(),inside[i].clear();
    FOR(i,1,cnt) if (du[i]==0) mrk[i]=++C1; C2=C1;//should-cover
    //solve-2
    FOR(j,1,m) rFOR(i,1,n) {
        idy[getid(i,j)]=idy[getid(i+1,j)];
        if (s[getid(i,j)]=='#') {
            if (mrk[idx[getid(i,j)]]&&idx[getid(i,j)]!=idx[getid(i+1,j)])
                idy[getid(i,j)]=mrk[idx[getid(i,j)]];
            else idy[getid(i,j)]=++C2;
        }
    }
    FOR(j,1,m) rFOR(i,1,n) if (s[getid(i,j)]=='#') {
        int x=idy[getid(i,j)];
        if (idy[getid(i+1,j)]) edge[x].push_back(idy[getid(i+1,j)]);
        if (idy[getid(i,j+1)]) edge[x].push_back(idy[getid(i,j+1)]);
        if (idy[getid(i,j-1)]) edge[x].push_back(idy[getid(i,j-1)]);
        if (s[getid(i-1,j)]=='#'&&idy[getid(i-1,j)]!=idy[getid(i,j)]) edge[x].push_back(idy[getid(i-1,j)]);
        // printf("solve %d ",x);
        // for (int v:edge[x]) printf("%d ",v); puts("<- edge");
    }
    FOR(i,1,C2) dfn[i]=id[i]=low[i]=0,vis[i]=0; tot=0; cnt=0; top=0;
    FOR(i,1,C2) if (!dfn[i]) tarjan(i,0);\
    // FOR(i,1,n) FOR(j,1,m) printf("%2d%c",mark[getid(i,j)]," \n"[j==m]); puts("<- second mask");
    // FOR(i,1,n) FOR(j,1,m) printf("%2d%c",idy[getid(i,j)]," \n"[j==m]); puts("<- second id");
    // FOR(i,1,n) FOR(j,1,m) printf("%2d%c",id[idy[getid(i,j)]]," \n"[j==m]); puts("<- third id");
    FOR(i,1,cnt) L[i]=INF,R[i]=-INF; 
    FOR(i,1,C1) min_(L[id[i]],i),max_(R[id[i]],i);
    FOR(i,1,cnt) {
        for (int x:inside[i]) for (int v:edge[x]) {
            min_(L[i],L[id[v]]);
            max_(R[i],R[id[v]]);
            // printf("%d->%d: %d %d\n",x,v,i,id[v]);
        }
        // printf("i=%d: ans=%d %d\n",i,L[i],R[i]);
        if (L[i]!=INF) P[L[i]].push_back(R[i]);
        // printf("%d->%d\n",L[i],R[i]);
    }
    int nxtr=0,r=0,ans=0;
    FOR(i,1,C1) {
        for (int v:P[i]) nxtr=max(nxtr,v);
        if (r<i) r=nxtr,ans++;
    } printf("%d\n",ans);
}
/*
5 7
#....#.
.#.#...
.....#.
#....##
#.#....
2 0 1 0 0 3 1

3 10
#...#...#.
...#.###..
#.#......#
1 0 1 0 0 1 0 0 0 1


3 10
#...#...#.
...#.###..
#.#.#....#
1 0 1 0 1 0 0 0 0 1

*/