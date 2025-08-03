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
int n,m;
int i,j;
int l,r,k,o;
int u,v;
char a[1000000];
char b[1000000];
int main(){
	int t=1;
	int MX=20;
	int n=30,m=20,q=10;
	srand(time(0));
	// printf("%d\n",t);
	while (t--){
		printf("%d\n",n);
		FOR(i,1,n) printf("%d ",rand()%MX-MX/2);puts("");
		FOR(i,1,n-1) printf("%d %d\n",rand()%i+1,i+1);
		printf("%d\n",m);
		FOR(i,1,m) {
			printf("%d\n",rand()%n+1);
		}
	}
}
/*
*/
