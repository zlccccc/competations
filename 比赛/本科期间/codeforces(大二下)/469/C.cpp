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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,h;
int i,j,k;
int a[maxn];
vector<int> edge[maxn];
stack<int> S;
vector<int> V[maxn];
int dfn[maxn],low[maxn],tot,cnt;
int id[maxn],ok[maxn];
bool vis[maxn];
void tarjan(int x){
    low[x]=dfn[x]=++tot;
    S.push(x);vis[x]=1;
    for (int i=0;i<edge[x].size();i++){
        int v=edge[x][i];
        if (!dfn[v]){
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }else if (vis[v]){
            low[x]=min(low[x],dfn[v]);
        }
    }
    if (low[x]==dfn[x]){
        cnt++;
        while (1){
            int now=S.top();S.pop();
            vis[now]=0;id[now]=cnt;
            V[cnt].push_back(now);
            if (now==x) break;
        }
    }
}
int ans;
int t[maxn];
int UU[maxn],VV[maxn];
int main(){
    scanf("%d%d%d",&n,&m,&h);
    FOR(i,1,n) scanf("%d",&a[i]);
    FOR(i,1,m){
        int u,v;
        scanf("%d%d",&u,&v);
        if ((a[u]+1)%h==a[v]) edge[u].push_back(v);
        if ((a[v]+1)%h==a[u]) edge[v].push_back(u);
        UU[i]=u;VV[i]=v;
    }FOR(i,1,n) if (!dfn[i]) tarjan(i);
    ans=0;
    FOR(i,1,n) if (id[UU[i]]!=id[VV[i]]){
        int u=UU[i],v=VV[i];
        if ((a[u]+1)%h==a[v]) ok[id[u]]=1;
        if ((a[v]+1)%h==a[u]) ok[id[v]]=1;
    }
    FOR(i,1,cnt) if (!ok[i]){
        if (ans==0||V[i].size()<V[ans].size()) ans=i;
    }
    printf("%d\n",V[ans].size());
    for (int v:V[ans]) printf("%d ",v);
}
/*
*/
