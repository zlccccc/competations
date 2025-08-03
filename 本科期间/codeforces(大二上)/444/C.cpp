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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int a[24],b[24];
int c[8]={1,3,5,7,9,11,24,22};
int d[8]={5,6,17,18,21,22,13,14};
int e[8]={3,4,17,19,10,9,16,14};
bool check(){
	int i;
//	REP(i,24) printf("%d ",b[i]);puts("");
	REP(i,6) if ((b[i*4]!=b[i*4+1])||
				 (b[i*4]!=b[i*4+2])||
				 (b[i*4]!=b[i*4+3])) return 0;
	return 1;
}
int n;
int main(){
	int i,j,k;
	REP(i,24) scanf("%d",&a[i]);
	REP(i,8) c[i]--,d[i]--,e[i]--;
	REP(i,24) b[i]=a[i];
	REP(i,8) b[c[i]]=a[c[(i-2+8)%8]];
	if (check()) return 0*puts("YES");
	REP(i,24) b[i]=a[i];
	REP(i,8) b[c[i]]=a[c[(i+2+8)%8]];
	if (check()) return 0*puts("YES");
	REP(i,24) b[i]=a[i];
	REP(i,8) b[d[i]]=a[d[(i-2+8)%8]];
	if (check()) return 0*puts("YES");
	REP(i,24) b[i]=a[i];
	REP(i,8) b[d[i]]=a[d[(i+2+8)%8]];
	if (check()) return 0*puts("YES");
	REP(i,24) b[i]=a[i];
	REP(i,8) b[e[i]]=a[e[(i-2+8)%8]];
	if (check()) return 0*puts("YES");
	REP(i,24) b[i]=a[i];
	REP(i,8) b[e[i]]=a[e[(i+2+8)%8]];
	if (check()) return 0*puts("YES");
	puts("NO");
}
/*
*/
