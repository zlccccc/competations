#include <bits/stdc++.h>
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
using namespace std;
typedef pair<long long,long long> pii;
const int MAX=1e5+5;
#define pb push_back
#define mp make_pair
typedef long long ll;
void max_(int &A,int B){(A<B)&&(A=B);}
int n,m,k;
int R[2007]; int B[2007][2007];
int main() {
	int _t,T; scanf("%d",&T);
	FOR(_t,1,T) {
		int i,j;
		scanf("%d%d%d",&m,&n,&k);
		int ans=0;
		FOR(i,1,m) FOR(j,0,k) B[i][j]=0;
		FOR(i,1,m) R[i]=i-1;
		FOR(i,1,n) {
			int l,r;
			scanf("%d%d",&l,&r);
			max_(R[l],r);
		} FOR(i,2,m) max_(R[i],R[i-1]);
		FOR(i,1,m){
			FOR(j,0,k){
				max_(B[i+1][j],B[i][j]);
				max_(B[R[i]][j+1],B[i-1][j]+R[i]-i+1);
				max_(ans,B[i][j]);
			}
			// printf("%d : ",i);
			// FOR(j,0,k) printf("%d ",B[i][j]);puts("");
		}
		printf("Case #%d: %d\n",_t,ans);
	}
}
/*
2
5 3 2
3 4
1 1
1 3
100 2 1
1 50
90 100
*/
