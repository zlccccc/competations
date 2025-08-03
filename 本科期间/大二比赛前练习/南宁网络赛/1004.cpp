#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const LL eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a) {return a>0?a:-a;}

LL n,m;
int MID=20,MAX=40; 
inline double len(double x,double y,double x1,double y1){
	return (x1-x)*(x1-x)+(y1-y)*(y1-y);
}
int main(){
	int x,y,i,j,k,ansx,ansy;
	double maxlen;
	FOR(k,1,10){
		scanf("%d%d",&x,&y);
//		printf("%lf",len(0,15,0,15));
		maxlen=100000000;
		ansx=ansy=0;
		FOR(i,-10,10){
			FOR(j,-10,10){
//				printf("%d-%d:%lf,%lf,len=%d\n",i,j,(5.0*i+5.0*j/2)*sqrt(3),7.5*j);
				if (len((5.0*i+5.0*j/2)*sqrt(3),7.5*j,x,y)<maxlen){
					ansx=i;ansy=j;maxlen=len((5.0*i+5.0*j/2)*sqrt(3),7.5*j,x,y);
				}
			}
		}
		printf("[%d,%d]",ansx,ansy);
		if (k!=10) printf(", ");
	}
}
/*
*/
