#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define ULL unsigned long long
#define REP(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x7f7f7f7f
#define N 1000000
const int M=1e9+7;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
inline int min(int a,int b) {return a>b?b:a;}

int n,m,m0;
int id;
int i,j;
vector<int>a[N+5];
long long num=1,ans=1;
int main()
{
	scanf("%d%d",&n,&m);
	FOR(i,1,n){
		scanf("%d",&m0);
		REP(j,0,m0) scanf("%d",&id),a[id].push_back(i);
	}
	sort(a+1,a+m+1);
	FOR(i,2,m){
		if (a[i]==a[i-1]) ans=ans*++num%M;
		else num=1;
	}
	printf("%lld",ans);
}
