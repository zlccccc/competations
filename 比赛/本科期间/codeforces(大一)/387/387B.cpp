#include <cstdio>
#include <cmath>
int n,i,t;
char a[256];
int b[4]={0};
int main()
{
	scanf("%d",&n);
	if (n%4!=0)
	{
		printf("===");
		return 0;
	}
	scanf("%s",a);
	t=n/4;
	for (i=0;i<n;i++)
	if (a[i]=='A') b[0]++;
	else if (a[i]=='G') b[1]++;
	else if (a[i]=='T') b[2]++;
	else if (a[i]=='C') b[3]++;
	for (i=0;i<4;i++) if (b[i]>t)
	{
		printf("===");
		return 0;
	}
	for (i=0;i<n;i++)
	if (a[i]!='?') printf("%c",a[i]);
	else {
	if (b[0]<t) {b[0]++; printf("A");}
	else if (b[1]<t) {b[1]++; printf("G");}
	else if (b[2]<t) {b[2]++; printf("T");}
	else if (b[3]<t) {b[3]++; printf("C");}
	}
}
