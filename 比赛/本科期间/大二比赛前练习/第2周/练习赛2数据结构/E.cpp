#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}

int fa[maxn];
int sum[maxn],num[maxn];
int id[maxn];
inline int getfather(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfather(fa[x]);
}
int n,m;
int i,j,k,tot;
int p,q;
int main()
{
	while (~scanf("%d%d",&n,&m)){
		FOR(i,1,n) fa[i]=sum[i]=id[i]=i,num[i]=1;
		tot=n+1;
		REP(i,m){
			scanf("%d",&k);
			if (k==1){
				scanf("%d%d",&p,&q);
				int x=getfather(id[p]),y=getfather(id[q]);
				if (x==y) continue;
				fa[x]=y,sum[y]+=sum[x];num[y]+=num[x];
			}else if (k==2){
				scanf("%d%d",&p,&q);
				int x=getfather(id[p]),y=getfather(id[q]);
				if (x==y) continue;
				sum[x]-=p;num[x]--;
				sum[y]+=p;num[y]++;
				id[p]=tot++;fa[id[p]]=y;
			}else{
				scanf("%d",&p);
				int x=getfather(id[p]);
				printf("%d %d\n",num[x],sum[x]);
			}
		}
	}
	return 0;
}
/*
*/
