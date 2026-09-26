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
const LL maxn=1007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

#define double long double 
//直线与多边形相交公共长度 
int n,m,T;
int i,j,k,t;
int sgn(double x){
	if (abs(x)<eps) return 0;
	if (x<0) return -1;
	return 1;
}
struct point{
	double x,y;
	point(double _x=0,double _y=0):x(_x),y(_y){}
	point operator -(const point &b)const{return point(x-b.x,y-b.y);}
	point operator +(const point &b)const{return point(x+b.x,y+b.y);}
	double operator ^(const point &b)const{return x*b.y-y*b.x;}
	double len(){return sqrt(x*x+y*y);}
}a[maxn];
double len(point a,point b,point c,point d){
	return (a-b).len()*((c-a)^(d-c))/((b-a)^(d-c));//这里是按a为基准的。。线段的话我觉得直接>0就好吧(当然还要加上in polygon限制)
}
vector<pair<double,int> > dis;//len,sign
int mark,mark1,mark2,sign;
double solve(point s,point e){
	dis.clear();
	int i;
	REP(i,n){
		mark=sgn((e-s)^(a[i]-s))-sgn((e-s)^(a[i+1]-s));
		if (mark==0) continue;
		dis.push_back(make_pair(len(s,e,a[i],a[i+1]),mark));
	}
	sort(dis.begin(),dis.end());
	sign=0;
	double ans=0;
//	REP(i,dis.size()) printf("i:%d:i  %.15lf %d\n",i,dis[i].first,dis[i].second);
	REP(i,dis.size()){
		sign+=dis[i].second;
		if (sign) ans+=dis[i+1].first-dis[i].first;
	}
	return ans;
}
point s,e;
int main(){
	scanf("%d%d",&n,&m);
	REP(i,n) scanf("%Lf%Lf",&a[i].x,&a[i].y);
	a[n]=a[0];
	REP(i,m){
		scanf("%Lf%Lf%Lf%Lf",&s.x,&s.y,&e.x,&e.y);
		printf("%.30Lf\n",solve(s,e));
	}
}
/*
*/
