#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=4e5+7;
const double eps=0.00000001;
const LL INF=0x3f3f3f3f;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b){
	LL ret=1;
	while (b){
		if (b&1) ret=ret*a%M;
		a=a*a%M;
		b>>=1;
	}
	return ret;
}
const LL MID=2e5;
const LL MAX=4e5;
struct BIT{
	int num[maxn];
	LL mul[maxn];
	inline int lowbit(int x){return x&-x;}
	void insert(int x,LL val){
		while (x<=MAX){
			num[x]++;
			mul[x]=mul[x]*val%M;
			x+=lowbit(x);
		}
	}
	LL calnum(int x){
		LL ret=0;
		for (;x;x-=lowbit(x)) ret=ret+num[x];
		return ret;
	}
	LL calmul(int x){
		LL ret=1;
		for (;x;x-=lowbit(x)) ret=ret*mul[x]%M;
		return ret;
	}
	void init(int x){
		while (x<=MAX){
			num[x]=0;
			mul[x]=1;
			x+=lowbit(x);
		}
	}
	BIT(){
		int i;
		FOR(i,1,MAX) mul[i]=1,num[i]=0;
	}
}bitA,bitB;
vector<int> edge[maxn];
vector<int> col[maxn];
vector<LL> len[maxn];
bool mark[maxn];
int sz[maxn];
int minweight,root;
int dfs1(int x,int fa,int n){
	int weight=0;
	sz[x]=1;
	for (int v:edge[x]){
		if (v==fa||mark[v]) continue;
		dfs1(v,x,n);
		sz[x]+=sz[v];
		weight=max(weight,sz[v]);
	}
	weight=max(weight,n-sz[x]);
	if (weight<minweight) {root=x;minweight=weight;}
}
LL ans1,ans2;
vector<pair<int,LL> > nowA,nowB;
void dfs2(int x,int fa,int B,int R,LL val){
	nowA.push_back(make_pair(R-2*B,val));
	nowB.push_back(make_pair(R*2-B,val));
	int i,v;
	REP(i,edge[x].size()){
		v=edge[x][i];
		if (v==fa||mark[v]) continue;
		if (col[x][i]==0) dfs2(v,x,B+1,R,val*len[x][i]%M);
		if (col[x][i]==1) dfs2(v,x,B,R+1,val*len[x][i]%M);
	}
	ans1=ans1*powMM(val,bitA.calnum(2*B-R+MID))%M;//2B-R>=r-2b
	ans1=ans1*bitA.calmul(2*B-R+MID)%M;//2B-R>=r-2b
	ans2=ans2*powMM(val,bitB.calnum(B-R*2-1+MID))%M;//B-2R>2r-b
	ans2=ans2*bitB.calmul(B-R*2-1+MID)%M;//2B-R>=r-2b
}
vector<int> allA,allB;
void calc(int x){
	int i,v;
	bitA.insert(MID,1);
	bitB.insert(MID,1);
	REP(i,edge[x].size()){
		v=edge[x][i];
		if (mark[v]) continue;
		if (col[x][i]==0) dfs2(v,0,1,0,len[x][i]);
		if (col[x][i]==1) dfs2(v,0,0,1,len[x][i]);
		for (pair<int,LL> now:nowA) allA.push_back(now.first),bitA.insert(now.first+MID,now.second);
		for (pair<int,LL> now:nowB) allB.push_back(now.first),bitB.insert(now.first+MID,now.second);
		nowA.clear();
		nowB.clear();
	}
	for (int del:allA) bitA.init(del+MID);
	for (int del:allB) bitB.init(del+MID);
	bitA.init(MID);
	bitB.init(MID);
	allA.clear();
	allB.clear();
}
void dfs3(int x){
	mark[x]=1;
	calc(x);
	for (int v:edge[x]){
		if (mark[v]) continue;
		minweight=sz[v];
		dfs1(v,0,sz[v]);
		dfs3(root);
	}
}
int n,m;
int i,j;
int u,v;
int main(){
	scanf("%d",&n);
	REP(i,n-1){
		int u,v,c;
		LL x;
		scanf("%d%d%I64d%d",&u,&v,&x,&c);
		edge[u].push_back(v);
		len[u].push_back(x);
		col[u].push_back(c);
		edge[v].push_back(u);
		len[v].push_back(x);
		col[v].push_back(c);
	}
	FOR(i,1,MAX) bitA.mul[i]=1,bitA.num[i]=0;
	FOR(i,1,MAX) bitB.mul[i]=1,bitB.num[i]=0;
	minweight=n;
	dfs1(1,0,n);
	ans1=ans2=1;
	dfs3(root);
	printf("%I64d\n",ans1*powMM(ans2,M-2)%M);
}
/*
5
1 2 9 0
2 3 5 1
2 4 5 0
2 5 5 1
*/
