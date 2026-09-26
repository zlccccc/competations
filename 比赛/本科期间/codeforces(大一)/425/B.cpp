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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

int n,T;
int i,j;
char a[30],b[maxn],c[maxn];
bool mark[255];
int len,lenn;
int main(){
	scanf("%s",a);
	len=strlen(a);
	REP(i,len) mark[a[i]]=1;
	scanf("%s",b);
	len=strlen(b);
	scanf("%d",&T);
	while (T--){
		scanf("%s",c);
		lenn=strlen(c);
		i=0;j=0;
		while (j<lenn){
			if (b[i]==c[j]) i++,j++;
			else if (b[i]=='?'&&mark[c[j]]) i++,j++;
			else if (b[i]=='*'&&!mark[c[j]]&&j<=lenn-len+i) j++;
			else if (b[i]=='*') i++;
			else break;
		}if (b[i]=='*') i++;
//		printf("%d %d\n",i,j);
		if (i==len&&j==lenn) puts("YES");
		else puts("NO");
	}
}
/*
*/
