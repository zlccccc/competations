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
const LL maxn=2000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

#define MP make_pair
int n;
void change(int &x){
	while (x<1) x+=n;
	while (x>n) x-=n;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	if (n&1){//满足后两个sum->OK的 
		printf("%d\n",n*(n-1)/2);
		FOR(i,1,n){
			FOR(j,1,n/2){
				int u=i+j,v=i-j;
				change(u);change(v);
				printf("%d %d %d\n",i,u,v);
			}
		}
	}else{//前面的每个两点间边权=[3*n*(n-1)/2]/n=3*(n-1)/2 (已经n--)
		//权值all+=n*(n-1)/2,d+=n
		printf("%d\n",n*(n-1));
		n--;
		FOR(i,1,n){
			FOR(j,2,n/2){
				int u=i+j,v=i-j;
				change(u);change(v);
				printf("%d %d %d\n",i,u,v);
			}
		}
		FOR(i,1,n){
			FOR(j,1,n/2){
				int u=i+j,v=i-j;
				change(u);change(v);
				printf("%d %d %d\n",i,u,v);
			}
		}
		FOR(i,1,n){//du=3(n-1)
			int u=i+1,v=i+2;change(u);change(v);
			printf("%d %d %d\n",i,u,n+1);
			printf("%d %d %d\n",i,v,n+1);
			printf("%d %d %d\n",u,v,n+1);
		}
	}
}
/*
*/
