#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e6+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const double eps=0.000001;

int n,i;
vector<pair<int,LL> > edge[maxn];
LL ans,k;
LL dfs(int x,int fa){
	LL ret=1;
    for (pair<int,LL> v:edge[x]){
    	if (v.first==fa) continue;
        LL t=dfs(v.first,x);
		ans+=min(k,t-1)*v.second;
        ret+=t;
    }
    return ret;
}
int main()
{
    while (~scanf("%d%d",&n,&k)){
        ans=0;
        REP(i,n-1){
            int u,v;
            LL cost;
            scanf("%d%d%lld",&u,&v,&cost);
            edge[u].push_back(make_pair(v,cost));
            edge[v].push_back(make_pair(u,cost));
            ans+=cost;
        }
        k--;
        dfs(1,0);
        printf("%lld\n",ans);
        FOR(i,1,n) edge[i].clear();
    }
    return 0;
}
/*
*/
