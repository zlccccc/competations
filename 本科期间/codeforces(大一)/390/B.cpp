#include <cstdio>
#include <cmath>
char a[10][10];
int i,j,k;
int n,m;
int l0;
int num;
int main()
{
	scanf("%s%s%s%s",a[0],a[1],a[2],a[3]);
	for (i=0;i<4;i++)
		for (j=0;j<4;j++) if (a[i][j]=='.')
		{
			a[i][j]='x';
			for (n=0;n<4;n++)
				for (m=0;m<4;m++)
				if (a[n][m]=='x'&&a[n+1][m]=='x'&&a[n+2][m]=='x'){
					printf("YES");
					return 0;
				}
				else if (a[n][m]=='x'&&a[n][m+1]=='x'&&a[n][m+2]=='x'){
					printf("YES");
					return 0;
				}
				else if (a[n][m]=='x'&&a[n+1][m+1]=='x'&&a[n+2][m+2]=='x'){
					printf("YES");
					return 0;
				}
				else if (n>=2&&a[n][m]=='x'&&a[n-1][m+1]=='x'&&a[n-2][m+2]=='x'){
					printf("YES");
					return 0;
				}
//			printf("\n%s\n%s\n%s\n%s\n",a[0],a[1],a[2],a[3]);
			a[i][j]='.';
		}
	printf("NO");
	return 0;
}
