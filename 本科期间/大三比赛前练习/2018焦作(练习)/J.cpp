#include <bits/stdc++.h>
using namespace std;
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define rREP(I,N) for (I=N-1;I>=0;I--)
typedef long long ll;
typedef long long ll;
typedef pair<int,int> pii;
const int maxn=1e6+7;
const ll inf=0x3f3f3f3f;
const ll mod=998244353;
ll powMM(ll a,ll b){
	ll ret=1;
	for (;b;b>>=1,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
typedef unsigned long long ull;

unsigned A[1507][1507],E[1507][1507];
ull D[1507][1507],B[maxn];
int X1[maxn],X2[maxn],Y1[maxn],Y2[maxn];

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
gp_hash_table<ull,int> more;
int main(){
	mt19937 rand(time(0));
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		int n,m; int i,j;
		scanf("%d%d",&n,&m);
		more.clear();
		FOR(i,1,n) scanf("%d%d%d%d",&X1[i],&X2[i],&Y1[i],&Y2[i]);
		FOR(i,1,m) FOR(j,1,m) A[i][j]=0;//C_init
		FOR(i,1,n) {//one
			int x1,x2,y1,y2;
			x1=X1[i]; x2=X2[i]; y1=Y1[i]; y2=Y2[i];
			A[x1][y1]++; A[x2+1][y2+1]++;
			A[x1][y2+1]--; A[x2+1][y1]--;
		} //second
		FOR(i,1,m) FOR(j,1,m) A[i][j]+=A[i-1][j]+A[i][j-1]-A[i-1][j-1];
		FOR(i,1,m) FOR(j,1,m) D[i][j]=0;//count_init
		FOR(i,1,n) {//one
			B[i]=((ll)rand()<<32)|rand(); int x1,x2,y1,y2;
			x1=X1[i]; x2=X2[i]; y1=Y1[i]; y2=Y2[i];
			D[x1][y1]+=B[i]; D[x2+1][y2+1]+=B[i];
			D[x1][y2+1]-=B[i]; D[x2+1][y1]-=B[i];
		} FOR(i,1,m) FOR(j,1,m) {
			D[i][j]+=D[i-1][j]+D[i][j-1]-D[i-1][j-1];
			if (A[i][j]<=2) more[D[i][j]]++;
		}
		FOR(i,1,m) FOR(j,1,m) E[i][j]=0;//count_init
		FOR(i,1,n) {//count
			int tmp=more[B[i]]; more.erase(B[i]);
			B[i]=tmp; int x1,x2,y1,y2;
			x1=X1[i]; x2=X2[i]; y1=Y1[i]; y2=Y2[i];
			E[x1][y1]+=B[i]; E[x2+1][y2+1]+=B[i];
			E[x1][y2+1]-=B[i]; E[x2+1][y1]-=B[i];
		} FOR(i,1,m) FOR(j,1,m) E[i][j]+=E[i-1][j]+E[i][j-1]-E[i-1][j-1];		
		unsigned ans=0,all=0;
		FOR(i,1,m) FOR(j,1,m){	
			if (A[i][j]) all++;
			if (A[i][j]==2) ans=max(ans,more[D[i][j]]+E[i][j]);
		}
		// FOR(i,1,m) {
		// 	FOR(j,1,m) printf("%d ",A[i][j]);puts("");
		// } puts("<- A");
		// FOR(i,1,m) {
		// 	FOR(j,1,m) printf("%d ",D[i][j]);puts("");
		// } puts("<- D");
		// FOR(i,1,m) {
		// 	FOR(j,1,m) printf("%d ",E[i][j]);puts("");
		// } puts("<- E");
		// printf("%d\n",ans);

		sort(B+1,B+1+n);
		// FOR(i,1,n) printf("%d ",B[i]);
		ans=max(ans,(unsigned)(B[n]+B[n-1]));
		printf("%d\n",all-ans);
	}
}
/*
*/