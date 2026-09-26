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
#include <cassert>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

LL A[maxn];
int n,m;
int ans=-1;
vector<LL> V;
vector<LL> have[maxn*5];
inline int getid(LL x){
	return lower_bound(V.begin(), V.end(),x)-V.begin();
}
int main() {
	int i,j;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%I64d",&A[i]);
	FOR(i,1,n)
		REP(j,20) V.push_back(A[i]<<j);
	sort(V.begin(), V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	FOR(i,1,n)
		have[getid(A[i])].push_back(i);
	REP(i,V.size()){
		sort(have[i].begin(),have[i].end());
		REP(j,have[i].size()/2){
			A[have[i][j*2]]=0;
			A[have[i][j*2+1]]=V[i]*2;
			have[getid(V[i]*2)].push_back(have[i][j*2+1]);
		}
	}int cnt=0;
	FOR(i,1,n) if (A[i]) cnt++;
	printf("%d\n",cnt);
	FOR(i,1,n) if (A[i]) printf("%I64d ",A[i]);
	return 0;
}
/*
121
*/
