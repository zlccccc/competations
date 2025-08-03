#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const LL eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a) {return a>0?a:-a;}

int n,m;
int i,j,k;
LL now[maxn],all;
LL a[maxn];
LL val,cnt;
int main(){
	while (~scanf("%lld",&val)) a[++n]=val;
//	FOR(i,1,n) printf("%d ",a[i]);
	FOR(i,1,n){
		if (a[i]>=10000) val=a[i]-10000,cnt=5;
		else if (a[i]<0) val=a[i],cnt=0;
		else val=a[i],cnt=1;
//		printf("i=%d, val=%d, cnt=%d, all=%d;;a[i]=%d\n",i,val,cnt,all,a[i]);
		int pos=upper_bound(now,now+all,val)-now;
		REP(j,cnt) {now[pos+j]=val;if (all==pos+j) all++;}
	}
//	REP(i,all) printf("%d ",now[i]);
	printf("%lld\n",all);
}
/*
*/
