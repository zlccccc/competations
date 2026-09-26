#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <ctime>
#include <set>
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
const LL N=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

int n,m,now;
int i,j;
int l,r,k,o;
int u,v;
int a[8];
int main(){
	int t=1; 
	int MX=1000000;
	int n=1000,m=10,q=20000;
	srand(time(0));
	int all;
//	printf("%d\n",t);
	while (t--){
		printf("%d %d\n",n,m);
//		FOR(i,1,n) printf("%d ",rand()%MX);puts("");
//		FOR(i,1,n) printf("%d ",rand()*10000+rand());puts("");
		now=0;
		REP(i,q){
			int k;
			k=rand()%3;
//			k=0;
			if (k==0){
				printf("S %d:%d:%c:%d\n",now,rand()%n,rand()%m+'A',rand()%2);
				now+=rand()%5;
//				printf("C 1 %d\n",i);
			}else if (k==1){
//				printf("R %d\n",rand()%n);
				printf("T %d\n",rand()%n+1);
			}else if (k==2){
				printf("R %d\n",rand()%n);
//				printf("T %d\n",rand()%n+1);
			}
		}
		puts("Contest Ends");
	}
}
/*
*/
