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
const LL maxn=2048+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int a[4][maxn][maxn];
inline int lowbit(int x){
	return x&-x;
}
inline void update(int a[][maxn],int _x,int _y,int val){
	for (int x=_x;x<=n;x+=lowbit(x))
		for (int y=_y;y<=m;y+=lowbit(y)) a[x][y]+=val;
}
inline void update(int x1,int y1,int x2,int y2,int val){
	update(a[0],x2+1,y2+1,val*x2*y2);
	update(a[1],x2+1,y1,val*x2);update(a[1],x2+1,y2+1,-val*x2);//y
	update(a[2],x1,y2+1,val*y2);update(a[2],x2+1,y2+1,-val*y2);//x
	update(a[3],x1,y1,val);update(a[3],x2+1,y2+1,val);
	update(a[3],x1,y2+1,-val);update(a[3],x2+1,y1,-val);

	update(a[0],x1,y1,(x1-1)*(y1-1)*val);
	update(a[1],x1,y1,-(x1-1)*val);update(a[1],x1,y2+1,(x1-1)*val);
	update(a[0],x1,y2+1,-(x1-1)*y2*val);
	update(a[2],x1,y1,-(y1-1)*val);update(a[2],x2+1,y1,(y1-1)*val);
	update(a[0],x2+1,y1,-x2*(y1-1)*val);
}
inline int query(int a[][maxn],int _x,int _y){
	int ret=0;
	for (int x=_x;x;x-=lowbit(x))
		for (int y=_y;y;y-=lowbit(y)) ret+=a[x][y];
	return ret;
}
inline int query(int x,int y){
	return query(a[0],x,y)+query(a[1],x,y)*y+query(a[2],x,y)*x+query(a[3],x,y)*x*y;
}
inline int query(int x1,int y1,int x2,int y2){
	return query(x2,y2)-query(x1-1,y2)-query(x2,y1-1)+query(x1-1,y1-1);
}
int main(){
	int q;
	int i,j;
	char s[5];
	scanf("%s%d%d",s,&n,&m);
	int x1,y1,x2,y2,val,k;
	while (~scanf("%s%d%d%d%d",s,&x1,&y1,&x2,&y2)){
		if (s[0]=='L') scanf("%d",&val);
		if (s[0]=='L') update(x1,y1,x2,y2,val);
		if (s[0]=='k') printf("%d\n",query(x1,y1,x2,y2));
	}
}
/*
*/

