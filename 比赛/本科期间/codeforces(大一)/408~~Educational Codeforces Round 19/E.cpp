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
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,m,p;
int i,j,k,t;
int a[100007];
int b[100007][307];
int solve(int p,int k){
	if (p>n) return 0;
	if (k<=300&&b[p][k]) return b[p][k];
	int t=solve(p+a[p]+k,k)+1;
	if (k<=300) b[p][k]=t;
	return t;
}
int main()
{
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]);
	scanf("%d",&m);
	REP(i,m){
		scanf("%d%d",&p,&k);
		printf("%d\n",solve(p,k));
	}
}
