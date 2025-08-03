#include <iostream>
#include <bits/stdc++.h>
#include <utility>
using namespace std;
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
const int inf=0x3f3f3f3f;
const int maxn=1e5+7;
typedef long long ll;

struct node {
	int prea,preb,prex,prey,okay;
} okay[307][307][10][10];
int main() {
	okay[0][0][0][0]=node{0,0,0,0,1};
	int i,j,x,y;
	REP(i,201) REP(j,201) REP(x,3) REP(y,3) if (okay[i][j][x][y].okay){
		int mat,base;
		if (x==2&&y==2) base=13; else base=23;
		FOR(mat,0,base) {
			okay[i+base+2][j+mat][x+1][y]=node{i,j,x,y,1};
			okay[i+mat][j+base+2][x][y+1]=node{i,j,x,y,1};
		} 
		FOR(mat,base,200-min(i,j)) {
			okay[i+mat+2][j+mat][x+1][y]=node{i,j,x,y,1};
			okay[i+mat][j+mat+2][x][y+1]=node{i,j,x,y,1};
		}
	}
	int T,_; scanf("%d",&T);
	FOR(_,1,T) {
		int a,b,i,j; scanf("%d%d",&a,&b);
		rREP(i,4) {
			REP(j,4) if (max(i,j)==3){
			// printf("CHK:%d %d  %d %d  %d\n",a,b,i,j,okay[a][b][i][j].okay);
				if (okay[a][b][i][j].okay) break;
			} if (okay[a][b][i][j].okay) break;
		} if (i==-1) puts("Impossible");
		else {
			vector<string> ans;
			printf("%d:%d\n",i,j);
			while (a||b||i||j) {
				int nxta=okay[a][b][i][j].prea,nxtb=okay[a][b][i][j].preb;
				int nxti=okay[a][b][i][j].prex,nxtj=okay[a][b][i][j].prey;
				ans.push_back(to_string(a-nxta)+":"+to_string(b-nxtb));
				a=nxta; b=nxtb; i=nxti; j=nxtj;
			} reverse(ans.begin(), ans.end());
			for (string now:ans) cout<<now<<" ";
			puts("");
		}
	}
}
/*
100
80 28
82 76
65 109
65 50
75 119
75 94

*/
