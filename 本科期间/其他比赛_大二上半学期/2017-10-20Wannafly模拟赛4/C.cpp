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
//LL ...卡死我了 
int sum[32][maxn];
int val[32][maxn];
LL F[maxn];
int n;
inline int lowbit(int x){return x&-x;}
int presum(int x,int i){
	int ret=0;
	for (;x;x-=lowbit(x)) ret+=sum[i][x];
	return ret;
}
int query(int l,int r,int i){
	return presum(r,i)-presum(l-1,i);
}
void add(int x,int val,int i){//修改不如add有效 
	for (;x<=n;x+=lowbit(x)) sum[i][x]+=val;
}
int i,j,m;
int main(){
	scanf("%d",&n);
	FOR(j,1,n){
		int VAL;
		scanf("%d",&VAL);
		FOR(i,0,30) val[i][j]=((VAL>>i)&1);
		FOR(i,0,30) if (val[i][j]) add(j,val[i][j],i);
	}
	scanf("%d",&m);
	F[0]=0;
	FOR(i,1,100000) F[i]=(F[i-1]*2+1)%M;
	while (m--){
		int k;
		scanf("%d",&k);
		if (k==1){
			int x,VAL;
			scanf("%d%d",&x,&VAL);
			FOR(i,0,30){
				if (val[i][x]) add(x,-val[i][x],i);
				val[i][x]=((VAL>>i)&1);
				if (val[i][x]) add(x,val[i][x],i);
			}
		}else{
			int l,r;
			int ans=0;
			scanf("%d%d",&l,&r);
//			FOR(i,0,30) printf("%d:%d ",i,query(1,l,r,1,n,sum[i]));puts("");
//			FOR(i,0,30) printf("%d:%d ",i,1<<i);puts("");
			FOR(i,0,30) ans=(ans+(F[query(l,r,i)]<<i)%M)%M;
			printf("%lld\n",ans);
		}
	}
	return 0;
}
/*
*/
