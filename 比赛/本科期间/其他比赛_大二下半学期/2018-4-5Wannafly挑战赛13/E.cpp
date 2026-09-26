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
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

int n,m,k;
int L[maxn],R[maxn];
vector<int> V;
vector<int> have[maxn];
inline int getid(int val){
	return lower_bound(V.begin(), V.end(),val)-V.begin();
}
priority_queue<pair<int,int> > Q,Q_Q;
int ans;
int main() {
	int i;
	scanf("%d",&n);
	FOR(i,1,n){
		assert(scanf("%d%d",&L[i],&R[i])==2);
		assert(L[i]<=R[i]);
		V.push_back(L[i]);
		V.push_back(R[i]);
	}sort(V.begin(), V.end());
	V.erase(unique(V.begin(), V.end()),V.end());
	FOR(i,1,n){
		have[getid(L[i])].push_back(R[i]);
		// erase[getid(R[i])].push_back(L[i]);
	}
	REP(i,V.size()){
		sort(have[i].begin(), have[i].end());
		int L=V[i];
		for (int R:have[i]){
			Q.push(make_pair(-L-R,R));
			Q_Q.push(make_pair(-L+R,R));
		}
		for (int R:have[i]){
			while (Q.size()&&Q.top().second<L) Q.pop();
			if (Q.size()) ans=max(ans,L+R+Q.top().first);
			while (Q_Q.size()&&Q_Q.top().second<L) Q_Q.pop();
			if (Q_Q.size()) ans=max(ans,L-R+Q_Q.top().first);
		}
	}
	printf("%d\n",ans);
	return 0;
}
/*
3
1 100
2 99
*/
