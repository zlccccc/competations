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

#define MP make_pair
typedef pair<int,int> pii;
int i,j,k,n,q;
int fa[maxn];
struct node{
	int u,v,w;
}E[maxn];
vector<int> edge[maxn];
vector<pii> Q[maxn];
int ans[maxn];
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
int F[maxn],T[maxn],id[maxn];
inline int getFA(int x,int now){
	if (id[x]!=now) id[x]=now,F[x]=fa[x];
	if (F[x]==x) return x;
	return F[x]=getFA(F[x],now);
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	REP(i,m){
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
		edge[E[i].w].emplace_back(i);
	}scanf("%d",&q);
	REP(i,q){
		int c;
		scanf("%d",&c);
		while (c--){
			int pos;
			scanf("%d",&pos);pos--;
			Q[E[pos].w].push_back(MP(pos,i));
		}ans[i]=1;
	}FOR(i,1,500000) fa[i]=i,F[i]=i,id[i]=-1;
	FOR(i,1,500000){
		for (auto &now:Q[i]){
			int u=E[now.first].u,v=E[now.first].v,pos=now.second;
			int x=getfa(u),y=getfa(v);
			if (getFA(x,pos+n*i)==getFA(y,pos+n*i)) ans[pos]=0;
			F[getFA(x,pos+n*i)]=getFA(y,pos+n*i);
//			printf("ask:len=%d;u,v=%d %d;x,y=%d %d,F=%d %d,pos=%d\n",i,u,v,x,y,F[x],F[y],pos);
//			printf("FA=%d %d\n",getFA(x),getFA(y));
		}for (auto &now:edge[i]){
			int x=getfa(E[now].u),y=getfa(E[now].v);
			if (x==y) continue;
			fa[x]=y;
		}
	}REP(i,q) if (ans[i]) puts("YES");
	else puts("NO");
}
/*
*/
