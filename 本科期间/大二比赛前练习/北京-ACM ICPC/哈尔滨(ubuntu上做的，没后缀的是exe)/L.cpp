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
vector<int> edge[maxn];
int pre[maxn],sub[maxn],MIN[maxn],MAX[maxn];
int n;
int dfs(int x,int fa,int X){
    MIN[x]=0;MAX[x]=1;
    int ret=1;
    for (auto v:edge[x]) if (v!=fa){
        ret&=dfs(v,x,X);
        MIN[x]+=MIN[v];MAX[x]+=MAX[v];
    }
    MIN[x]=max(MIN[x],sub[x]);
    MAX[x]=min(MAX[x],X-pre[x]);
    if (MIN[x]>MAX[x]) return 0;
    return ret;
}
int main(){
	int i,j,m,x,T;
	scanf("%d",&T);
    while (T--){
        scanf("%d",&n);
        FOR(i,1,n-1){
            int u,v;
            scanf("%d%d",&u,&v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        scanf("%d",&m);
        FOR(i,1,m){
            int u,val;
            scanf("%d%d",&u,&val);
            sub[u]=max(sub[u],val);
        }scanf("%d",&m);
        FOR(i,1,m){
            int u,val;
            scanf("%d%d",&u,&val);
            pre[u]=max(pre[u],val);
        }
        int l=-1,r=n+1;//r:OK
        while (l+1<r){
            int mid=(l+r)/2;
            if (dfs(1,0,mid)&&MAX[1]>=mid) r=mid;//OKAY
            else l=mid;
        }
        if (r==n+1) puts("-1");
        else printf("%d\n",r);
        FOR(i,1,n){
            edge[i].clear();
            pre[i]=sub[i]=0;
        }
    }
	return 0;
}
/*
*/
