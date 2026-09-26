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

//喵的我就是个SB 
int n,m;
int i,j,k;
int u,v;
int S[maxn],top;
int head[maxn],nxt[maxn],to[maxn];
int id[maxn];
int a[maxn],fa[maxn],FA[maxn];
int num[maxn];
LL all[maxn],now[maxn];
int tot,cnt;
int low[maxn],dfn[maxn],vis[maxn];
inline void tarjan(int x){
	low[x]=dfn[x]=++tot;
	S[++top]=x;vis[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		int v=to[i];
		if (!dfn[v]){
			tarjan(v);
			low[x]=min(low[x],low[v]);
		}else if (vis[v]){
			low[x]=min(low[x],dfn[v]);
		}
	}if (low[x]==dfn[x]){
		cnt++;
		while (1){
			int now=S[top--];
			vis[now]=0;id[now]=cnt;
			all[cnt]+=a[now];num[cnt]++;
			if (now==x) break; 
		}
	}
}
inline int check(LL x){
	LL ALL=0;int i;
	FOR(i,1,cnt) now[i]=all[i];
	FOR(i,1,cnt){
		if (now[i]<x*num[i]){
			if (FA[i]!=-1){
				now[FA[i]]-=x*num[i]-now[i];
			}else ALL+=x*num[i]-now[i];
		}if (ALL>m) return 0;
	}
//	printf("%d:%d\n",x,ALL);
	return 1;
}
int main(){
//	#define OPENSTACK
//	#ifdef OPENSTACK
//			int size = 256 << 20; // 256MB
//			char *p = (char*)malloc(size) + size;
//			#if (defined _WIN64) or (defined __unix)
//				__asm__("movq %0, %%rsp\n" :: "r"(p));
//			#else
//				__asm__("movl %0, %%esp\n" :: "r"(p));
//			#endif
//	#endif
	scanf("%d%d",&n,&m);
	FOR(i,1,n){
		scanf("%d",&fa[i]);
		if (fa[i]!=-1&&fa[i]!=i){
			to[++tot]=i;
			nxt[tot]=head[fa[i]];
			head[fa[i]]=tot;
		}
//		edge[i].push_back(fa[i]);
	}FOR(i,1,n) scanf("%d",&a[i]);
	FOR(i,1,n) if (!dfn[i]) tarjan(i);
	FOR(i,1,cnt) FA[i]=-1;
	FOR(i,1,n) if (fa[i]!=-1&&id[fa[i]]!=id[i]) FA[id[i]]=id[fa[i]];
//	FOR(i,1,cnt){
//		printf("%d %d;FA=%d\n",all[i],num[i],FA[i]);
//	}puts("");
	LL L=0,R=2000000007;
	while(L+1<R){
		int mid=(L+R)/2;
		if (check(mid)) L=mid;
		else R=mid;
	}printf("%lld\n",L);
	exit(0);
}
/*
*/
