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

//2 4 6 8 10 12*(250-t)   /2 
int cnt[6];
int a[6],b[6];
int i,j,k;
int sum;
int num(int m,int n){
	if (m*2>n) return 1;
	if (m*4>n) return 2;
	if (m*8>n) return 3;
	if (m*16>n) return 4;
	if (m*32>n) return 5;
	return 6;
}
int n,m;
bool judge(int x){
	int sum=0,i;
	FOR(i,1,5){
//		printf("/%d:%d/",cnt[i],n+x);
		if (a[i]==0||a[i]>b[i]) sum+=num(cnt[i],n+x)*(a[i]-b[i]);
		else sum+=num(cnt[i]+x,n+x)*(a[i]-b[i]);
//		printf("%4d ",sum);
	}
//	printf("%d %d\n",x,sum);
	return sum>0;
}
int main(){
	scanf("%d",&n);
	FOR(i,1,5) {scanf("%d",&k); if (k!=-1) cnt[i]++,a[i]=250-k;else a[i]=0;}
	FOR(i,1,5) {scanf("%d",&k); if (k!=-1) cnt[i]++,b[i]=250-k;else b[i]=0;}
	REP(j,n-2)
		FOR(i,1,5){scanf("%d",&k);if (k!=-1) cnt[i]++;}
//	FOR(i,1,5) printf("%4d ",a[i]);puts("");
//	FOR(i,1,5) printf("%4d ",b[i]);puts("");
//	FOR(i,1,5) printf("%4d ",cnt[i]);puts("");
	FOR(i,0,10000) if (judge(i)) {printf("%d",i);return 0;}
	puts("-1");
}
