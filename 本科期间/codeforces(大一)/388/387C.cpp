#include <cstdio>
inline int min(int a,int b)
{
	return a<b?a:b;
}
int c;
char a[800000];
int main()
{
	int i,n;
	int v=0;//D+R;
	scanf("%d",&n);
	scanf("%s",a);
	for (i=0;i<min(n,600000);i++)
	{
		if (a[i]=='D')
		{
			if (v>=0) a[n++]='D';
			v++;
		}
		if (a[i]=='R')
		{
			if (v<=0) a[n++]='R';
			v--;
		}
	}
	printf("%c\n",a[n-1]);
}
