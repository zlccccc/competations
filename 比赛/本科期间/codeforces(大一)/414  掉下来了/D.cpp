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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1,a*=a) ret=1ll*ret*a%M;return ret;}


int n,m;
vector<int> edge[maxn],K[maxn],H[maxn];
set<int> MP[maxn];
bool used[maxn];
int color[maxn],id[maxn];
int i,j;
int u,v;
int tot;
bool dfs(int x,int c){
	int i;
	if (color[id[x]]) c=color[id[x]];
	color[id[x]]=c;
	used[x]=1;
	REP(i,edge[x].size())
		if (!used[edge[x][i]]) dfs(edge[x][i],c+(id[x]!=id[edge[x][i]]));
}
int main(){
	scanf("%d%d",&n,&m);
	REP(i,m){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	FOR(i,1,n){
		K[i]=edge[i];
		K[i].push_back(i);
		sort(K[i].begin(),K[i].end());
		H[i-1]=K[i];
	}
	sort(H,H+n);tot=unique(H,H+n)-H;
	FOR(i,1,n) id[i]=lower_bound(H,H+tot,K[i])-H;
	FOR(i,1,n){
		REP(j,K[i].size()){
				MP[id[i]].insert(id[K[i][j]]);
				MP[id[K[i][j]]].insert(id[i]);
			}
	}
//	FOR(i,1,n) printf("%d ",id[i]);puts("");
//	REP(i,tot) printf("%d ",MP[i].size());puts("");
	REP(i,tot) if (MP[i].size()>3) return 0*puts("NO");
	FOR(i,1,n)
		if (MP[id[i]].size()<=2){
			dfs(i,1);
			break;
		}
	puts("YES");
	FOR(i,1,n) printf("%d ",color[id[i]]);
}
/*
*/
