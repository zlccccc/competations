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
#define rep(I,pos,N) for (I=pos;I<N;I++)
#define rrep(I,pos,N) for (I=N-1;I>=pos;I--)
#define FOR(I,pos,N) for (I=pos;I<=N;I++)
#define rFOR(I,pos,N) for (I=N;I>=pos;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


int n,m;
int i,j,k;
int a[257][257];
int main(){
	scanf("%d%d",&n,&m);
	int x1,x2,y1,y2;
	FOR(i,1,n){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if (x1>x2){
			swap(x1,x2);
			swap(y1,y2);
		}
		if (x1==x2) FOR(j,y1,y2) a[x1][j]=i;
		else if (y1==y2) FOR(j,x1,x2) a[j][y1]=i;
		else FOR(j,x1,x2){
			if ((y2-y1)*(j-x1)%(x2-x1)==0){
//				printf(":::%d %d\n",j,(y2-y1)*(j-x1)/(x2-x1)+y1);
				a[j][(y2-y1)*(j-x1)/(x2-x1)+y1]=i;
			}
		}
	}
	scanf("%d",&m);
	REP(i,m){
		scanf("%d%d",&x1,&y1);
		printf("%d\n",a[x1][y1]);
	}
}
/*
*/
