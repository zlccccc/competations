#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define REP(I,N) for (I=0;I<N;I++)
const int inf=0x3f3f3f3f;
const int maxn=1e5+7;
typedef long long ll;

vector<string> ans;
int fa[maxn];
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
} vector<int> nodes[maxn];
int depth[maxn],D[maxn];
int A[107][107];
char str[107][107];
int n;
void print1(int dep){//node
	int i,j;
	REP(i,n*3) {
		REP(j,n*3){
			if (i%3==0){
				int x=i/3+1;
				if (fa[x]==x) str[i][j]='.';
				else str[i][j]='#';
			} else if (i%3==1){
				str[i][j]='#';
			} else str[i][j]='#';
		}
	}
	REP(i,n*3) printf("%s\n",str[i]);
}
void print2(int dep){//edge
	int i,j;
	REP(i,n*3) {
		REP(j,n*3) {
			if (j%3==0){
				str[i][j]='#';
				if (dep!=1000&&dep!=3000) str[i][j]='.';
				if (i%3==0){
					if (i==j&&dep!=3000) str[i][j]='.';
					int x=j/3+1,y=i/3+1;
					if (depth[x]==dep&&fa[y]==x) str[i][j]=y+'0';
				}
			} else if (j%3==1){
				str[i][j]='#';
				if (i%3==0){
					int x=j/3+1,y=i/3+1;
					if ((fa[y]==y&&A[x][y])||x==y) str[i][j]='.';
				}
			} else str[i][j]='#';
		}
	}
	REP(i,n*3) printf("%s\n",str[i]);
}
void print3(){
	int i,j;
	REP(i,n*3) {
		REP(j,n*3) {
			if (j%3==0){
				if (i==j) str[i][j]='.';
				else str[i][j]='#';
			} else if (j%3==1){
				str[i][j]='#';
			} else str[i][j]='#';
		}
	}
	REP(i,n*3) printf("%s\n",str[i]);
}
int main(){
	int i,j,k;
	scanf("%d",&n); FOR(i,1,n) fa[i]=i;
	FOR(i,1,n) FOR(j,1,n) scanf("%d",&A[i][j]);
	FOR(k,1,n) FOR(i,1,n) FOR(j,1,n) A[i][j]|=A[i][k]&A[k][j];
	FOR(i,1,n) A[i][i]=0;
	FOR(i,1,n) FOR(j,1,n) if (A[i][j]&&A[j][i]){
		int x=getfa(i),y=getfa(j);
		if (x==y) continue; fa[x]=y;
	} FOR(i,1,n) nodes[getfa(i)].push_back(i);
	FOR(i,1,n) FOR(j,1,n) if (A[i][j]&&fa[i]==i&&fa[j]==j) D[j]++;
	queue<int> Q;
	FOR(i,1,n) if (fa[i]==i&&D[i]==0) Q.push(i);
	while (Q.size()){
		int x=Q.front(); Q.pop();
		// printf("x=%d\n",x);
		FOR(i,1,n) if (fa[i]==i&&A[x][i]){
			D[i]--;
			if (!D[i]) depth[i]=depth[x]+1,Q.push(i);
		}
	}
	printf("%d %d %d\n",n*3,n*3,n*4);
	// FOR(i,1,n) printf("%d ",fa[i]);puts(" <- fa");
	// FOR(i,1,n) printf("%d ",depth[i]);puts(" <- depth");
	REP(i,n) {
		print1(i);//merge
		puts("");
		print3();
		puts("");
		print2(i);//edge
		puts("");
		print2(3000);//down,no_self;
		puts("");
		// print2(1000);
		// puts("");
		// puts("");
		// print2(1000);
		// puts("");
	}
}
/*
6
0 1 1 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
1 0 0 0 1 0
0 0 1 0 0 0
0 1 1 0 1 0
*/
