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
const LL M=10007;
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
	int a[2][2];
	node(int a00=1,int a01=0,int a10=0,int a11=1){
		a[0][0]=a00;
		a[0][1]=a01;
		a[1][0]=a10;
		a[1][1]=a11;
	}
};
node mul(node a,node b){
	node ret;
	int i,j;
	REP(i,2) REP(j,2) ret.a[i][j]=(a.a[i][0]*b.a[0][j]+a.a[i][1]*b.a[1][j])%M;
	return ret;
}
inline node poww(node a,int b){
	node ret;
	for (;b;b>>=1ll,a=mul(a,a)){
		if (b&1) ret=mul(ret,a);
	}
	return ret;
}

int n,m,i,j,k;
LL a[maxn],b[maxn],c[maxn];
int cnt;
double ans;
int main(){
	while (~scanf("%d",&n)){
		node x=node(1,1,1,0);
		printf("%d\n",poww(x,n).a[0][1]);
	}
}
/*
1 1
13465128645621
561328465789987
*/
