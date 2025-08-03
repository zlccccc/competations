#include <cstdio>
inline min(int a,int b){
	return a>b?b:a;
}
int main()
{
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	printf("%d",7*min(min(a,b/2),c/4));
}
