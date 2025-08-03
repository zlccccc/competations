#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#define REP(I,S,N) for (I=S;I<N;I++)
#define rREP(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
const int maxn=1e6+7;
const int INF=0x3f3f3f3f;
using namespace std;
typedef long long LL;

vector<int> edge[maxn];
int match[maxn];
bool used[maxn];
int n,m;
bool dfs(int u){
    int v,i;
    REP(i,0,edge[u].size()){
        v=edge[u][i];
        if (!used[v]){
            used[v]=1;
            if (match[v]==-1||dfs(match[v])){
                match[v]=u;
                match[u]=v;
                return 1;
            }
        }
    }return 0;
}
int main(){
    int T,n,m,k,i,j;
    while (~scanf("%d%d%d",&n,&m,&k)){
        FOR(i,1,n+m) edge[i].clear();
        FOR(i,1,k){
            int x,y;
            scanf("%d%d",&x,&y);
            if (x==0||y==0) continue;
            edge[x].push_back(y+n);
            edge[y+n].push_back(x);
        }FOR(i,1,n+m) match[i]=-1;
        int ans=0;
        FOR(i,1,n+m){
            if (match[i]==-1){
                FOR(j,1,n+m) used[j]=0;
                if (dfs(i)) ans++;
            }
        }printf("%d\n",ans);
    }
}