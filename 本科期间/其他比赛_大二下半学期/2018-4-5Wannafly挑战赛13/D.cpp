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
double p;
int w[maxn];
int ans;
struct node{
	int A,B;
	node(int _A=0,int _B=1):A(_A),B(_B){};
	bool operator < (const node &x)const{
		return A*x.B<B*x.A;
	}
};
priority_queue<node> Q;
bool check(int x){
	int i;
	double minweight,maxweight;
	FOR(i,1,n) Q.push(node(w[i],1));
	while (x--){
		auto now=Q.top();Q.pop();
		now.B++;
		Q.push(now);
	}minweight=INF;maxweight=-INF;
	while (Q.size()){
		auto now=Q.top();Q.pop();
		minweight=min(minweight,(double)now.A/now.B);
		maxweight=max(maxweight,(double)now.A/now.B);
	}
	if (maxweight*p<=minweight) return 1;
	return 0;
}
int main() {
	int i;
	scanf("%lf%d",&p,&n);
	FOR(i,1,n) scanf("%d",&w[i]);
	i=0;
	while (!check(i)) i++;
	printf("%d\n",i);
	return 0;
}
/*
*/
