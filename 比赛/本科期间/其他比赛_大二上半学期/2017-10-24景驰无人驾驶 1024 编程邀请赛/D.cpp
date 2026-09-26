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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int fa[maxn],mark[maxn];
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
priority_queue<int> now,all;
struct node{
	int u,v,len;
};
int cmp(node a,node b){
	return a.len<b.len;
}
LL ans,cnt;
vector<int> H;
vector<node> N[5007];
void solve(){
	int n,m,t,w,i,j;
	scanf("%d%d%d%d",&n,&m,&t,&w);
	FOR(i,1,m) N[i].clear();
	FOR(i,1,n){
		node e;int d;
		scanf("%d%d%d%d",&d,&e.u,&e.v,&e.len);
		N[d].push_back(e);
	}
	cnt=ans=0;
	FOR(i,1,m){
		int p;
		scanf("%d",&p);
		H.clear();
		for (auto e:N[i]) H.push_back(e.u),H.push_back(e.v);
		sort(H.begin(),H.end());H.erase(unique(H.begin(),H.end()),H.end());
		FOR(j,1,H.size()) fa[j]=j,mark[j]=0;
		sort(N[i].begin(),N[i].end(),cmp);
		for (auto &e:N[i]){
			int u=lower_bound(H.begin(),H.end(),e.u)-H.begin()+1;
			int v=lower_bound(H.begin(),H.end(),e.v)-H.begin()+1;
			int x=getfa(u),y=getfa(v);
//			printf("%d,%d-->u,v=%d %d;%d %d\n",e.u,e.v,u,v,x,y);
			if (x!=y){
				cnt++;fa[x]=y;
				ans=ans+e.len;
				now.push(e.len);
				e.len=-1;
			}
		}
		for (auto &e:N[i]){
			if (e.len==-1) continue;
			int u=lower_bound(H.begin(),H.end(),e.u)-H.begin()+1;
			int v=lower_bound(H.begin(),H.end(),e.v)-H.begin()+1;
			int x=getfa(u),y=getfa(v);
//			printf("%d,%d-->u,v=%d %d;%d %d\n",e.u,e.v,u,v,x,y);
			if (!mark[x]){
				cnt++;ans=ans+e.len;
				mark[x]=1;
				now.push(e.len);
			}
		}
		while (now.size()&&p--) all.push(now.top()),now.pop();
		while (now.size()) now.pop();
	}
	while (all.size()&&w--) ans-=all.top(),all.pop();
	while (all.size()) all.pop();
	printf("%lld\n%lld\n",cnt,ans);
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/
