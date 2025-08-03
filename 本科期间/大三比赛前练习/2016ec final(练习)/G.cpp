#include <bits/stdc++.h>
#include <utility>
#include <algorithm>
using namespace std;
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
typedef long long ll;
typedef pair<int,int> pii;
const int inf=0x3f3f3f3f;
const int maxn=3e5+7;
const ll mod=1e9+7;
ll powMM(ll a,ll b,ll M=mod){
    ll ret=1;
    for (;b;b>>=1,a=a*a%M)
        if (b&1) ret=ret*a%M;
    return ret;
}
int fa[maxn];
pii ans[maxn];
map<int,int> MP[maxn];
inline int getfa(int x){
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
} int Fa[maxn][20];
struct node{
    int u,v,w;
}edge[maxn];
void merge(int x,int y){//merge_dsu; y->x
    Fa[y][0]=x; fa[y]=x;
    ans[x]=max(ans[x],ans[y]);
    if (MP[x].size()<MP[y].size()) swap(MP[x],MP[y]);
    for (auto now:MP[y]){
        MP[x][now.first]+=now.second;
        ans[x]=max(ans[x],make_pair(MP[x][now.first],-now.first));
    } MP[y].clear();
}
int n,m,q;
void solve1(){
    int i,k;
    scanf("%d%d",&n,&m);
    FOR(i,1,n+m) {
        fa[i]=i,Fa[i][0]=0,ans[i]=make_pair(0,0);
        MP[i].clear();
    }
    FOR(i,1,n) scanf("%d",&k),MP[i][k]++,ans[i]=make_pair(1,-k);
    FOR(i,n+1,n+m)
        scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
    sort(edge+n+1,edge+1+n+m,[](node i,node j){
        return i.w<j.w;
    });
    FOR(i,n+1,n+m){
        int x=getfa(edge[i].u),y=getfa(edge[i].v);
        merge(i,x); merge(i,y);//x->w; y0>w
    }
    rFOR(i,1,n+m){
        int j; rep(j,1,20) Fa[i][j]=Fa[Fa[i][j-1]][j-1];
    }
}
void solve2(){
    int lastans=0,i; edge[0].w=inf;
    scanf("%d",&q);
    while (q--){
        int x,val;
        scanf("%d%d",&x,&val);
        x^=lastans; val^=lastans;
        // printf("query: %d %d\n",x,val);
        rREP(i,20) if (edge[Fa[x][i]].w<=val) x=Fa[x][i];
        // printf("x=%d; val=%d; %d %d\n",x,val,ans[x].first,ans[x].second);
        printf("%d\n",lastans=-ans[x].second);
    }
}
int main(){
    int _,T; scanf("%d",&T);
    FOR(_,1,T){
        printf("Case #%d:\n",_);
        solve1();
        solve2();
    }
}
/*
1
5 6
2 1 1 3 2
1 2 2
1 3 4
2 3 7
3 4 5
4 5 6
5 3 3
4
1 1
0 0
5 5
6 11
*/