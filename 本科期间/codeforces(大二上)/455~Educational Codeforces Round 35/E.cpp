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

int n,i,j,k;
bool ans;
set<int> Q;
int a[maxn];
int s[maxn],top;
bool mark[maxn];
int now=0;
int main(){
	scanf("%d%d",&n,&k);
	FOR(i,1,k) scanf("%d",&a[i]);
	now=1;Q.insert(n+1);
	FOR(i,1,k){
		if (a[i]>now&&*(Q.begin())<a[i]) return 0*puts("-1");
		mark[a[i]]=1;Q.insert(a[i]);
		while (mark[now]) Q.erase(now),now++;
	}
	FOR(i,1,k) printf("%d ",a[i]);
	FOR(i,k+1,n){
		int t=*(Q.begin())-1;
		printf("%d ",t);
		mark[t]=1;Q.insert(t);
		while (mark[now]) Q.erase(now),now++;
	}
}
/*
7 2
6 4
*/
