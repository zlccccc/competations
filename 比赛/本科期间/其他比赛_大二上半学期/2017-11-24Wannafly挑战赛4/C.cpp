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
const LL M=998244353;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k,t;
int val;
char a[157][157];
int cnt;int _x,_y;
inline void go(int x,int y){
//	printf("%d-%d --> %d %d;ans+=%d\n",_x,_y,x,y,abs(x-_x)+abs(y-_y));
	cnt+=abs(x-_x)+abs(y-_y);
	_x=x;_y=y;
}int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%s",a[i]+1);
	_x=1,_y=1;
	FOR(i,1,n){
		int pre=1,suf=m;
		while (a[i][pre]=='G'&&pre<=m) pre++;
		while (a[i][suf]=='G'&&suf>=1) suf--;
//		printf("%d:%d %d\n",i,pre,suf);
		if (pre>m) continue;
		if (i&1){
			if (pre<_y) go(i-1,pre);
			go(i,suf);
		}else{
			if (suf>_y) go(i-1,suf);
			go(i,pre);
		}
	}
	printf("%d\n",cnt);
}
/*
*/
