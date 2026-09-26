#include <cstdio>
int ans[100001];
int main()
{
	int n,now=1;
	scanf("%d",&n);
	for(int i=1;i<=n;i+=2)
		ans[i]=now++;
	for(int i=2;i<=n;i+=2)
		ans[i]=now++;
	for(int i=1;i<n;i++)
		printf("%d ",ans[i]);
	printf("%d\n",ans[n]);
	return 0;
}
