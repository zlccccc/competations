#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <utility>
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


vector<pair<LL,LL> > edge[maxn];
LL t,i,k;
LL ans[maxn],sum[maxn];
void dfs(int x,int from)
{
	LL i,tot;
	vector<pair<LL,LL> > V;
	REP(i,edge[x].size()) if (edge[x][i].first!=from){
		dfs(edge[x][i].first,x);
		V.push_back(make_pair(sum[edge[x][i].first]+edge[x][i].second,ans[edge[x][i].first]+edge[x][i].second));
	}
	sort(V.begin(),V.end());
	reverse(V.begin(),V.end());
	tot=V.size();
	tot=min(tot,k-1);
	REP(i,tot) sum[x]+=V[i].first;
	REP(i,tot){
		if (V.size()>=k)
			ans[x]=max(ans[x],V[i].second-V[i].first+V[k-1].first);
		else
			ans[x]=max(ans[x],V[i].second-V[i].first);
//		printf("%d %d %d\n",x,ans[x],sum[x]+V[i].second-V[i].first);
	}
	rep(i,tot,V.size()) ans[x]=max(ans[x],V[i].second);
	ans[x]+=sum[x];
}
LL n,u,v,c;
int main()
{
    scanf("%I64d%I64d",&n,&k);
    for(int i=0;i<n-1;i++)
    {
        scanf("%I64d%I64d%I64d",&u,&v,&c);
        edge[u].push_back(make_pair(v,c));
        edge[v].push_back(make_pair(u,c));
    }
    dfs(0,-1);
//    REP(i,n) printf("%3d ",ans[i]);puts("");
//    REP(i,n) printf("%3d ",sum[i]);puts("");
    printf("%I64d\n",ans[0]);
    return 0;
}
/*
*/
