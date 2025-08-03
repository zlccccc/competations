#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
int a[100001];
int b[100001];
int c[200001];
vector<int> e[200001];
void addedge(int u,int v)
{
	e[u].push_back(v);
	e[v].push_back(u);
}
void dfs(int u,int food)
{
	c[u]=food;
//	printf("%d	",u);
	for (int i=0;i<e[u].size();i++) if (!c[e[u][i]]) dfs(e[u][i],3-food);
}
int main()
{
	int n,m,w0;
	int i;
	scanf("%d",&n);
	for (i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
	for (i=1;i<=n;i++)
	{
		addedge(a[i],b[i]);
		addedge(i*2-1,i*2);
	}
	for (i=1;i<=2*n;i++) if (!c[i]) dfs(i,1);
	for (i=1;i<=n;i++) printf("%d %d\n",c[a[i]],c[b[i]]);
	return 0;
}
