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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int head[maxn];
struct node{
	int to,next;
	LL len;
	node(int _to=0,LL _len=0,int _next=0):to(_to),len(_len),next(_next){}
	bool operator < (const node &A)const{
		if (len==A.len) return to<A.to;
		return len>A.len;
	}
}edge[maxn];
priority_queue<node> Q;
vector<int> q[maxn];
LL d[maxn];
int g[maxn];
int main(){
	int n,m,T;
	int i,j;
	scanf("%d%d%d",&n,&m,&T);
	memset(head,0xff,sizeof(head));
	FOR(i,1,m){
		int u,v,len;
		scanf("%d%d%d",&u,&v,&len);
		edge[i]=node(v,len,head[u]);head[u]=i;
	}
	memset(d,0x3f,sizeof(d));d[1]=0;
	Q.push(node(1,0));
	while (Q.size()){
		node x=Q.top();Q.pop();
		if (x.len>d[x.to]) continue;
		for (int i=head[x.to];i!=-1;i=edge[i].next){
			node &y=edge[i];
			if (d[y.to]>d[x.to]+y.len){
				d[y.to]=d[x.to]+y.len;
				Q.push(node(y.to,d[y.to]));
			}
		}
	}
	while (T--){
		int k;
		scanf("%d",&k);
		if (k==1){
			int v;
			scanf("%d",&v);
			if (d[v]==INFF) puts("-1");
			else printf("%I64d\n",d[v]);
		}else{
			int c;
			scanf("%d",&c);
			REP(i,c){
				int l;
				scanf("%d",&l);
				edge[l].len++;
			}
			memset(g,0x3f,sizeof(g));
			q[0].emplace_back(1);g[1]=0;
			int len;
			FOR(len,0,c){
				if (q[len].empty()) break;
				REP(i,q[len].size()){
					int v=q[len][i];
					if (len>g[v]) continue;
					for (int i=head[v];i!=-1;i=edge[i].next){
						int y=edge[i].to,l=edge[i].len,L=-d[y]+d[v]+g[v]+l;
						if (g[y]>L){
							g[y]=L;
							if (g[y]<=min(n-1,c)) q[g[y]].emplace_back(y);
						}
					}
				}
				q[len].clear();
			}
			FOR(i,1,n) if (d[i]!=INFF) d[i]+=g[i];
		}
	}
}
/*
*/
