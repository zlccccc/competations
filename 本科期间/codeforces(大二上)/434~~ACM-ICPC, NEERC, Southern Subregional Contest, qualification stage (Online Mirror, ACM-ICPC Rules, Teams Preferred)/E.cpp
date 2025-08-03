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
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n;
char a[maxn];
bool check(int x){
	int i=0,nxt=0,len=0;
	while (i<n){
		while (a[i]=='.') i++;
		len=0;
		while (a[i]!='P'&&i<n){
			i++;len++;
//			printf("%d %d\n",i,len);
			if (i==n||len>x) return 0;
		}
		nxt=max(x-len*2,(x-len)/2);i++;//'P'
//		printf("%d : i=%d,len=%d,nxtlen=%d\n",x,i,len,nxt);
		while (nxt&&i<n){
			if (a[i]=='P') nxt=x;
			else nxt--;
			i++;
		}
//		printf("nxt-->%d\n",i);
	}
	return 1;
}
int l,r,mid;
int main(){
	scanf("%d",&n);
	scanf("%s",a);
	n=strlen(a);
	l=0;r=n*2;
	while (l+1<r){
		mid=(l+r)/2;
		if (!check(mid)) l=mid;
		else r=mid;
//		puts("");
	}
	printf("%d",r);
}
/*
2
........P.....*

11
***P......*
*......P***
*/
