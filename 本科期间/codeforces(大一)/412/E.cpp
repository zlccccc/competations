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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


int i,j;
LL k;
int sum;
int a[64],b[64];
int num[64];
void pushin(LL x){
	int i;
	FOR(i,0,60){
		if (x==1ll<<i){
			a[i]++;
			return;
		}
		if (x<1ll<<i){
			b[i-1]++;
			return;
		}
	}
}
bool judge(int x){
	int i,count=0,prex=x,use;
	FOR(i,0,60){
		if (a[i]<x) x=a[i];
		num[i]=x;
	}
//	FOR(i,0,20) printf("%d ",num[i]);puts("");
//	FOR(i,0,20) printf("%d ",a[i]);puts("");
//	FOR(i,0,20) printf("%d ",b[i]);puts("");
	rFOR(i,0,60){
		count+=a[i]+b[i]-num[i];//Î²²¿ 
//		printf("%d ",count);
		if (count>num[i]) return 0;
	}
	return 1;
}
bool mark;
int n;
int main(){
	scanf("%d",&n);
	REP(i,n){
		scanf("%I64d",&k);
		pushin(k);
	}
	FOR(i,1,a[0]) if (judge(i)) printf("%d ",i),mark=1;
	if (!mark) puts("-1");
}
