#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
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


int n,k,d;
int i,j,t;
int a[maxn];
vector<int> edge[maxn];
int from[maxn];
bool ans[maxn],mark[maxn];
int num;
queue<int> Q;
int u,v;
int XOR[maxn];
int main()
{
	scanf("%d%d%d",&n,&k,&d);
	FOR(i,1,k) {scanf("%d",&j);if (!mark[j]) Q.push(j);mark[j]=1;}
	FOR(i,1,n) ans[i]=0;
	FOR(i,1,n-1){
		scanf("%d%d",&u,&v);
		edge[u].push_back(i);
		edge[v].push_back(i);
		XOR[i]=u^v;
	}
	while (!Q.empty()){
		u=Q.front();Q.pop();
		REP(i,edge[u].size()){
			t=edge[u][i];
			v=XOR[t]^u;
			if (from[u]==v) continue;
			if (mark[v]) ans[t]=1;
			else{
				from[v]=u;
				mark[v]=1;
				Q.push(v);
			}
		}
	}
	FOR(i,1,n) num+=ans[i];
	printf("%d\n",num);
	FOR(i,1,n) if (ans[i]) printf("%d ",i);
}
