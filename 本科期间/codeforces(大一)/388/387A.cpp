#include <cstdio>
#include <cmath>
int main()
{
	int n;
	scanf("%d",&n);
	printf("%d\n",n/2);
	if (n%2==1)
	{
		while (n>4) {printf("2 "); n-=2;}
		printf("3");
	}
	else
		while (n>0) {printf("2 "); n-=2;}
}
