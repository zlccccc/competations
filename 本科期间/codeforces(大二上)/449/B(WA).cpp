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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}


int n,m,c;
int T;
int a[maxn],_x;
int solve(int x){
//	printf("solve:%d\n",x);
	while (a[x]&&a[x+1]&&x+1<=n&&a[x]<=_x) x++;
	int cnt1=0,cnt2=0,i;
	FOR(i,1,x) if (!a[i]) cnt1++;
	FOR(i,x+1,n) if (!a[i]) cnt2++;
	if (cnt1<cnt2){
		while (x+1<=n&&a[x]&&a[x]<=_x) x++;
	}else if (cnt1>cnt2){
		while (x-1>=1&&a[x]&&a[x]>=_x) x--;
	}
//	printf("cnt:%d %d %d\n",x,cnt1,cnt2);
	if (!cnt1&&!cnt2) return 0;
	a[x]=_x;
//	printf("pos:%d - %d\n",x,_x);
	return x;
}
int main(){
	int i,j;
	scanf("%d%d%d",&n,&m,&c);
	FOR(i,1,m){
		cin>>_x;
		cout<<solve(_x*n/c+(_x*n%c!=0))<<"\n";
		fflush(stdout);
		bool mark=0;
		FOR(j,1,n) if (!a[j]) mark=1;
		if (!mark) break;
	}
}
/*
10 2 10
*/
