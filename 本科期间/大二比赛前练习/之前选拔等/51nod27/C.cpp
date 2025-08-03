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
queue<int> Q;
int T;
int main()
{
	LL x,k,y;
	scanf("%d",&T);
	while (T--){
		scanf("%lld%lld",&x,&k);
		y=sqrt(x);if (y*y<x) y++;if (y*y>x) y--;
		if (x==0) puts("0");
		else if (k==1){
			if (y*y+1>x) printf("%lld\n",2*y-1);
			else printf("%lld\n",2*y);
		}else{
			if (x==1||x==3) puts("-1");
			else if (x==2) puts("1");
			else if (x==5) puts("3");
			else if (y*y+2>x) printf("%lld\n",2*y-2);
			else printf("%lld\n",2*y-1); 
		}
	}
}
/*
*/
