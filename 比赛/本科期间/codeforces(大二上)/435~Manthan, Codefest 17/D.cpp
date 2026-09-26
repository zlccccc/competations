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

int fa[maxn][20],FA0[maxn][20],FA1[maxn][20];
int dep[maxn],DEP0[maxn],DEP1[maxn];
int lca(int fa[maxn][20],int dep[maxn],int x,int y){
	int i;
	if (dep[x]<dep[y]) swap(x,y);
	rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
	if (x==y) return x;
	rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int main(){
	int i,j,n;
	scanf("%d",&n);
	FOR(i,1,n){
		int f,k;
		scanf("%d%d",&f,&k);
		if (f==-1&&k==-1) continue;
		fa[i][0]=f,dep[i]=dep[f]+1;
		if (k==0) FA0[i][0]=f,DEP0[i]=DEP0[f]+1;
		else FA1[i][0]=f,DEP1[i]=DEP1[f]+1;
		FOR(j,1,20){
			fa[i][j]=fa[fa[i][j-1]][j-1];
			FA0[i][j]=FA0[FA0[i][j-1]][j-1];
			FA1[i][j]=FA1[FA1[i][j-1]][j-1];
		}
	}
	int q;
	scanf("%d",&q);
	while (q--){
		int k,u,v;
		scanf("%d%d%d",&k,&u,&v);
		if (u==v){
			puts("no");
			continue;
		}if (k==1){
			if (u==lca(FA0,DEP0,u,v)) puts("yes");
			else puts("no");
		}else{
			int f=lca(fa,dep,u,v);
			if (f&&lca(FA0,DEP0,u,f)==f&&lca(FA1,DEP1,FA1[v][0],f)==f) puts("yes");
			else puts("no");
		}
	}
}
/*
*/
