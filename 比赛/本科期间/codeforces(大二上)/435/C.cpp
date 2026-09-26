#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int mark[maxn];
int main(){
	int n,k;
//	printf("%d",1<<19);
	scanf("%d%d",&n,&k);
	if (k==0&&n==2) return 0*puts("NO");
	puts("YES");
	if (n%4==1){
		printf("%d ",k);mark[k]=1;
		n--;
	}else if (n%4==2){
		if (k==0) printf("1 2 4 8 16 31 "),n-=6,mark[1]=mark[2]=mark[4]=mark[8]=mark[16]=mark[31]=0;
		else{
		printf("%d ",k|(1<<17));mark[k]=1;
		printf("%d ",1<<17);mark[k]=1;
		n-=2;
		}
	}else if (n%4==3){
		printf("%d ",k|(1<<17)|(1<<18));mark[k|(1<<17)|(1<<18)]=1;
		printf("%d ",1<<17);mark[1<<17]=1;
		printf("%d ",1<<18);mark[1<<18]=1;
		n-=3;
	}else if (n%4==0){
		printf("%d ",k|(1<<17));mark[k|(1<<17)]=1;
		printf("%d ",(1<<17)|(1<<18));mark[(1<<17)|(1<<18)]=1;
		printf("%d ",(1<<18)|1);mark[1<<18|1]=1;
		printf("%d ",1);mark[1]=1;
		n-=4;
	}
	int i=0;
	while (n){
		i++;
		if (mark[i<<3|1]||mark[i<<3|2]||mark[i<<3|4]||mark[i<<3|7]) continue;
		printf("%d %d %d %d ",i<<3|1,i<<3|2,i<<3|4,i<<3|7);mark[i<<3|1]=mark[i<<3|2]=mark[i<<3|4]=mark[i<<3|7]=1;
		n-=4;
	}
}
/*
*/
