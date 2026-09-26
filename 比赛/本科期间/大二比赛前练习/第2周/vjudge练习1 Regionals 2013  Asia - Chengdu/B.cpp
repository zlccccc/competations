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
stack<string> S;
string now;
int len;
int main()
{
	int x=0;
	ans[0]=1;
	FOR(i,1,100) ans[i]=ans[i-1]*1000.0/1024.0;
	scanf("%d",&T);
	while (T--){
		getchar();
		while (1){
			t=getchar();
			if (t==9||t==32||t==10){
				while (t==9||t==32||t==10) t=getchar();
				printf(" ");
			}
			
		}
	}
    return 0;
}
/*
*/
