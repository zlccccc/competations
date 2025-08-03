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
#include <ctime>
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
const LL maxn=1e5+7;
const double eps=0.000000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//到底顺时针还是逆时针
//样例顺时针 
int sgn(double x){
	if(fabs(x)<eps) return 0;
	if(x<0) return -1;
	else return 1;
}
struct point{
	double x,y;
	point(){}
	point(double _x,double _y){
		x=_x;y=_y;
	}
	point operator -(const point &b)const{
		return point(x-b.x,y-b.y);
	}
	double operator ^(const point &b)const{
		return x*b.y-y*b.x;
	}
};
struct line{
	point s,e;
};
bool onseg(point p,line l){
	point a=l.s,b=l.e;
	return (sgn((a-p)^(b-p))==0&&
			sgn((p.x-a.x)*(p.x-b.x))<=0&&
			sgn((p.y-a.y)*(p.y-b.y))<=0);
}
bool inter(line l1,line l2){
	return
	max(l1.s.x,l1.e.x) >= min(l2.s.x,l2.e.x) &&
	max(l2.s.x,l2.e.x) >= min(l1.s.x,l1.e.x) &&
	max(l1.s.y,l1.e.y) >= min(l2.s.y,l2.e.y) &&
	max(l2.s.y,l2.e.y) >= min(l1.s.y,l1.e.y) &&
	sgn((l2.s-l1.e)^(l1.s-l1.e))*sgn((l2.e-l1.e)^(l1.s-l1.e)) <= 0 &&
	sgn((l1.s-l2.e)^(l2.s-l2.e))*sgn((l1.e-l2.e)^(l2.s-l2.e)) <= 0;
}
int inPoly(point p,point poly[],int n){
	int cnt;
	line ray,side; cnt = 0;
	ray.s = p; ray.e.y = p.y;
	ray.e.x = -100000000000.0;
	for(int i = 0;i < n;i++){
		side.s = poly[i]; side.e = poly[(i+1)%n];
		if(onseg(p,side))return 0;
		if(sgn(side.s.y - side.e.y) == 0) continue;
		if(onseg(side.s,ray)){
			if(sgn(side.s.y - side.e.y) > 0)cnt++;
		}else if(onseg(side.e,ray)){
			if(sgn(side.e.y - side.s.y) > 0) cnt++;
		}else if(inter(ray,side)) cnt++;
	}
	if(cnt % 2 == 1)return 1;
	else return -1;
}
char s[maxn];
point a;
point p[10];
int n,i,j,t;
int main(){
	scanf("%lf%lf",&a.x,&a.y);
	REP(i,8) scanf("%*s%lf%lf",&p[i].x,&p[i].y);
//	printf("%lf %lf\n",a.x,a.y);
//	REP(i,8) printf("%lf %lf\n",p[i].x,p[i].y);
//	printf("%d\n",inConvexPoly(a,p,8));
	if (inPoly(a,p,8)>=0) puts("WTF!");
	else puts("yeah!");
}
/*
0 0
wjj 2 2
HansBug 2 0
MountVoom 2 0
HugeGun 2 0
Ryan 2 0
Hefafa 2 0
wjy 2 0
prime21 0 2
*/
