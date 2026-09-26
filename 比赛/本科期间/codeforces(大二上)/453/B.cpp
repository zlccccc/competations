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

int n;
int now[maxn],pre[maxn],tmp[maxn];
int i,j,k;
int main(){
	scanf("%d",&n);
	pre[0]=1;
	now[0]=0;now[1]=1;
	FOR(k,2,n){
		bool mark=1;
		FOR(i,0,n) tmp[i]=now[i];
		FOR(i,1,n)
			if (abs(now[i-1]+pre[i])>1) mark=0;
		rFOR(i,1,n){
			if (mark) now[i]=now[i-1]+pre[i];
			else now[i]=-now[i-1]+pre[i];
		}now[0]=pre[0];
		FOR(i,0,n) pre[i]=tmp[i];
	}
	if (now[n]<0)
		FOR(i,0,n) now[i]=-now[i];
	if (pre[n-1]<0)
		FOR(i,0,n) pre[i]=-pre[i];
	printf("%d\n",n);
	FOR(i,0,n) printf("%d ",now[i]);puts("");
	printf("%d\n",n-1);
	FOR(i,0,n-1) printf("%d ",pre[i]);puts("");
}
/*
*/
