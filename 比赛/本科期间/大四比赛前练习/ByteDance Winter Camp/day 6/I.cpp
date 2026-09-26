#include<bits/stdc++.h>
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
using namespace std;
const int maxn=2e5+7;

int n,m;
vector<pair<int,int> > edges[maxn];
int sz[maxn];
bool okay[maxn],mark[maxn];
int sonx[maxn],sony[maxn];
vector<int> sons[maxn];

int dfn[maxn],low[maxn],vis[maxn],tot;
int belong[maxn];
int S[maxn],top;
vector<int> edge[maxn];
void tarjan(int x) {
    dfn[x]=low[x]=++tot;
    S[++top]=x; vis[x]=1;
    for (int v:edge[x]){
        if (!dfn[v]) {
            tarjan(v);
            low[x]=min(low[x],low[v]);
        } else if (vis[v])
            low[x]=min(low[x],dfn[v]);
    } if (low[x]==dfn[x]){
        while (1){
            int now=S[top--];
            vis[now]=0;
            belong[now]=x;
            if (now==x) break;
        }
    }
}
bool check(const vector<pair<int,int> > &E) {
    tot=0; bool no=0;//no!
    for (auto e:E) {
        int x=e.first,y=e.second;
        int _x=-x,_y=-y;
        if (x<0) x=n-x;
        if (y<0) y=n-y;
        if (_x<0) _x=n-_x;
        if (_y<0) _y=n-_y;
//        printf("e:%d-%d\n",_x,y);
//        printf("e:%d-%d\n",_y,x);
        edge[_x].push_back(y);
        edge[_y].push_back(x);
    }
    for (auto e:E) {
        int x=e.first,y=e.second;
        int _x=-x,_y=-y;
        if (_x<0) _x=n-_x;
        if (_y<0) _y=n-_y;
        if (!dfn[_x]) tarjan(_x);
        if (!dfn[_y]) tarjan(_y);
    }
//    for (auto e:E) printf("%d %d\n",e.first,e.second);
    for (auto e:E) {
        int x=e.first,y=e.second;
        x=abs(x); y=abs(y);
        int _x=x+n,_y=y+n;
//        printf("%d %d: belong: %d %d\n",x,_x,belong[x],belong[_x]);
//        printf("%d %d: belong: %d %d\n",y,_y,belong[y],belong[_y]);
        if (belong[x]==belong[_x]) no=1;
        if (belong[y]==belong[_y]) no=1;
        dfn[x]=vis[x]=0; edge[x].clear();
        dfn[y]=vis[y]=0; edge[y].clear();
        dfn[_x]=vis[_x]=0; edge[_x].clear();
        dfn[_y]=vis[_y]=0; edge[_y].clear();
    }
    return !no;
}
vector<pair<int,int> > E;
bool dfs(int i,int top){
    sons[top].push_back(i);
    if (i<=m) return okay[i]=1;
    mark[i]=1;
    int x=sz[sonx[i]]<sz[sony[i]]?sonx[i]:sony[i];
    int y=sonx[i]+sony[i]-x;
    if (!dfs(x,x)) return okay[i]=0;
    edges[i].swap(edges[x]);
//    printf("solve - down: %d: y=%d\n",i,y);
    if (!dfs(y,top)) return 0;//heavy
    if (i==top) {
        reverse(sons[i].begin(),sons[i].end());
        int l=-1,r=sons[i].size(),k;
//        printf("solve %d: ",i);
//        for (int v:sons[i]) printf("%d ",v);
//        puts("");
        while (l+1<r) {
            int mid=(l+r)/2; E.clear();
//            printf("check: mid=%d\n",mid);
            FOR(k,0,mid) for (auto e:edges[sons[i][k]]) E.push_back(e);
            if (check(E)) l=mid; else r=mid;
        } FOR(k,0,l) okay[sons[i][k]]=1;
        FOR(k,l+1,(int)sons[i].size()-1) okay[sons[i][k]]=0;
        FOR(k,0,(int)sons[i].size()-2){
            for (auto e:edges[sons[i][k]])
                edges[i].push_back(e);
            edges[sons[i][k]].clear();
        } return okay[i];
//        FOR(k,0,l) printf("sons[i][k]=%d\n",sons[i][k]);
//        for (auto e:edges[i]) printf("%d-%d\n",e.first,e.second);
    } return 1;
}
int main() {
    int i;
    scanf("%d%d",&n,&m);
    FOR(i,1,m) {
        int x,y; sz[i]=1;
        scanf("%d%d",&x,&y);
        edges[i].push_back(make_pair(x,y));
    } FOR(i,m+1,m+m-1) {
        scanf("%d%d",&sonx[i],&sony[i]);
        sz[i]=sz[sonx[i]]+sz[sony[i]];
        sz[i]=sz[sonx[i]]+sz[sony[i]];
    }
//    puts("yes");
    rFOR(i,m+1,m+m-1)
        if (!mark[i]) dfs(i,i);
    FOR(i,m+1,m+m-1) {
        if (okay[i]) puts("Possible");
        else puts("Impossible");
    }
    return 0;
}
