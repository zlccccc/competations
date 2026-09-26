#include <bits/stdc++.h>
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
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
inline void add(int &A,int B){A+=B;(A>=M)&&(A-=M);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

struct Edge {
    int to,next;
    Edge(int _to=0,int _next=-1):to(_to),next(_next) {};
} edge[maxn*10];
int head[maxn],pre[maxn],dom[maxn],etot; //edges
inline void addedge(int head[],int u,int v) {
    edge[++etot]=Edge(v,head[u]);
    head[u]=etot;
}
int dfn[maxn],tot,par[maxn]; //dfs-tree
int Fa[maxn],best[maxn]; //disjoint-set
int semi[maxn],id[maxn],idom[maxn]; //dom-tree
inline int getfa(int x) {
    if(Fa[x]==x) return x;
    int F=getfa(Fa[x]);
    if(dfn[semi[best[x]]]>dfn[semi[best[Fa[x]]]])
        best[x]=best[Fa[x]];
    return Fa[x]=F;
}
void dfs(int x) {
    dfn[x]=++tot;
    id[tot]=x;
    for(int i=head[x]; ~i; i=edge[i].next) {
        int v=edge[i].to;
        if(!dfn[v]) par[v]=x,dfs(v);
    }
}
void tarjan(int n) {
    int i;
    FOR(i,1,n) dom[i]=-1;
    FOR(i,1,n) best[i]=semi[i]=Fa[i]=i;
    rFOR(i,2,tot) {
        int x=id[i];
        for(int j=pre[x]; ~j; j=edge[j].next) {
            int v=edge[j].to;
            if(!dfn[v]) continue; //could not reach
            getfa(v); //pre_dfn:not changed
            if(dfn[semi[best[v]]]<dfn[semi[x]])
                semi[x]=semi[best[v]];
        }
        addedge(dom,semi[x],x);
        Fa[x]=par[x];
        x=id[i-1];
        for(int j=dom[x]; ~j; j=edge[j].next) { //path
            int v=edge[j].to;
            getfa(v); //id[min{dfn[z]}];
            if(semi[best[v]]==x) idom[v]=x;
            else idom[v]=best[v];
        }
    }
    FOR(i,2,tot) {
        int x=id[i];
        if(idom[x]!=semi[x]) idom[x]=idom[idom[x]];
    }
}
typedef pair<int,ll> pil;
typedef pair<ll,int> pli;
vector<pil> E[maxn];
ll dis[maxn];
int n,m;
int cnt[maxn];
int solve(){
    int ans=0,i;
//    FOR(i,1,tot) printf("%d ",id[i]);puts("");
//    FOR(i,1,tot) printf("%d ",idom[i]);puts("");
    FOR(i,1,tot) cnt[id[i]]=0;
    rFOR(i,2,tot) {
        int x=id[i]; cnt[x]++;
        cnt[idom[x]]+=cnt[x];
        ans=max(ans,cnt[x]);
    }
    return ans;
}
int TaskA(){
    int i,j,k,s;
    scanf("%d%d%d",&n,&m,&s);
    priority_queue<pli> Q;
    FOR(i,1,n) head[i]=pre[i]=-1,E[i].clear();
    FOR(i,1,n) dfn[i]=id[i]=idom[i]=0; etot=tot=0;
    FOR(i,1,m){
        int u,v; ll len;
        scanf("%d%d%I64d",&u,&v,&len);
        E[u].push_back(make_pair(v,len));
        E[v].push_back(make_pair(u,len));
    }FOR(i,1,n) dis[i]=INFF;
    Q.push(make_pair(0,s)); dis[s]=0;
    while (Q.size()){
        auto TOP=Q.top(); Q.pop();
        int x=TOP.second;
        if (dis[x]!=-TOP.first) continue;
        for (auto now:E[x]){
            int v=now.first;
            ll len=now.second+dis[x];
            if (dis[v]>len) dis[v]=len,Q.push(make_pair(-dis[v],v));
        }
    }FOR(i,1,n){
        for (auto now:E[i]){
            int v=now.first; ll len=now.second+dis[i];
            if (dis[v]==len) addedge(head,i,v),addedge(pre,v,i);
        }
    }
    dfs(s);tarjan(n);
    printf("%d\n",solve());
    return 0;
}
void initialize(){}
void Task_one(){TaskA();}
void Task_T(){int T;scanf("%d",&T);while (T--) TaskA();}
void Task_more_n(){while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m(){while (~scanf("%d%d",&n,&m)) TaskA();}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*
*/
