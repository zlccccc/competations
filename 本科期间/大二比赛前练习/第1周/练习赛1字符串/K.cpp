#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e6+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;

int n,k;
int nxt[maxn];
char a[maxn];
int i,j;
int main(){
	scanf("%d%d",&n,&k);
	scanf("%s",a);
	nxt[0]=-1;
	rep(i,1,n){
		j=nxt[i-1];
		while (j>=0&&a[j+1]!=a[i]) j=nxt[j];
		if (a[i]==a[j+1]) nxt[i]=j+1;
		else nxt[i]=-1;
	}
	REP(i,n){
		int num=(i+1)/(i-nxt[i]);//¸öÊý 
		if (num%k==0) putchar('1');//b=""
		else if (num/k-num%k-((i+1)%(i-nxt[i])!=0)>=0) putchar('1');
		else putchar('0');
	}
}
