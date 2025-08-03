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
const LL maxn=5000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,k;
vector<int> edge[maxn];
int root[maxn],val[maxn];
int cnt;
void dfs(int x,int fa,int should){
	val[x]=0;
	for (int v:edge[x]) if (v!=fa){
		dfs(v,x,should);
		if (val[v]==should) cnt++;
		else val[x]=max(val[x],val[v]+1);
	}
}
int i,j;
int main(){
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%d",&k);
		n=0;
		FOR(i,1,k){
			int now;
			scanf("%d%d",&now,&root[i]);n+=now;
			FOR(j,1,now-1){
				int u,v;
				scanf("%d%d",&u,&v);
				edge[u].push_back(v);
				edge[v].push_back(u);
			}
		}cnt=0;int N=n;
		FOR(j,1,k) dfs(root[j],0,n);
		FOR(j,1,k) N=min(N,val[root[j]]);
//		printf("%d\n",n);
		rFOR(i,0,N){
			bool mark=1;cnt=0;
			FOR(j,1,k){
				dfs(root[j],0,i);
				if (val[root[j]]!=i){
					mark=0;
					break;
				}
			}if (mark) break;
		}printf("%d %d\n",cnt,i);
		FOR(i,1,n) edge[i].clear();
	}
}
