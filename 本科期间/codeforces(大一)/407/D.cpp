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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

LL n,m;
LL i,j;
vector<int> edge[maxn];
bool haveedge[maxn];
bool used[maxn];
void dfs(int u){
	used[u]=1;
	int i;
	REP(i,edge[u].size()){
		int v=edge[u][i];
		if (!used[v]) dfs(v);
	}
}
bool mark;
int k; 
LL ans,circle;
int u,v;
int main()
{
	scanf("%d%d",&n,&m);
	REP(i,m){
		scanf("%d%d",&u,&v);
		haveedge[u]=haveedge[v]=1;
		if (v==u){
			circle++;
			continue;
		}
		edge[u].push_back(v);
		edge[v].push_back(u);
		k++;
	}
	mark=0;
	FOR(i,1,n){
		if (!used[i]){
			if (haveedge[i]){
				if (mark){
					puts("0");
					return 0;
				}
				mark=1;
			}
			dfs(i);
		}
	}
	/*原图2m边,去掉两条如果不是相邻的,必定没有欧拉回路,因为回不来了*/
	FOR(i,1,n) ans+=1ll*edge[i].size()*(edge[i].size()-1)/2;
	ans+=1ll*circle*(circle-1)/2;//任选两条自环边没问题 
	ans+=1ll*circle*k;//任选一条自环边和一条其他边没问题 
	printf("%I64d",ans);
}
