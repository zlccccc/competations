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
const LL maxn=4e5+107;
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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int k;
vector<int> edge[maxn];
int dep[maxn],len[maxn],fa[maxn],son[maxn];
bool vis[maxn];
void dfs(int x,int depth) {//建bfs树
	vis[x]=1; dep[x]=depth;
	for (int v:edge[x]) if (!vis[v]){
		fa[v]=x; dfs(v,depth+1); 
		if (len[v]>len[son[x]]) son[x]=v;
	} len[x]=len[son[x]]+1;
}
void getcircle(int x) {
	vis[x]=1; bool isleaf=1;
	for (int v:edge[x]) if (!vis[v]){
		getcircle(v); isleaf=0;
		if (dep[v]>dep[son[x]]) son[x]=v;
	}
	// if (isleaf) printf("isleaf:%d\n",x);
	if (isleaf&&k) {
		vector<int> more;
		for (int v:edge[x]) if (v!=fa[x]){
			if ((dep[x]-dep[v]+1)%3!=0) {
				k--; vector<int> now;
				for (;x!=v;x=fa[x]) now.push_back(x);
				now.push_back(v);
				printf("%d\n",(int)now.size());
				for (int v:now) printf("%d ",v);
				puts(""); return;
			} else more.push_back(v);
		}
		k--; vector<int> now;
		int u=more[0],v=more[1];
		if (dep[u]>dep[v]) swap(u,v);
		now.push_back(x);
		for (;v!=u;v=fa[v]) now.push_back(v);
		now.push_back(u);
		printf("%d\n",(int)now.size());
		for (int v:now) printf("%d ",v);
		puts(""); return;
	}
}
int main() {
	int n,m;
	int i;
	scanf("%d%d%d",&n,&m,&k);
	FOR(i,1,m){
		int u,v; scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} dfs(1,1);
	if (len[1]>=n/k) {
		puts("PATH");
		printf("%d\n",len[1]);
		for (i=1;len[1];len[1]--,i=son[i]) printf("%d ",i);
	} else {
		puts("CYCLES");
		FOR(i,1,n) vis[i]=0;
		getcircle(1);
	}
}
/*
4 6 1
1 2
1 3
1 4
2 3
2 4
3 4
*/