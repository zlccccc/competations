#include <iostream>
#include <cstdio>
#include <vector>
#define INF 0x7ffffffffffffff
using namespace std;
vector<int> edge[200002];
int a[200002];
bool m[200002];
long long ans=-INF;
long long max0;
long long dp(int root)
{
	m[root]=1;
	long long sum=0;
	long long max=-INF;
	long long j;
	int i;
	for (i=0;i<edge[root].size();i++) if (!m[edge[root][i]])
	{
		sum+=dp(edge[root][i]);
		j=max0;
		if (max!=-INF&&j+max>ans) ans=j+max;
		if (max<j) max=j;
	}
	if (max<sum+a[root]) max0=sum+a[root];
	else max0=max;
	return sum+a[root];
}
int main()
{
	int n;
	int i,j,k;
    scanf("%d",&n);
    for (i=1;i<=n;i++) scanf("%d",&a[i]);
    for (i=1;i<n;i++)
    {
    	scanf("%d%d",&j,&k);
    	edge[j].push_back(k);
    	edge[k].push_back(j);
	}
	dp(1);
	if (ans==-INF) printf("Impossible");
	else printf("%I64d",ans);
    return 0;
}
