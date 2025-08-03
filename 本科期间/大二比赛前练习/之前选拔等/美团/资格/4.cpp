#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


int n,m;
int i,j;
char c;
int a[maxn],b[maxn];
int mark[maxn];
int next[maxn];
vector<int> edge[maxn];
int now;
string ans;
void dfs(int x){
	if (mark[x]) return;
	mark[x]=1;
	for (int v:edge[x]) dfs(v);
}
int main(){
	scanf("%d",&n);
	REP(i,n) scanf("%d",&a[i]);
	REP(i,n) scanf("%d",&b[i]);
	REP(i,n) if (i+a[i]>=0&&i+a[i]<=n+1) edge[i+a[i]].push_back(i);
	REP(i,n) if (i+b[i]>=0&&i+b[i]<=n+1) edge[i+b[i]].push_back(i);
	dfs(n-1);
	if (!mark[0]) return 0*puts("No solution!");
	now=0;
	while (now!=n-1){
		if (ans.length()>1000000) return 0*puts("Infinity!");
		if (now+a[now]>=0&&now+a[now]<=n-1&&mark[now+a[now]]) {ans+='a';now=now+a[now];}
		else {ans+='b';now=now+b[now];}
	}
	cout<<ans;
}
/*
*/
