#include <cstdio>
#include <algorithm>
#define ULL unsigned long long
#define REP(I,N) for (I=0;I<N;I++)
#define INF 0x7f7f7f7f
#define N 100000
int gcd(int a,int b){return b?gcd(b,a%b):a;}
inline int min(int a,int b) {return a>b?b:a;}
int n,m;
int i,j;
bool a[2*N+3];
int c[2*N+3];
int si;
int num;
int main()
{
	scanf("%d",&n);
	REP(i,n) scanf("%d",&si),c[si]++;
	for (i=2;i<=N;i++)
		if (a[i]==0){
			m=0;
			for (j=i;j<=N;j+=i) m+=c[j];
			for (j=i;j<=N;j+=i) a[j]=1;
			if (m>num) num=m;
		}
	if (num==0) num=1;
	printf("%d",num);
}
