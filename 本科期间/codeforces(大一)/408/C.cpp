#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


int n,m;
int i,j;
int a[maxn];
vector<int> edge[maxn];
multiset<int> Q;
int mx,ans;
int u,v;
int main()
{
	scanf("%d",&n);
	FOR(i,1,n) {scanf("%d",&a[i]);Q.insert(a[i]);}
	REP(i,n-1){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	ans=INF;
	FOR(i,1,n){
		mx=a[i];
		Q.erase(Q.find(a[i]));
		REP(j,edge[i].size()){
			mx=max(mx,a[edge[i][j]]+1);
			Q.erase(Q.find(a[edge[i][j]]));
		}
//		if (!Q.empty()) printf(" %d ",*Q.rbegin());
		if (!Q.empty()) mx=max(mx,*Q.rbegin()+2);
		REP(j,edge[i].size()) Q.insert(a[edge[i][j]]);
		Q.insert(a[i]);
		ans=min(ans,mx);
//	printf("%d",mx);
	}
	printf("%d",ans);
}
