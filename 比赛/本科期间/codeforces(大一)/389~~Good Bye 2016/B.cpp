#include <cstdio>
#include <cmath>
int n=0,i;
int T;
char a[10];
int main()
{
	scanf("%d",&T);
	while (T--){
		scanf("%d%s",&i,a);
		if (((n==0)&&(a[0]!='S'))||((n==20000)&&(a[0]!='N'))){
			printf("NO");
			return 0;
		}
		if (a[0]=='S') n+=i;
		if (a[0]=='N') n-=i;
		if (a[0]=='N'&&n*(n+i)<0){
			printf("NO");
			return 0;
		}
		if (n>20000||n<-20000){
			printf("NO");
			return 0;
		}
		n=(n+40000)%40000;
	}
	if (n==0) printf("YES");
	else printf("NO");
}
