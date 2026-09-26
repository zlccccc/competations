#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


int nxt[maxn*30][2],num[maxn*30];
int cnt;
void ins(int x,int val){
	int i,now=0;
	rREP(i,30){
		int mark=(x>>i)&1;
		if (!nxt[now][mark]) nxt[now][mark]=++cnt;
		now=nxt[now][mark];
		num[now]+=val;
	}
}
int query(int x,int val){//<=val
	int i,now=0,ret=0;
	rREP(i,30){
		int mark=(x>>i)&1,limit=(val>>i)&1;
		if (limit&&nxt[now][mark]) ret+=num[nxt[now][mark]];
		now=nxt[now][mark^limit];
		if (now==0) return ret;
	}
	//ret+=num[now]  //not==.....
	return ret; 
}
int n,m;
int i,j,k,l;
int main(){
	scanf("%d",&n);
	REP(i,n){
		scanf("%d",&k);
		if (k==1){
			scanf("%d",&j);
			ins(j,1);
		}
		if (k==2){
			scanf("%d",&j);
			ins(j,-1);
		}
		if (k==3){
			scanf("%d%d",&j,&l);
			printf("%d\n",query(j,l));
		}
	}
}
/*
*/
