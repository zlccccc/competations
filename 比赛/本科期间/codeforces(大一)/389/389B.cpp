#include <cstdio>
#include <string>
char a[1003];
char b[1003];
int c[257];
int d[257];
bool mark=0;
int i;
int num;
int main()
{
	scanf("%s%s",a,b);
	for (i=0;a[i]!='\0';i++)
	{
		if (c[a[i]]==0) c[a[i]]=b[i];
		else if (c[a[i]]!=b[i]) mark=1;
		if (d[c[a[i]]]!=0&&d[c[a[i]]]!=a[i]) mark=1;
		d[c[a[i]]]=a[i];
	}
	for (i=0;i<256;i++)
	{
		if ((c[i]!=0)&&(c[c[i]]!=0)&&(c[c[i]]!=i)) mark=1;
		else if (c[c[i]]==i) c[c[i]]=0;
	}
	if (mark==1) printf("-1");
	else{
		for (i=0;i<256;i++) if (c[i]!=i&&c[i]!=0) num++;
		printf("%d\n",num);
		for (i=0;i<256;i++) if (c[i]!=i&&c[i]!=0) printf("%c %c\n",i,c[i]);
	}
}
