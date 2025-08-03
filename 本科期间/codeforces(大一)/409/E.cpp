#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
#include <cmath>
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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
void exgcd(LL a,LL b,LL &x,LL &y){
	if (!b) {x=1;y=0;}
	else {exgcd(b,a%b,y,x);y-=a/b*x;} 
}
int n,m;
int i,j;
bool used[maxn];
vector<int> v[maxn];
int num[maxn],fa[maxn],mx;
int pre=1;
void print(int mx){
	if (fa[mx]) print(fa[mx]);
	LL a,b,t;
	REP(i,v[mx].size()){
		exgcd(pre,m,a,b);
		printf("%I64d ",(v[mx][i]/gcd(pre,m)*a%m+m)%m);
		pre=v[mx][i];
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	REP(i,n) scanf("%d",&j),used[j]=1;
	rep(i,1,m) if (!used[i]) v[gcd(i,m)].push_back(i);
	rep(i,1,m){
		if ((num[i]+=v[i].size())>num[mx]) mx=i;
		for (j=i<<1;j<m;j+=i) if (num[j]<num[i]) num[j]=num[i],fa[j]=i;
	}
	printf("%d\n",num[mx]+!used[0]);
	print(mx);
	if (!used[0]) puts("0");
	else puts("");
}
/*
*/
