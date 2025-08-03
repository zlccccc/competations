#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
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
const LL maxn=4e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

#define MP make_pair
typedef pair<int,int> pii;
int T;
vector<int> edge[maxn];
int size[maxn],val[maxn],fa[maxn];
pii getfa(int x){
	int ret=x,color=val[ret];
	while (fa[ret]!=ret) ret=fa[ret],color^=val[ret];
	return MP(ret,color);
}int ans[maxn];
vector<pii> back[maxn];
int u[maxn],v[maxn];
void solve(int X,int l,int r){
	if (l==r) return;
	int mid=(l+r)/2,i;
	bool flag=0;
	FOR(i,mid+1,r){
		pii x=getfa(u[i]),y=getfa(v[i]);
		if (x.first==y.first){
			if (x.second==y.second){flag=1;break;}
		}else{
			if (size[x.first]>size[y.first]) swap(x,y);
			back[X].push_back(MP(x.first,x.second^y.second));
			fa[x.first]=y.first;
			size[y.first]+=size[x.first];
			val[x.first]^=x.second^y.second;
		}
	}if (flag){
		FOR(i,l,mid) ans[i]=0;
	}else solve(X<<1,l,mid);
	for (pii u:back[X]){
		size[fa[u.first]]-=size[u.first];
		fa[u.first]=u.first;
		val[u.first]^=u.second;
	}vector<pii>().swap(back[X]);
	flag=0;
	FOR(i,l,mid){
		pii x=getfa(u[i]),y=getfa(v[i]);
		if (x.first==y.first){
			if (x.second==y.second){flag=1;break;}
		}else{
			if (size[x.first]>size[y.first]) swap(x,y);
			back[X].push_back(MP(x.first,x.second^y.second));
			fa[x.first]=y.first;
			size[y.first]+=size[x.first];
			val[x.first]^=x.second^y.second;
		}
	}if (flag){
		FOR(i,mid+1,r) ans[i]=0;
	}else solve(X<<1|1,mid+1,r);
	for (pii u:back[X]){
		size[fa[u.first]]-=size[u.first];
		fa[u.first]=u.first;
		val[u.first]^=u.second;
	}vector<pii>().swap(back[X]);
}int n,m,i;
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,m) scanf("%d%d",&u[i],&v[i]),ans[i]=1;
	FOR(i,1,n) fa[i]=i,val[i]=size[i]=1;
	solve(1,1,m);
	int ANS=0;
	FOR(i,1,m) ANS+=ans[i];
	if (ANS==0) return 0*puts("0");
	printf("%d\n",ANS);
	FOR(i,1,m) if (ans[i]){
		printf("%d",i);ANS--;
		if (ANS) putchar(' ');
	}
}
/*
*/
