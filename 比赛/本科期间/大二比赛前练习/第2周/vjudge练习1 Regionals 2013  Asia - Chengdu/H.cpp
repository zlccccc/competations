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
const double eps=0.000001;

int n,i,T;
char S[100000];
double ans[10000];
int len;
int main()
{
	int x=0;
	ans[0]=1;
	FOR(i,1,100) ans[i]=ans[i-1]*1000.0/1024.0;
	scanf("%d",&T);
	while (T--){
		scanf("%s",S);
		len=strlen(S);
		printf("Case #%d: ",++x);
		if (S[len-3]=='[') printf("%.2lf%%",(1.0-ans[0])*100);
		if (S[len-3]=='K') printf("%.2lf%%",(1.0-ans[1])*100);
		if (S[len-3]=='M') printf("%.2lf%%",(1.0-ans[2])*100);
		if (S[len-3]=='G') printf("%.2lf%%",(1.0-ans[3])*100);
		if (S[len-3]=='T') printf("%.2lf%%",(1.0-ans[4])*100);
		if (S[len-3]=='P') printf("%.2lf%%",(1.0-ans[5])*100);
		if (S[len-3]=='E') printf("%.2lf%%",(1.0-ans[6])*100);
		if (S[len-3]=='Z') printf("%.2lf%%",(1.0-ans[7])*100);
		if (S[len-3]=='Y') printf("%.2lf%%",(1.0-ans[8])*100);
		puts("");
	}
    return 0;
}
/*
*/
