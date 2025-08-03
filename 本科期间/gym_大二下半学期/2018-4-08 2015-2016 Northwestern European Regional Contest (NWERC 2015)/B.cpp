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

struct node {
	int l,r;
} A[207],B[207];
int sum[207];
int l_r[207][207];
int dp[207],pre[207];
struct qnode {
	int l,r,xl,xr;
};
queue<qnode> Q;
void solve(int n) {
	int i;
	Q.push(qnode{1,n,0,n-1});
	while (Q.size()) {
		qnode F=Q.front(); Q.pop();
		int l=F.l,r=F.r,L=F.xl,R=F.xr;
		int m=(l+r)/2,M=L;
		int &now=dp[m];
		FOR(i,L,min(m-1,R)) {
			if (l_r[i+1][m]==-INF) continue;
			if (now<l_r[i+1][m]+pre[i])
				now=l_r[i+1][m]+pre[i],M=i;
		}
		if (l<m) Q.push(qnode{l,m-1,L,M});
		if (r>m) Q.push(qnode{m+1,r,M,R});
	}
}
bool cmp(node &A,node &B) {
	if (A.l!=B.l) return A.l<B.l;
	return A.r>B.r;
} bool cmplength(node &A,node &B) {
	return A.r-A.l>B.r-B.l;
}
int n,p;
int m,k;
int ans;
int main() {
	int i,j;
	scanf("%d%d",&n,&p);
	FOR(i,1,n) scanf("%d%d",&A[i].l,&A[i].r);
	sort(A+1,A+1+n,cmp);
	FOR(i,1,n) {
		bool mark=0;
		FOR(j,i+1,n)
			if (A[i].l<=A[j].l&&A[j].r<=A[i].r) mark=1;
		if (mark) B[++m]=A[i];
		else A[++k]=A[i];
	}n=k;
	sort(B+1,B+1+m,cmplength);
	FOR(i,1,p) sum[i]=sum[i-1]+B[i].r-B[i].l;
	FOR(i,1,n) dp[i]=-INF;
	FOR(i,1,n) {
		int l=A[i].l,r=A[i].r;
		l_r[i][i]=r-l;
		FOR(j,i+1,n) {
			l=max(l,A[j].l); r=min(r,A[j].r);
			if (r>l) l_r[i][j]=r-l;
			else l_r[i][j]=-INF;
		}
	}
	// FOR(i,1,n) printf("%d %d\n",A[i].l,A[i].r);
	// FOR(i,1,n){
	// 	FOR(j,1,n) printf("%d-%d : %5d  ",i,j,l_r[i][j]);
	// 	puts("");
	// }
	FOR(i,1,p) {
		FOR(j,0,n) pre[j]=dp[j],dp[j]=-INF;
		// FOR(j,1,n){
		// 	FOR(k,0,j-1){
		// 		dp[j]=max(dp[j],pre[k]+l_r[k+1][j]);
		// 	}
		// }
		solve(n);
		ans=max(ans,dp[n]+sum[p-i]);
		// FOR(j,0,n) printf("(%d)%-10d ",j,dp[j]);
		// puts("");
	} printf("%d\n",ans);
	return 0;
}
/*
4 2
1 3
1 5
4 6
2 7
*/
