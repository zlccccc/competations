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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n;
struct node{
	int M,S;
}T[maxn];
bool cmp(node a,node b){
	if (a.M==b.M) return a.S>b.S;
	return a.M>b.M;
}
int ans,MAX;
int main(){
	int i;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d%d",&T[i].M,&T[i].S);T[i+1].M=T[i+1].S=INF;
	sort(T+1,T+1+n,cmp);
	MAX=-INF;
	FOR(i,1,n){
		if (T[i].S==T[i+1].S&&T[i].M==T[i+1].M) ans++;
		else if (T[i].S<=MAX) ans++;
		MAX=max(MAX,T[i].S);
	}
	printf("%d\n",ans);
}
/*
*/
