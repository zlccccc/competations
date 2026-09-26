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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

int n,m;
int A[maxn],B[maxn];
vector<int> pos[maxn];
multiset<int> S;
multiset<int>::iterator it;
int ans,all;
int main() {
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&A[i]),pos[A[i]].push_back(i);
	FOR(i,1,m) scanf("%d",&B[i]),all+=B[i];
	FOR(i,1,m){
		if (B[i]>(int)pos[i].size()) return 0*puts("-1");
		else B[i]--;
		if (B[i]!=-1) S.insert(pos[i][B[i]]);
	}//puts("OK1");
	ans=INF;
	if (S.empty()) return 0*puts("0");
	FOR(i,1,n){
		int k=A[i];
		if (B[A[i]]==-1) continue;
		it=S.end();it--;
		// printf("%d : %d\n",i,*it);
		ans=min(ans,*it-i-all+1);
		it=S.find(pos[k][B[k]]);
		S.erase(it);
		// printf("erase: %d\n",pos[A[i]][B[A[i]]]);
		B[k]++;
		if (B[k]==(int)pos[k].size()) break;
		S.insert(pos[k][B[k]]);
		// printf("insert: %d\n",pos[A[i]][B[A[i]]]);
	}
	printf("%d\n",ans);
	return 0;
}
/*
8 3
3 3 1 2 2 1 1 3
0 0 1
*/
