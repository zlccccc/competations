#include <cstdio>
#include <algorithm>
#define ULL unsigned long long
#define REP(I,N) for (I=0;I<N;I++)
#define INF 0x7f7f7f7f
#define N 100000
int gcd(int a,int b){return b?gcd(b,a%b):a;}
inline int min(int a,int b) {return a>b?b:a;}
int n,m;
int i;
char s[]="Bulbasaur"; 
int b[300];
char a[N+3];
int num;
int main()
{
	scanf("%s",a);
	for (i=0;a[i]!='\0';i++) b[a[i]]++;
	num=min(b['B'],b['l']);
	num=min(num,b['r']);
	num=min(num,b['s']);
	num=min(num,b['b']);
	num=min(num,b['u']/2);
	num=min(num,b['a']/2);
	printf("%d",num);
}
