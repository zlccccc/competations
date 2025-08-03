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
int a[maxn];
int solve(int x){
	int pos;
	if (x<=c/2){
		pos=1;
		while (a[pos]&&a[pos]<=x) pos++;
	}else {
		pos=n;
		while (a[pos]&&a[pos]>=x) pos--;
	}a[pos]=x;
	return pos;
}
int main(){
	int i,j;
	scanf("%d%d%d",&n,&m,&c);
	FOR(i,1,m){
		int x;
		cin>>x;
		cout<<solve(x)<<"\n";
		fflush(stdout);
		bool mark=0;
		FOR(j,1,n) if (!a[j]) mark=1;
		if (!mark) break;
	}
}
/*
10 2 10
*/
