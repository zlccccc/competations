#include <cstdio>
#include <algorithm>
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

int a[102];
int n,m;
int i,j,k;
int x,y,z;
int ans,max0;
int main()
{
	scanf("%d",&n); 
	REP(i,n){
		scanf("%d",&m);
		ans+=m;
		if (m>max0) max0=m;
	}
	printf("%d",max0*n-ans);
}
