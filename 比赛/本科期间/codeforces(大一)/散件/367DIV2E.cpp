#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const LL M=1e9+7;
const LL maxn=1e3+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

struct node{
	int v;
	node *d,*r;
}A[maxn][maxn];
node *xx,*yy,*x,*y;
int n,m,q;
int i,j,k;
int a,b,c,d,e,f;
int main()
{
	while (~scanf("%d%d%d",&n,&m,&q)){
		FOR(i,1,n)
			FOR(j,1,m) scanf("%d",&A[i][j].v);
		REP(i,n+1)
			REP(j,m+1) {A[i][j].d=&A[i+1][j];A[i][j].r=&A[i][j+1];}
		REP(j,q){
			x=y=&A[0][0];
			scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f);
			while (--a) x=x->d;
			while (--b) x=x->r;
			while (--c) y=y->d;
			while (--d) y=y->r;
			xx=x; yy=y;
			REP(i,e){
				x=x->d;y=y->d;
				swap(x->r,y->r);
			}
			REP(i,f){
				x=x->r;y=y->r;
				swap(x->d,y->d);
			}
			REP(i,f){
				xx=xx->r;yy=yy->r;
				swap(xx->d,yy->d);
			}
			REP(i,e){
				xx=xx->d;yy=yy->d;
				swap(xx->r,yy->r);
			}
		}
		x=&A[0][0];
		REP(i,n){
			x=x->d;
			y=x;
			REP(j,m){
				y=y->r;
				printf("%d ",y->v);
			}
			puts("");
		}
	}
}
