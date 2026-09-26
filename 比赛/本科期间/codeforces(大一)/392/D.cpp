#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
#define ULL long long
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,N) for (I=1;I<=N;I++)
#define INF 1e18+1
#define INFF 0x3f3f3f3f3f3f3f3f
#define N 1000000
const int M=1e9+7;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
inline int min(int a,int b) {return a>b?b:a;}

char a[102];
ULL n,m;
ULL i,i0,j,k;
ULL mn;
ULL x,y=1,y0=1;
bool mark;
int main()
{
	scanf("%I64d%s",&n,a);
	m=strlen(a);
	for (i=m-1;i>=0;){
		x=0; y0=1; i0=i;
		while (i0>=0&&y0<n&&(x+(a[i0]-'0')*y0)<n) x=x+(a[i0]-'0')*y0,y0*=10,i0--;
		while ((i0<i)&&(a[i0+1]=='0')) i0++;
		if (x==0) y*=n,i--;
		else {
			i=i0;
			mn=mn+x*y;
			y*=n;
			if (i>=0) x=a[i]-'0';
		}
//		printf("x=%I64d   y0=%I64d,  y=%I64d,  %I64d     %I64d\n",x,y0,y,mn,i);
	}
	printf("%I64d",mn);
}
