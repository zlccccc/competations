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
const LL maxn=4e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

struct node{
	int l,r;
	LL cost;
}a[maxn];
bool cmp(node a,node b){
	if (a.l==b.l) return a.r<b.r;
	else return a.l<b.l;
}
int n,m;
int i,j,k;
LL val[maxn];
vector<pair<int,LL> > T[maxn];
int main(){
	scanf("%d%d",&n,&m);
	REP(i,n) scanf("%d%d%I64d",&a[i].l,&a[i].r,&a[i].cost);
	sort(a,a+n,cmp);
	fill(val,val+m+1,INFF);
	j=0;
	LL ans=INFF;
	REP(i,n){
		while (j<a[i].l){
			REP(k,T[j].size())
				val[T[j][k].first]=min(val[T[j][k].first],T[j][k].second);
			j++; 
		}
//		printf("---%d %d\n",a[i].r-a[i].l+1,a[i].cost);
		if (m-(a[i].r-a[i].l+1)>0) ans=min(ans,val[m-(a[i].r-a[i].l+1)]+a[i].cost);
		T[a[i].r].push_back(make_pair(a[i].r-a[i].l+1,a[i].cost));
	}
//	FOR(i,0,7) printf("%d ",val[i]);
	if (ans==INFF) puts("-1");
	else printf("%I64d",ans);
}
/*
4 4
1 3 4
1 2 5
5 6 1
1 6 4
*/
