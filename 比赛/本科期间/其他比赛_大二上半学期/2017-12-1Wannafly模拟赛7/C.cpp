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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct _T{
	int val[maxn<<2];
	void update(int x,int pos,int VAL,int L,int R){
		val[x]+=VAL;
		if (L==R) return;
		int mid=(L+R)/2;
		if (pos<=mid) update(x<<1,pos,VAL,L,mid);
		else update(x<<1|1,pos,VAL,mid+1,R);
	}
	LL query(int x,int l,int r,int L,int R){
		if (l<=L&&R<=r) return val[x];
		int mid=(L+R)/2;LL ret=0;
		if (l<=mid) ret+=query(x<<1,l,r,L,mid);
		if (mid<r) ret+=query(x<<1|1,l,r,mid+1,R);
		return ret;
	}
}T[6];
LL p[]={2,3,5,7,11,13};
int in[maxn],out[maxn];
vector<int> edge[maxn];
int tot;
void dfs(int x){
	in[x]=++tot;
	for (int v:edge[x]) dfs(v);
	out[x]=tot;
}int a[maxn];
int n,m;
int i,j,k;
int u,v,q;
char c[10];
int main(){
	scanf("%d",&n);
	FOR(i,1,n-1) scanf("%d%d",&u,&v),edge[u].push_back(v);
	dfs(0);
	FOR(i,0,n-1){
		scanf("%d",&v);
		REP(j,6){
			int cnt=0;
			while (v%p[j]==0) v/=p[j],cnt++;
			T[j].update(1,in[i],cnt,1,n); 
		}
	}scanf("%d",&q);
	while (q--){
		scanf("%s",c);
		if (c[0]=='R'){
			LL ans1=1,ans2=1;int x;
			scanf("%d",&x);
			REP(i,6){
				(ans1*=powMM(p[i],T[i].query(1,in[x],out[x],1,n)))%=M;
				(ans2*=(1+T[i].query(1,in[x],out[x],1,n)))%=M;
			}printf("%lld %lld\n",ans1,ans2);
		}else{
			int x,v;
			scanf("%d%d",&x,&v);
			REP(i,6){
				int cnt=0;
				while (v%p[i]==0) v/=p[i],cnt++;
				T[i].update(1,in[x],cnt,1,n); 
			}
		}
	}
}
/*
*/
