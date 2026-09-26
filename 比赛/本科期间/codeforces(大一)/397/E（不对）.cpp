#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e6;
const LL N=1e6;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

int n,m;
int i,j,k;
int u,v;
bool mark2=1; 
vector<int> edge[N];
int ans;
int dfs(int from,int u,int l){
	int leng=0;
	int i,j,k;
	int ll;
	k=edge[u].size();
//	printf("\n%d   %d\n",u,ans);
//	printf("%d\n",k);
	REP(i,k) if (edge[u][i]!=from){
		ll=dfs(u,edge[u][i],l+1);
//		printf("%d %d ",i,k);
//		printf("%d->%d ll==%d  l==%d\n",u,edge[u][i],ll,l);
		if (ll==-1) return -1;
		if (ll==l||leng==ll){
			ans-=ll;
			leng=ll;
//			printf("/%d/*%d*\n",ll,edge[u][i]);
		}
		else if (leng==0) leng=ll;
		else {mark2=0; return -1;}
	}
//	printf("leng=%d,l=%d\n",leng,l);
	if (leng==l) ans+=l;
//	printf("%d   %d\n",u,ans);
	if (k==1) return 1;
	if (leng==0) return l+1;
	return leng+1;
}
int main()
{
	cin>>n;
	REP(i,n-1){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	u=1;
	while (edge[u].size()>1) u++;
	ans=n-1;
	dfs(0,u,0);
	while (ans%2==0) ans>>=1;
	if (mark2==0) printf("-1");
	else printf("%d",ans);
	return 0;
}
/*
6
1 2
2 3
2 4
4 5
1 6
7
1 2
1 3
3 4
1 5
5 6
6 7
9
1 2
1 3
1 4
1 5
1 6
6 7
6 8
8 9
*/
