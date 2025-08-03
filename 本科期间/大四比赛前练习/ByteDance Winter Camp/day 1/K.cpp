#include<bits/stdc++.h>
#define FOR(I,S,N) for (I=S;I<=N;I++)
using namespace std;

int n;
typedef long long ll;
const ll INF=0x3f3f3f3f3f3f3f3fll;
typedef pair<int,int> pii;
typedef pair<double,pair<pii,pii> > P;
typedef pair<double,int> pdi;
ll A[307][307];
const double eps=1e-9;
inline P query(double p) {
	int i,j,k;//div
	P ans=P{-INF,{{0,0},{0,0}}};
	FOR(i,1,n) FOR(j,i,n){
		double base=-2*(j-i+1)*p;
		pdi MIN=make_pair(INF,0);
		FOR(k,0,n) {
			double now=A[j][k]-A[i-1][k]-p*2*k;
			ans=max(ans,P{now+base-MIN.first,{{i,MIN.second},{j,k}}});
			// printf("updown=%d-%d;k=%d now=%f\n",i,j,k,now+base-MIN.first);
			MIN=min(MIN,pdi{now,k+1});
		}
	}
	// printf("P=%f; ans=%f\n",p,ans.first);
	int x1=ans.second.first.first;
	int y1=ans.second.first.second;
	int x2=ans.second.second.first;
	int y2=ans.second.second.second;
	ans.first=(double)(A[x2][y2]-A[x2][y1-1]-A[x1-1][y2]+A[x1-1][y1-1])/(2*(y2-y1+1+x2-x1+1));
	// printf("%d - %d : %d - %d : %f\n",x1,y1,x2,y2,ans.first);
	return ans;
}
int main() {
	int _=0;
	while (scanf("%d",&n)&&n) {
		int i,j;
		FOR(i,1,n) FOR(j,1,n) scanf("%lld",&A[i][j]);
		FOR(i,1,n) FOR(j,1,n) A[i][j]+=A[i-1][j]+A[i][j-1]-A[i-1][j-1];
		double ans=0;
		while (1){
			double nxt=query(ans).first;
			if (abs(nxt-ans)<eps) break;
			else ans=nxt; 
		} P x=query(ans);
		printf("Case #%d: The maximal value is %.10f, rectangle corners are (%d, %d) and (%d, %d).\n",++_,
				x.first,x.second.first.second,x.second.first.first,x.second.second.second,x.second.second.first);
	}
	return 0;
}
/*
2
100 100
1 1
2
-100 -100
-1 -1
0
*/