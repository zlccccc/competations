#include <cstdio>
#include <iostream>
#include <queue>
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
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


LL i,j,n;
int f[maxn][2],a[maxn][2],cnt[maxn][2],s[2];//2lose,1win,0loop
struct node{
	int x,t;
};
int x,t,y;
void dfs(int x,int k){
	int i,j;
	REP(i,s[k^1]){
		int y=(x-a[i][k^1]+n)%n;
		if (f[y][k^1]!=0) continue;
		if (f[x][k]==2) {f[y][k^1]=1;dfs(y,k^1);}
		else cnt[y][k^1]++;
		if (cnt[y][k^1]==s[k^1]){f[y][k^1]=2;dfs(y,k^1);}
	}
}
int main(){
	scanf("%d",&n);
	scanf("%d",&s[0]);
	REP(i,s[0]) scanf("%d",&a[i][0]);
	scanf("%d",&s[1]);
	REP(i,s[1]) scanf("%d",&a[i][1]);
	f[0][0]=f[0][1]=2;
	dfs(0,0);
	dfs(0,1);
	REP(j,2){
		FOR(i,1,n-1){
			if (f[i][j]==1) printf("Win ");
			else if (f[i][j]==2) printf("Lose ");
			else printf("Loop ");
		}
		puts("");
	}
	return 0; 
}
/*
*/
