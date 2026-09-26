#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int a[maxn],b[maxn];
int mark[maxn],cnt;
vector<int> ans[maxn];
void dfs(int x){
	mark[x]=1;ans[cnt].push_back(x);
	if (!mark[b[x]]) dfs(b[x]);
}
int cmp(int x,int y){
	return a[x]<a[y];
}
int main(){
	int n,m,k;
	int i,j;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]),b[i]=i;
	sort(b+1,b+1+n,cmp);
//	FOR(i,1,n) printf("%d ",b[i]);
	FOR(i,1,n) if (!mark[i]) cnt++,dfs(i);
	printf("%d\n",cnt);
	FOR(i,1,cnt){
		printf("%d",ans[i].size());
		for (int now:ans[i]) printf(" %d",now);
		puts("");
	}
}
/*
*/
