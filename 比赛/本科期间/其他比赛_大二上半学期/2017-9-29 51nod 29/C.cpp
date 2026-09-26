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
#include <bitset>
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

int fa[1007];
vector<int> now[1007];
bitset<100007> val[1007];
int n,k,q;
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
int main(){
	scanf("%d",&n);
	int i;
	FOR(i,1,n){
		scanf("%d",&k);
		fa[i]=i;
		now[i].push_back(k);
		val[i].set(k),val[i].set(0);
	}
	scanf("%d",&q);
	while (q--){
		scanf("%d",&k);
		if (k==1){
			int u,v;
			scanf("%d%d",&u,&v);
			int x=getfa(u),y=getfa(v),K;
			if (now[x].size()>now[y].size()) swap(x,y);
			for (int K:now[x]){
				val[y]=val[y]|(val[y]<<K);
				now[y].push_back(K);
			}
			fa[x]=y;
		}else{
			int K;
			scanf("%d",&K);
			int x=getfa(K);
			printf("%d\n",val[x].count());
		}
	}
}
/*
*/
