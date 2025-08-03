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
#define rep(I,pos,N) for (I=pos;I<N;I++)
#define rrep(I,pos,N) for (I=N-1;I>=pos;I--)
#define FOR(I,pos,N) for (I=pos;I<=N;I++)
#define rFOR(I,pos,N) for (I=N;I>=pos;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=4e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

#define x x_x
#define y y_y
LL n,m,q;
vector<int> edge[maxn];
LL i,j,k,u,v,t;
double ans;
LL L2[maxn],L1[maxn],sum,D1,D2;
LL mxlen,mx;
void dfs(int x,int fa,int length){
	if (length>L2[x]) L2[x]=length;
	if (length>mxlen) mx=x,mxlen=length;
	for (int v:edge[x]) if (v!=fa) dfs(v,x,length+1);
}
int main(){
	while (~scanf("%d%d",&n,&m)){
		REP(i,n-1){
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		FOR(i,1,n) L2[i]=0;
		mxlen=0;
		dfs(1,0,0);
		dfs(mx,0,0);
		dfs(mx,0,0);
		FOR(i,1,n) edge[i].clear();
		D1=mxlen;
		FOR(i,1,n) L1[i]=L2[i];
		sort(L1+1,L1+n+1);
		REP(i,m-1){
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		FOR(i,1,m) L2[i]=0;
		mxlen=0;
		dfs(1,0,0);
		dfs(mx,0,0);
		dfs(mx,0,0);
		FOR(i,1,m) edge[i].clear();
		D2=mxlen;
		ans=0;
//		FOR(i,1,m)
//			FOR(j,1,n) ans+=max(max(D2,D1),L1[j]+L2[i]+1);

		sort(L2+1,L2+1+m);
//		FOR(i,1,n) printf("%d ",L1[i]);puts("/////L1");
		j=n;sum=0;
		FOR(i,1,m){
			while (j<n&&L1[j+1]+L2[i]+1<=max(D1,D2)) {j++;sum-=L1[j];}
			while (j>=1&&L1[j]+L2[i]+1>max(D1,D2)) {sum+=L1[j];j--;}
			ans+=sum+(L2[i]+1)*(n-j)+max(D1,D2)*j;
//		printf("ans=%d sm=%d sm1=%d  sm2=%d  %d\n",ans,sum,(L2[i]+1)*(n-j),max(D1,D2)*j,j);
		}
		ans=ans/m/n;
		printf("%.3lf\n",ans);
	}
}
/*
*/
