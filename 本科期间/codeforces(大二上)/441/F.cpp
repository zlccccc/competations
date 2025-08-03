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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
	int u,v,val;
}a[maxn];
int n,m;
int i,j,k,t;
int ans;
int fa[maxn],have[maxn];
bool cmp(node a,node b){
	return a.val>b.val;
}
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n) fa[i]=i;
	REP(i,m) scanf("%d%d%d",&a[i].u,&a[i].v,&a[i].val);
	sort(a,a+m,cmp);
	REP(i,m){
		int x=getfa(a[i].u),y=getfa(a[i].v);
		if (x==y&&!have[x]) have[x]=1,ans+=a[i].val;
		else if (x!=y&&(!have[x]||!have[y])) fa[x]=y,have[y]|=have[x],ans+=a[i].val;
	}
	printf("%d\n",ans);
}
/*
*/
