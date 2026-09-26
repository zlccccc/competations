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
int f[maxn][2],a[maxn][2],cnt[maxn][2],s[2];//0lose,1win,2loop
struct node{
	int x,t;
	node(int xx=0,int tt=0):x(xx),t(tt){};
};
queue<node> Q;
int x,t,y;
int main(){
	scanf("%d",&n);
	scanf("%d",&s[0]);
	REP(i,s[0]) scanf("%d",&a[i][0]);
	scanf("%d",&s[1]);
	REP(i,s[1]) scanf("%d",&a[i][1]);
	Q.push(node(0,0));
	Q.push(node(0,1));
	REP(i,n) f[i][0]=f[i][1]=2; 
	f[0][0]=f[0][1]=0;
	while (!Q.empty()){
		x=Q.front().x;t=Q.front().t;Q.pop();
//		printf("%d %d   %d\n",x,t,s[t^1]);
		REP(i,s[t^1]){
			y=(x-a[i][t^1]+n)%n;
			if (f[x][t]==0&&f[y][t^1]==2) {
				Q.push(node(y,t^1));f[y][t^1]=1;
//				printf("  %d %d=>1  ",y,t^1);
			}//if have failed
			if (f[x][t]==1&&f[y][t^1]==2){
				cnt[y][t^1]++;
				if (cnt[y][t^1]==s[t^1]) {Q.push(node(y,t^1));f[y][t^1]=0;}
//				printf("  %d %d++",y,t^1);
			}
		}
//		puts("");
	}
//	puts(""); 
//	REP(i,n) printf("%d",f[i][0]);
//	puts("");
//	REP(i,n) printf("%d",f[i][1]);
//	puts("");
	REP(j,2){
		FOR(i,1,n-1){
			if (f[i][j]==1) printf("Win ");
			else if (f[i][j]==0) printf("Lose ");
			else printf("Loop ");
		}
		puts("");
	}
	return 0; 
}
/*
*/
