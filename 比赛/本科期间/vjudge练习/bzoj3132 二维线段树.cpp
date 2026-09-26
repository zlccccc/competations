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
const LL maxn=2000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int lazyXY[maxn<<2][maxn<<2],lazyY[maxn<<2][maxn<<2],lazyX[maxn<<2][maxn<<2],val[maxn<<2][maxn<<2];
inline void updateXY(int x,int y,int yl,int yr,int val,int L,int R){
	if (yl<=L&&R<=yr){lazyXY[x][y]+=val;return;}
	else lazyX[x][y]+=val*(min(yr,R)-max(yl,L)+1);
	int mid=(L+R)/2;
	if (mid>=yl) updateXY(x,y<<1,yl,yr,val,L,mid);
	if (yr>mid) updateXY(x,y<<1|1,yl,yr,val,mid+1,R);
}
inline void updateY(int x,int y,int yl,int yr,int actval,int L,int R){
	if (yl<=L&&R<=yr){lazyY[x][y]+=actval;return;}
	else val[x][y]+=actval*(min(yr,R)-max(yl,L)+1);
	int mid=(L+R)/2;
	if (mid>=yl) updateY(x,y<<1,yl,yr,actval,L,mid);
	if (yr>mid) updateY(x,y<<1|1,yl,yr,actval,mid+1,R);
}
inline void updateX(int x,int xl,int xr,int yl,int yr,int val,int L,int R){
	if (xl<=L&&R<=xr){updateXY(x,1,yl,yr,val,1,m);return;}
	else updateY(x,1,yl,yr,val*(min(xr,R)-max(xl,L)+1),1,m);
	int mid=(L+R)/2;
	if (mid>=xl) updateX(x<<1,xl,xr,yl,yr,val,L,mid);
	if (xr>mid) updateX(x<<1|1,xl,xr,yl,yr,val,mid+1,R);
}
inline int queryY(int x,int y,int yl,int yr,int size,int L,int R){//size无法之前乘 
	int mid=(L+R)/2,ret=0;
	if (lazyXY[x][y]){
		lazyY[x][y]+=lazyXY[x][y]*size;
		if (size!=1){
			lazyXY[x<<1][y]+=lazyXY[x][y];
			lazyXY[x<<1|1][y]+=lazyXY[x][y];
		}lazyXY[x][y]=0;
	}if (lazyY[x][y]){ 
		val[x][y]+=lazyY[x][y]*(R-L+1);
		if(L!=R){
			lazyY[x][y<<1]+=lazyY[x][y];
			lazyY[x][y<<1|1]+=lazyY[x][y];
		}lazyY[x][y]=0;
	}if (lazyX[x][y]){
		val[x][y]+=lazyX[x][y]*size;
		if (size!=1){
			lazyX[x<<1][y]+=lazyX[x][y];
			lazyX[x<<1|1][y]+=lazyX[x][y];
		}lazyX[x][y]=0;
	}
	if (yl<=L&&R<=yr) return val[x][y];
	if (mid>=yl) ret+=queryY(x,y<<1,yl,yr,size,L,mid);
	if (yr>mid) ret+=queryY(x,y<<1|1,yl,yr,size,mid+1,R);
	return ret;
}
inline int queryX(int x,int xl,int xr,int yl,int yr,int L,int R){
	int t=queryY(x,1,yl,yr,R-L+1,1,m);
	if (xl<=L&&R<=xr) return t;
	int mid=(L+R)/2,ret=0;
	if (mid>=xl) ret+=queryX(x<<1,xl,xr,yl,yr,L,mid);
	if (xr>mid) ret+=queryX(x<<1|1,xl,xr,yl,yr,mid+1,R);
	return ret;
}
int main(){
	char s[5];
	scanf("%s%d%d",s,&n,&m);
	int x1,y1,x2,y2,val;
	while (~scanf("%s%d%d%d%d",s,&x1,&y1,&x2,&y2)){
		if (s[0]=='L') scanf("%d",&val);
		if (s[0]=='L') updateX(1,x1,x2,y1,y2,val,1,n);
		if (s[0]=='k') printf("%d\n",queryX(1,x1,x2,y1,y2,1,n));
	}
}
/*
*/

