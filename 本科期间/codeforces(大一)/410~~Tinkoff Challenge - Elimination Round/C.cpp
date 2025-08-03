#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)0
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.000000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,m;
int i;
double px[maxn],py[maxn],vx[maxn],vy[maxn];
double x1,x2,y1,y2;
double xx,yy;
double tl,tr;
bool judge(double v,double x,double l,double r){
	if (abs(v)<eps&&(x<l+eps||x>r-eps)) return 1;
	double t1=(l-x)/v,t2=(r-x)/v;
	tl=max(tl,min(t1,t2));
	tr=min(tr,max(t1,t2));
	return 0;
}
int main()
{
	scanf("%d",&n);
	scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
	REP(i,n) scanf("%lf%lf%lf%lf",&px[i],&py[i],&vx[i],&vy[i]);
	tl=0;tr=INF;
	REP(i,n)
		if (judge(vx[i],px[i],x1,x2)||judge(vy[i],py[i],y1,y2)) return 0*puts("-1");
	if (tl>=tr) return 0*puts("-1");
	else printf("%.20lf",tl);
}
