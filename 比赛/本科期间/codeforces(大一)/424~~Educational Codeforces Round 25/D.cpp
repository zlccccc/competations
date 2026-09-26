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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

LL n,m;
LL i,j,k;
LL l,r,mid;
char a[maxn];
char b[maxn];
LL num[255];
LL one[255];
bool check(LL x){
	LL i,cnt=0;
	FOR(i,'a','z') cnt+=max(0ll,x*one[i]-num[i]);
	return cnt<=num['?'];
}
int main(){
	scanf("%s",a);
	scanf("%s",b);
	n=strlen(a);
	m=strlen(b);
	REP(i,n) num[a[i]]++;
	REP(i,m) one[b[i]]++;
	l=0;r=1e6+7;
	while (l+1<r){
		mid=(l+r)/2;
		if (check(mid)) l=mid;
		else r=mid;
	}
	char now='a';
	REP(i,n) if (a[i]=='?'){
		while (now<'z'&&num[now]>=one[now]*l) now++;
		a[i]=now;
		num[now]++;
	}
	printf("%s",a);
}
/*
*/
