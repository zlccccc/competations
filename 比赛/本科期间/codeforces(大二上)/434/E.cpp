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
#include <unordered_map>
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
const LL maxn=5e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

#define pos first
#define cnt second
#define MP make_pair
map<int,pair<int,int> > NOW[maxn];//map¸ü¿ìÎªÉ¶ÄØ 
vector<pair<int,int> > E[maxn];
bool start[maxn];
vector<int> edge[maxn];
LL preans[maxn],ans[maxn];
void dfs(int x,int dep=0){//check
	printf("down %d dep=%d\n",x,dep);
	for (int v:edge[x]) dfs(v,dep+1);
	printf("up\n");
}
int dfs1(int x,int depth){
	int ret=x;//ret_pos
	NOW[ret][depth]=MP(x,1);
	for (int v:edge[x]){
		int add=dfs1(v,depth+1);
		if (NOW[ret].size()<NOW[add].size()) swap(ret,add);
		for (pair<int,pair<int,int> > now:NOW[add]){//v->ret
			if (!NOW[ret].count(now.first)) NOW[ret][now.first]=now.second;
			else{
				pair<int,int> A=NOW[ret][now.first],B=now.second;//B->A
				preans[A.pos]+=B.cnt*(depth+1);
				preans[B.pos]+=A.cnt*(depth+1);
				E[A.pos].push_back(MP(B.pos,preans[B.pos]-preans[A.pos]));
//				printf("ADD:%d->%d,val=%d\n",A.pos,B.pos,preans[B.pos]-preans[A.pos]);
				start[B.pos]=0;
				NOW[ret][now.first]=MP(A.pos,A.cnt+B.cnt);
			}
		}
		map<int,pair<int,int> >().swap(NOW[add]);
	}
	return ret;
}
void dfs2(int x){
	for (pair<int,int> now:E[x]){
		int v=now.first;
		preans[v]=preans[x]+now.second;
//		printf("dfs2:%d->%d\n",x,v); 
		dfs2(v);
	}
}
void dfs3(int x,int fa,int depth){
	ans[x]=ans[fa]+depth+preans[x];
	for (int v:edge[x]) dfs3(v,x,depth+1);
}
int root;
int main(){
	int n,m,i,j,f;
	scanf("%d",&n);
	FOR(i,1,n){
		scanf("%d",&f);
		if (f==0) root=i;
		else edge[f].push_back(i);
	}
//	dfs(root);
	FOR(i,1,n) start[i]=1;
	dfs1(root,0);
//	FOR(i,1,n) printf("%d ",preans[i]);puts("");
	FOR(i,1,n) if (start[i]) dfs2(i);
//	FOR(i,1,n) printf("%d ",preans[i]);puts("");
	dfs3(root,0,0);
	FOR(i,1,n) printf("%I64d ",ans[i]);
}
/*
*/
