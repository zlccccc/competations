#include <cstdio>
char a[200002];
bool c[257];
int i;
int n;
bool mark;
int ans;
int main()
{
	scanf("%d",&n);
	scanf("%s",a);
	c['R']=c['L']=c['U']=c['D']=0;
	for (i=0;a[i]!='\0';i++)
	{
		mark=0;
		if ((a[i]=='L')&&(c['R']==1)) mark=1;
		if ((a[i]=='R')&&(c['L']==1)) mark=1;
		if ((a[i]=='U')&&(c['D']==1)) mark=1;
		if ((a[i]=='D')&&(c['U']==1)) mark=1;
		if (mark)
		{
//			printf("  ");
			ans++;
			c['R']=0; c['L']=0; c['U']=0; c['D']=0;
		}
//		printf("%c",a[i]);
		c[a[i]]=1;
//		printf("%d%d%d%d ",c['R'],c['L'],c['U'],c['D']);
	}
	printf("%d",ans+1);
}
