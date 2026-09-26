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


int n,m;
int i,j,k,kk,t;
int a[maxn];
vector<int> edge[maxn];
int mx;
pair<int,int> dfs(int x,int from,int m3,int m4){
//	printf("%d %d\n",x,from);
	int m1,m2;//m1=max,m2=nextmax
	m1=m3;m2=m4;
	REP(i,edge[x].size())
		if (edge[x][i]!=from){
			pair<int,int> k=dfs(edge[x][i],x);
			if (k.first>m1) m1=k;
			if (k.second>m2) m2=k;
		}
	mx=max(num,m1+1);
	mx=max(num,m2+2);
	return make_pair(a[i],m1);
}
int u,v;
int main()
{
	scanf("%d",&n);
	FOR(i,1,n) {scanf("%d",&a[i]);mx=max(a[i],mx);}
	REP(i,n-1){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(1,0);
	printf("%d",mx);
}
/*
*/
