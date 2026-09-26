#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
#define ULL unsigned long long
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,N) for (I=1;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
#define N 1000000
const int M=1e9+7;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
inline int min(int a,int b) {return a>b?b:a;}

char a[102];
char b;
int c[256];
int n,m;
int i,j,k;
int x,y,z;
int ans,num;
int main()
{
	scanf("%s",a);
	n=strlen(a);
	REP(j,4){
		num=0;
		for (i=j;i<n;i+=4){
			if (a[i]!='!') b=a[i];
			if (a[i]=='!') num++;
		}
		c[b]=num;
	}
	printf("%d %d %d %d",c['R'],c['B'],c['Y'],c['G']);
}
