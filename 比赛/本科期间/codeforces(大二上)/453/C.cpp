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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,q;
vector<int> edge[maxn];
vector<pair<int,int> > Q[maxn];
LL L[maxn],A[maxn];
int low[maxn],dfn[maxn];
bool vis[maxn];
int tot,cnt;
stack<int> S;
void tarjan(int x,int f){
	low[x]=dfn[x]=++tot;
	S.push(x);vis[x]=1;
	for (int v:edge[x]) if (f!=v){
		if (!dfn[v]){
			tarjan(v,x);
			low[x]=min(low[x],low[v]);
		}else if (vis[v]){
			low[x]=min(low[x],dfn[v]);
		}
	}if (low[x]==dfn[x]){
		int MIN,MAX,NUM=0;
		MAX=0;MIN=n;
		while (1){
			int now=S.top();S.pop();
			vis[now]=0;NUM++;
			MAX=max(MAX,now);MIN=min(MIN,now);
			if (now==x) break;
		}if (NUM>2) L[MAX]=MIN;
	}
}
int i,j,k;
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,m){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].emplace_back(v);
		edge[v].emplace_back(u);
	}FOR(i,1,n) if (!dfn[i]) tarjan(i,0);
	FOR(i,1,n) L[i]=max(L[i],L[i-1]);
	FOR(i,1,n) A[i]=A[i-1]+i-L[i];
//	FOR(i,1,n) printf("%d ",L[i]);puts("");
//	FOR(i,1,n) printf("%d ",A[i]);puts("");
	scanf("%d",&q);
	REP(i,q){
		LL l,r;
		scanf("%I64d%I64d",&l,&r);
		LL x=lower_bound(L+l+1,L+n+1,l)-L;
		LL ans=0;
		if (x<=r){
			ans+=A[r]-A[x-1];
			ans+=(x-l)*(x-l+1)/2;
		}else{
			ans+=(r-l+1)*(r-l+2)/2;
		}printf("%I64d\n",ans);
	}
}
/*
6 6
1 2
2 3
3 1
4 5
5 6
6 4
3
1 3
4 6
1 6
*/
