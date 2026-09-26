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

char a[maxn];
int main(){
	int n,i,j,t;
	scanf("%d",&t);
	scanf("%s",a);
	int len=strlen(a);
	if (t==1){
		char now=0;
		int cnt=0;
		REP(i,len){
			if (now!=a[i]){
				if (cnt) printf("%d",cnt+1);
				now=a[i];cnt=0;
				printf("%c",a[i]);
			}else cnt++;
		}if (cnt) printf("%d",cnt+1);
	}else{
		i=0;char now=0;
		int cnt=0;
		while(i<len){
			cnt=0;now=a[i];
			printf("%c",a[i]);i++;
			while (i<len&&'0'<=a[i]&&a[i]<='9'){
				cnt=cnt*10+a[i]-'0';
				i++;
			}if (cnt) cnt--;
			while (cnt--) printf("%c",now);
		}
	}
}
/*
*/
