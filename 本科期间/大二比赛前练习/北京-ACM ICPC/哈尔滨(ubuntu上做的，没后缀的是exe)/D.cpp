#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <string>
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const int maxn=1e5+7;

bool mark[maxn];
int len[maxn];
vector<int> edge[maxn];
int dfs(int x,int fa){
    int ret=0,Len=0;
    for (int v:edge[x]) if (v!=fa){
        ret=max(ret,dfs(v,x));
        if (len[x]<len[v]) Len=len[x],len[x]=len[v];
        else if (Len<len[v]) Len=len[v];
    }
    if (len[x]&&Len) ret=max(ret,len[x]+Len);
    if (mark[x]&&len[x]) ret=max(ret,len[x]);
    if (mark[x]||len[x]) len[x]++;
    return ret;
}
int main(){
    int i,j,k,T;
    int n,m;
    scanf("%d",&T);
    while (T--){
        scanf("%d%d",&n,&m);
        FOR(i,1,n) len[i]=mark[i]=0,edge[i].clear();
        FOR(i,1,m) scanf("%d",&k),mark[k]=1;
        FOR(i,1,n-1){
            int u,v;
            scanf("%d%d",&u,&v);
            edge[u].emplace_back(v);
            edge[v].emplace_back(u);
        }printf("%d.00\n",dfs(1,0)/2);
    }
	return 0;
}
/*
*/
