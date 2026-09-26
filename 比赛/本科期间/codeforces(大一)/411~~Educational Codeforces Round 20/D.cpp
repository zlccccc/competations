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


int n,m;
int i,j,k;
int a[maxn],tot;
bool judge(int x){
	int len,i,num;
	len=0;num=1;
	REP(i,tot-1){
		if (a[i]+1>x) return 0;
		if (len+a[i]+1>x) num++,len=0;
		len+=a[i]+1;
//				printf("len=%d  ",len);
	}
	if (len+a[i]>x) num++;
	if (a[i]>x) return 0;
//	printf("%d %d %d\n",x,n,num);
	return num<=n;
}
int l,r,mid;
char c;
int main(){
	scanf("%d",&n);getchar();
	tot=0;
	while (c=getchar()){
//		printf("%d",tot);
		if (c==EOF) break;
		if (c=='\n') break;
		if (c==' '||c=='-') {if (a[tot]!=0) tot++;}
		else a[tot]++;
	}
	tot++;
//	REP(i,tot) printf("%d ",a[i]);
	l=0;r=INF;
	while (l+1<r){
		mid=(l+r)/2;
		if (!judge(mid)) l=mid;
		else r=mid;
	}
	printf("%d",l+1);
}
/*
*/
