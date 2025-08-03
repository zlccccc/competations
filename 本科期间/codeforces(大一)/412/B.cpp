#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


int n,m;
int i,j,k;
int t;
bool mark1,mark2;
int mn;
bool judge(int pos,int point){
	int i,j;
	i=(point/50)%475;
	REP(j,25){
		i=(i*96+42)%475;
		if (i+26==pos) return 1;
	}
	return 0;
}
int main(){
	scanf("%d%d%d",&n,&k,&t);
	i=k;
	while (i>=t){
		if (judge(n,i)) return 0*puts("0");
		i-=50;
	}
	i=0;
	while ((k-50<t||!judge(n,k-50))&&!judge(n,k)) {
		k+=100;
		i++;
	}
	printf("%d",i);
}
