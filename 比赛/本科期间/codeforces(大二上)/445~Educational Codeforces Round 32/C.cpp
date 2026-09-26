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
const LL maxn=1e5+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
char a[maxn];
int c1,c2,c3,c4;
bool Check(int x,int c){
	int i,cnt=0;
	REP(i,x) if (a[i]==c) cnt++;
	if (!cnt) return 0;
	rep(i,x,n){
		if (a[i-x]==c) cnt--;
		if (a[i]==c) cnt++;
		if (!cnt) return 0;
	}return 1;
}
bool check(int x){
	int i;
	FOR(i,'a','z') if (Check(x,i)) return 1;
	return 0;
}
int l,r,mid;
int main(){
	int i;
	scanf("%s",a);n=strlen(a);
	l=0;r=n;
	while (l+1<r){
		mid=(l+r)/2;
		if (check(mid)) r=mid;
		else l=mid;
	}
	printf("%d",r);
}
/*
abcdef
*/
