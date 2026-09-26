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

bool mark[maxn*3];
int n;
int a[maxn],b[maxn];
bool check(int x){
	int i;
	FOR(i,1,n) if (mark[a[i]+x]) return 0;
	return 1; 
}
int solve(){
	scanf("%d",&n);
	int i,j;
	FOR(i,1,n) scanf("%d",&a[i]);
	int tot=1;
	FOR(i,1,n){
		while (!check(tot)) tot++;
		if (tot>1000000) break;
		b[i]=tot;
		FOR(j,1,n) mark[a[j]+b[i]]=1;
	}
	FOR(i,1,n)
		FOR(j,1,n) mark[a[j]+b[i]]=0;
	puts("YES");
	FOR(i,1,n) printf("%d ",b[i]);puts("");
}
int main(){
	int T; 
	scanf("%d",&T);
	while (T--) solve();
}
/*
10
16
1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32756 65536
3
1 10 100
1
1
2
2 4
*/
