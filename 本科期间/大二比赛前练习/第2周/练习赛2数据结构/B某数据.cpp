#include <cstdio>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=3e5+7;
const double eps=0.00000001;
const LL INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}

int i;
char a[5];
int S[maxn],pos;
int l,r,val;
int main()
{
	freopen("invazia.in","w",stdout);
	printf("300000 500000\n");//262144
	FOR(i,1,500000) printf("I 1 262143 1\n");
	return 0;
}
/*
*/
