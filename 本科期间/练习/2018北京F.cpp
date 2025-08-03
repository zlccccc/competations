#include <sstream>
#include <fstream>
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
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=50000+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

bitset<50001> BIT[maxn];
vector<int> edge[maxn];
vector<int> nodes[maxn];
int cnt=0,tot=0;
int id[maxn],dfn[maxn],low[maxn];
int S[maxn],top,vis[maxn];
inline void tarjan(int x) {
	low[x]=dfn[x]=++tot;
	S[++top]=x; vis[x]=1;
	for (int v:edge[x]) {
		if (!dfn[v]) {
			tarjan(v); 
			low[x]=min(low[x],low[v]);
		} else if (vis[v])
			low[x]=min(low[x],dfn[v]);
	} if (low[x]==dfn[x]) {
		cnt++;
		while (1) {
			int now=S[top--];
			vis[now]=0; id[now]=cnt;
			nodes[cnt].push_back(now);
			if (now==x) break;
		}
	}
}
queue<int> Q; int d[maxn];
int CNT[maxn],C[65536];
int main() {
	int _t,T; scanf("%d",&T);
	int i; REP(i,65536) C[i]=C[i>>1]+(i&1);
	FOR(_t,1,T) {
		int i;
		scanf("%d%d%d",&n,&m,&q);
		cnt=tot=0; top=0;
		FOR(i,1,n) {
			dfn[i]=d[i]=vis[i]=0; BIT[i].reset();
			edge[i].clear(); nodes[i].clear();
		} FOR(i,1,m) {
			int u,v;
			scanf("%d%d",&u,&v);
			edge[v].push_back(u);
		} FOR(i,1,n) if (!dfn[i]) tarjan(i);
		FOR(i,1,n) {
			BIT[id[i]].set(i);
			for (int v:edge[i]) if (id[v]!=id[i]) d[id[v]]++;
		} FOR(i,1,cnt) if (!d[i]) Q.push(i);
		while (Q.size()) {
			int x=Q.front(); Q.pop();
			for (int u:nodes[x]) {
				for (int v:edge[u]) if (id[u]!=id[v]){
					d[id[v]]--; if (!d[id[v]]) Q.push(id[v]);
					BIT[id[v]]=BIT[id[v]]|BIT[x];
				}
			}
		}
		// int j;
		// FOR(i,1,n) {
		// 	FOR(j,1,n) printf("%d",(int)BIT[id[i]][j]); puts("");
		// }
		// FOR(i,1,n) {
		// 	FOR(j,1,n) if (BIT[id[i]][j]) printf("%d->%d\n",i,j);
		// }
		FOR(i,0,n) CNT[i]=0;
		FOR(i,1,n) {
			int j; unsigned short *ptr=(unsigned short*)&BIT[id[i]];
			FOR(j,0,(n>>4)) if (ptr[j]) CNT[(i>>4)^j]+=C[ptr[j]];
		}
		while (q--){
			int k;
			scanf("%d",&k);
			int l=0,r=n+n;
			while(l+1<r){
				int mid=(l+r)/2;
				ll nowcnt=0;
				rFOR(i,(mid>>4)+1,n) nowcnt+=CNT[i];
				FOR(i,1,n) if (((i>>4)^(mid>>4))<=(n>>4)){
					int j; unsigned short *ptr=(unsigned short*)&BIT[id[i]];
					unsigned short t=ptr[(i>>4)^(mid>>4)];
					REP(j,16) if (((t>>j)&1)&&((j^(i&15))>=(mid&15))) nowcnt++;
				}
				// printf(" gett %d : %lld\n",mid,nowcnt);
				if (nowcnt<k) r=mid;
				else l=mid;
			} printf("%d\n",l);
		}
	}
}
/*
*/
