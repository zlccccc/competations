#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
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
const LL maxn=1007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

LL n,m;
LL i,j,k,xx,yy;
char a[maxn][maxn];
int b[maxn][maxn];
LL ans;
bool mark;
struct node{
	int x,y,i;
	node(int _x=0,int _y=0,int _i=0):x(_x),y(_y),i(_i){}
};
queue<node> Q;
void color(int x,int y){
	Q.push(node(x,y,0));
	while(!Q.empty()){
		int x0=Q.front().x,y0=Q.front().y,i0=Q.front().i;
		if (i0==4) break;
		if (x0==xx&&y0==yy) mark=1;
//		printf("%d %d %d  %c\n",x0,y0,i0,a[x0][y0]);
		while (++x0<=n-1&&a[x0][y0]!='*'){
			if (!(b[x0][y0]==i0+1||b[x0][y0]==0)) break;
			Q.push(node(x0,y0,i0+1));
			b[x0][y0]=i0+1;
		}
		x0=Q.front().x,y0=Q.front().y;i0=Q.front().i;
		while (--x0>=0&&a[x0][y0]!='*'){
			if (!(b[x0][y0]==i0+1||b[x0][y0]==0)) break;
			Q.push(node(x0,y0,i0+1));
			b[x0][y0]=i0+1;
		}
		x0=Q.front().x,y0=Q.front().y;i0=Q.front().i;
		while (++y0<=m-1&&a[x0][y0]!='*'){
			if (!(b[x0][y0]==i0+1||b[x0][y0]==0)) break;
			Q.push(node(x0,y0,i0+1));
			b[x0][y0]=i0+1;
		}
		x0=Q.front().x,y0=Q.front().y;i0=Q.front().i;
		while (--y0>=0&&a[x0][y0]!='*'){
			if (!(b[x0][y0]==i0+1||b[x0][y0]==0)) break;
			Q.push(node(x0,y0,i0+1));
			b[x0][y0]=i0+1;
		}
		Q.pop();
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	REP(i,n) scanf("%s",&a[i]);
	REP(i,n)
		REP(j,m)  if (a[i][j]=='T') xx=i,yy=j;
	REP(i,n)
		REP(j,m) if (a[i][j]=='S') color(i,j); 
	if (mark) puts("YES");
	else puts("NO"); 
}
