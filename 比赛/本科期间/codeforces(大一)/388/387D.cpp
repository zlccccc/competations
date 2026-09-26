#include <cstdio> 
#include <algorithm>
#include <vector>
#include <iostream>
#define N 200005
using namespace std;
vector<int> c[N];
int Max[N];
int b[N];
int a[N];
int ban[N];
int num;
int n,i,j;
int k,v,q;
int m1,m2;
int cmp(int l,int r)
{
	return Max[l]>Max[r];
}
int main()
{
	scanf("%d",&n);
	for (i=0;i<n;i++)
	{
		scanf("%d%d",&k,&v);
		c[k].push_back(v);
		Max[k]=v;
		b[k]=k;
	}
	sort(b+1,b+n+1,cmp);
	scanf("%d",&q);
	for (i=0;i<q;i++)
	{
		m1=m2=0;
		scanf("%d",&k);
		for (j=1;j<=k;j++) {scanf("%d",&a[j]); ban[a[j]]=1;}
		for (j=1;j<=n;j++){
			if (b[j]==0) break;
			if (ban[b[j]]) continue;
			if (m1==0) m1=b[j];
			else {m2=b[j]; break;}
		}
		if (m1==0)
		{
			printf("0 0\n");
		}
		else if (m2==0){
			printf("%d %d\n",m1,c[m1][0]);
		}
		else {
			int p=lower_bound(c[m1].begin(),c[m1].end(),Max[m2])-c[m1].begin();
			printf("%d %d\n",m1,c[m1][p]);
		}
		for (j=1;j<=k;j++) ban[a[j]]=0;
	}
}
