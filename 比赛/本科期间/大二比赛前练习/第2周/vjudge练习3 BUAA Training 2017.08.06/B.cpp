#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const double eps=0.00000001;
const double pi=acos(-1.0);
struct point{
	double x,y;
	point(){}
	point(double _x,double _y):x(_x),y(_y){};
	double len(){
		return x*x+y*y;
	}
	point operator+(const point b){
		return point(x+b.x,y+b.y);
	}
	point operator-(const point b){
		return point(x-b.x,y-b.y);
	}
	point trans(double theta){
		double tx=x,ty=y;
		x=tx*cos(theta)-ty*sin(theta);
		y=tx*sin(theta)+ty*cos(theta);
		return *this;
	}
}now,a,b,noww;
int n;
int i;
double len,theta,alltheta;
int main()
{
	int x=0,T;
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		now=point(0,0);
		alltheta=0;
		REP(i,n){
			scanf("%lf%lf%lf",&a.x,&a.y,&theta);
			alltheta+=theta;
			while (alltheta>=2*pi) alltheta-=2*pi;
			while (alltheta<0) alltheta+=2*pi;
			if ((a-now).len()<=eps) continue;
			now=a+(now-a).trans(theta);
            printf("now = %lf %lf\n",now.x,now.y);
            b=point((now.x*(1-cos(alltheta))-now.y*sin(alltheta))/(2-2*cos(alltheta)),
					(now.y*(1-cos(alltheta))+now.x*sin(alltheta))/(2-2*cos(alltheta)));
				printf("%.10lf %.10lf %.10lf\n",b.x
								  			   ,b.y
								      		    ,alltheta);
			noww=b+(point(0,0)-b).trans(alltheta);
					printf("   ----->  %lf %lf\n",noww.x,noww.y);
		}
        b=point((now.x*(1-cos(alltheta))-now.y*sin(alltheta))/(2-2*cos(alltheta)),
				(now.y*(1-cos(alltheta))+now.x*sin(alltheta))/(2-2*cos(alltheta)));
		printf("%.15lf %.15lf %.15lf\n",b.x
						  			   ,b.y
						      		   ,alltheta);
//		noww=b+(-b).trans(alltheta);
//			printf("   ----->  %lf %lf\n",noww.x,noww.y);
	}
    return 0;
}
/*
1
3
0 0 1
1 1 1
2 2 1
1
2
0.381773 -1.301169 2


1
3
1 1 1
2 2 1
0 0 1
*/

