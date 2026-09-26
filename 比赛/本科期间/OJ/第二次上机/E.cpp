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
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j;
struct person{
	int power,pre,suf;
	bool dead;int id;
	double v,pos;
	const bool operator < (const person &A) const{
		return pos>A.pos;
	}
}a[maxn];
struct node{
	double time;
	int x,y;
	node(double _t,int _x,int _y):time(_t),x(_x),y(_y){}
	const bool operator < (const node &A) const{
		return time>A.time;
	}
};
priority_queue<node> Q;
double L;
double changeT(double x,double T,double t){
	while (x<=T) x+=t;
	while (x>=T+t) x-=t;
	return x;
}
void add(int i,int j,double nowtime){
	if (a[i].v-a[j].v>0)
		Q.push(node(changeT((a[j].pos-a[i].pos)/(a[i].v-a[j].v),nowtime,L/(a[i].v-a[j].v)),i,j));
	if (a[j].v-a[i].v>0)
		Q.push(node(changeT((a[i].pos-a[j].pos)/(a[j].v-a[i].v),nowtime,L/(a[j].v-a[i].v)),i,j));
}
void del(int i,double nowtime){
	a[i].dead=1;
	a[a[i].pre].suf=a[i].suf;
	a[a[i].suf].pre=a[i].pre;
	add(a[i].pre,a[i].suf,nowtime);
}
double ans;
int main(){
	int T;
	scanf("%d",&T); 
	while (T--){
		scanf("%d%lf",&n,&L);
		REP(i,n) scanf("%lf%lf%d",&a[i].pos,&a[i].v,&a[i].power);
		REP(i,n) a[i].id=i+1;
		sort(a,a+n);
		REP(i,n) a[i].dead=0,a[i].pre=(i-1+n)%n,a[i].suf=(i+1)%n,add(i,a[i].suf,0);
		while (Q.size()){
			node now=Q.top();Q.pop();
//			printf("%d %d %lf\n",a[now.x].id,a[now.y].id,now.time);
			if (a[now.x].dead||a[now.y].dead) continue;
			ans=now.time;
			if (a[now.x].power>a[now.y].power) del(now.y,now.time); else del(now.x,now.time);
		}
		printf("%.3lf\n",ans);
	}
}
/*
*/
