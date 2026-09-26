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
typedef array<int,3> ar3;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=5e6+107;
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

namespace T_SAT {
    const static int maxn=5e6+7;
    struct enode {
        int to,next;
        enode(int _to=0,int _next=-1):to(_to),next(_next) {};
    } edge[maxn*2];
    int head[maxn],etot;
    void addedge(int u,int v) {
        // printf("%d -> %d\n",u,v);
        edge[++etot]=enode(v,head[u]); head[u]=etot;
    }
    int dfn[maxn],low[maxn],belong[maxn];
    bool vis[maxn];
    int tot,cnt;
    int S[maxn],top;
    void dfs(int x) {
        dfn[x]=low[x]=++tot;
        S[++top]=x; vis[x]=1;
        for (int i=head[x]; ~i; i=edge[i].next) {
            int v=edge[i].to;
            if (!dfn[v]) {
                dfs(v);
                low[x]=min(low[x],low[v]);
            } else if (vis[v])
                low[x]=min(low[x],dfn[v]);
        }
        if (dfn[x]==low[x]) {
            cnt++;
            while (1) {
                int now=S[top--];
                vis[now]=0; belong[now]=cnt;
                if (now==x) break;
            }
        }
    }
    void init() {
        memset(head,-1,sizeof(head)); etot=0;
    }
    void solve(int n) {
        int i; tot=cnt=0;
        FOR(i,1,n) dfn[i]=vis[i]=0;
        FOR(i,1,n) if (!dfn[i]) dfs(i);
    }
}
// using namespace T_SAT;

vector<int> edge[maxn];
int dep[maxn],fa[maxn];
void dfs(int x,int depth) {
    dep[x]=depth;
    for (int v:edge[x]) {
        if (v==fa[x]) continue;
        fa[v]=x; dfs(v,depth+1);
    }
}
vector<int> Line(int x,int y){
    vector<int> ret,rev;
    while (x!=y) {
        if (dep[x]>dep[y]) ret.push_back(x),x=fa[x];
        else rev.push_back(y),y=fa[y];
    } rev.push_back(x);
    reverse(rev.begin(), rev.end());
    for (int v:rev) ret.push_back(v);
    return ret;
}
char str[maxn];
char ans[maxn][2];
int main() {
    int i;
    int n,q; scanf("%d%d",&n,&q);
    FOR(i,1,n-1) {
        int u,v; scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    T_SAT::init(); dfs(1,0);
    int tot=n+q;
    FOR(i,1,q) {
        int x,y,k; scanf("%d%d%s",&x,&y,str);
        auto line=Line(x,y);
        // for (int v:line) printf("%d ",v); puts("<- v");
        REP(k,(int)line.size()) {
            int id=line[k],nid=id+tot;
            int q=i+n,nq=q+tot;
            if (!ans[id][0]) ans[id][0]=str[k];
            else if (str[k]!=ans[id][0]&&!ans[id][1]) ans[id][1]=str[k];
            // printf("id=%d,%c; s=%c%c\n",id,str[k],ans[id][0],ans[id][1]);
            if (str[k]!=ans[id][0]) T_SAT::addedge(id,nq),T_SAT::addedge(q,nid);
            if (str[k]!=ans[id][1]) T_SAT::addedge(nid,nq),T_SAT::addedge(q,id);
        }
        reverse(line.begin(), line.end());
        REP(k,(int)line.size()) {
            int id=line[k],nid=id+tot;
            int q=i+n,nq=q+tot;
            if (!ans[id][0]) ans[id][0]=str[k];
            else if (str[k]!=ans[id][0]&&!ans[id][1]) ans[id][1]=str[k];
            // printf("id=%d,%c; s=%c%c\n",id,str[k],ans[id][0],ans[id][1]);
            if (str[k]!=ans[id][0]) T_SAT::addedge(id,q),T_SAT::addedge(nq,nid);
            if (str[k]!=ans[id][1]) T_SAT::addedge(nid,q),T_SAT::addedge(nq,id);
        }
    }
    T_SAT::solve(tot+tot);
    // FOR(i,1,n) printf("(%c,%c)",ans[i][0],ans[i][1]);
    // FOR(i,1,tot+tot) printf("%d ",T_SAT::belong[i]);  puts("<- belong");
    FOR(i,1,tot) if (T_SAT::belong[i]==T_SAT::belong[i+tot]) return 0*puts("NO");
    puts("YES");
    FOR(i,1,n) {
        if (!ans[i][0]) putchar('a');
        else if (!ans[i][1]) putchar(ans[i][0]);
        else if (T_SAT::belong[i]<T_SAT::belong[i+tot]) putchar(ans[i][0]);
        else putchar(ans[i][1]);
    }
    // printf("%d\n",ans);
}
/*
*/