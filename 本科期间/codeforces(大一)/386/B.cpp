#include <cstdio>
char a[2002];
int main()
{
	int n;
	int i;
	scanf("%d",&n);
	getchar();
	if (n&1) scanf("%c",&a[n/2]);
	for (i=n/2-1;i>=0;i--) scanf("%c%c",&a[i],&a[n-i-1]);
	printf("%s",a);
}
