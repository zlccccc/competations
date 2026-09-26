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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

vector<int> edge[maxn];
int id[maxn],out[maxn],tot;
void dfs(int x){
    id[x]=++tot;
    for (int v:edge[x]){
        dfs(v);
    }out[x]=tot;
}
int dep[maxn];
int fa[maxn][20];
int lca(int x,int y){
	int i;
	if (dep[x]<dep[y]) swap(x,y);
	rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
	if (x==y) return x;
	rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int dis(int x,int y){
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}
int top[maxn][20];

int upp[maxn];
int ans[maxn],ini[maxn],cnt[maxn];//cnt:if_have?
inline int lowbit(int x){return x&-x;}
int sum[maxn];
void update(int x){//修改不如add有效
	for (;x<=200000;x+=lowbit(x)) sum[x]++;
}
int presum(int x){
	LL ret=0;
	for (;x;x-=lowbit(x)) ret+=sum[x];
	return ret;
}
int query(int l,int r){
	return presum(r)-presum(l-1);
}

struct quer{
    int l,r,id,mask;
    quer(int _l,int _r,int _id,int _mask):l(_l),r(_r),id(_id),mask(_mask){};
};
vector<int> E[maxn];
vector<quer> Q[maxn];
int main() {
    int i,j,k,l,T;
    int n;
    scanf("%d",&n);
    FOR(i,2,n) {
        scanf("%d",&fa[i][0]);
        edge[fa[i][0]].push_back(i);
        rep(j,1,20) fa[i][j]=fa[fa[i][j-1]][j-1];
        dep[i]=dep[fa[i][0]]+1;
    }dfs(1);
    int m,q;
    scanf("%d",&m);
    FOR(i,1,n) top[i][0]=i;
    FOR(i,1,m){
        int u,v;
        scanf("%d%d",&u,&v);
        int f=lca(u,v);
//        dbg(u);dbg(v);dbgln(f);
        if (dep[top[u][0]]>dep[f]) top[u][0]=f;
        if (dep[top[v][0]]>dep[f]) top[v][0]=f;
        E[id[u]].push_back(id[v]);
        E[id[v]].push_back(id[u]);
    }rFOR(i,1,n){
        if (dep[top[fa[i][0]][0]]>dep[top[i][0]])
            top[fa[i][0]][0]=top[i][0];
//        printf("(%d):%d ",i,top[i][0]);
    }
    FOR(i,1,n)
        rep(j,1,20) top[i][j]=top[top[i][j-1]][j-1];
    scanf("%d",&q);
    FOR(k,1,q) {
        int u,v;
        scanf("%d%d",&u,&v);
        int f=lca(u,v);
        rREP(i,20) if (dep[top[u][i]]>dep[f]) {
            u=top[u][i]; ini[k]+=1<<i;
//            dbg(u);dbgln(f);
        }rREP(i,20) if (dep[top[v][i]]>dep[f]) {
            v=top[v][i]; ini[k]+=1<<i;
//            dbg(v);dbgln(f);
        }
//        dbg(u);dbg(v);
        if (dep[top[u][0]]<=dep[f]&&dep[top[v][0]]<=dep[f]) ans[k]=2;
        else ini[k]=INF;
        if (u==f||v==f) ans[k]=1;
        if (u==f&&v==f) ans[k]=0;
        if (id[u]>id[v]) swap(u,v);
        Q[id[u]-1].push_back(quer(id[v],out[v],k,-1));
        Q[out[u]].push_back(quer(id[v],out[v],k,1));
//        printf("%d-%d %d-%d\n",id[u],out[u],id[v],out[v]);
    }
//    cerr<<"start_2"<<"\n";
    FOR(i,1,n){
        for (int v:E[i]) update(v);
        for (auto now:Q[i]){
            cnt[now.id]+=now.mask*query(now.l,now.r);
        }
    }FOR(i,1,q){
        if (cnt[i]) ans[i]=min(ans[i],1);
    }
//    FOR(i,1,q) printf("%d ",cnt[i]);puts("");
//    FOR(i,1,q) printf("%d + %d\n",ans[i],ini[i]);
    FOR(i,1,q){
        int ANS=ans[i]+ini[i];
        if (ANS>INF/2) puts("-1");
        else printf("%d\n",ANS);
    }
}
/*
*/
