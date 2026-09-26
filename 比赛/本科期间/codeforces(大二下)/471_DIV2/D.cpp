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

int n,m,k;
char A[maxn],B[maxn];
int fail[maxn];
int _L,_R;
void solve(int F[]){
	int i,j;
	fail[1]=0;
	FOR(i,2,m) {
		j=fail[i-1];
		while (j&&B[j+1]!=B[i]) j=fail[j];
		if (B[j+1]==B[i]) fail[i]=j+1;
		else fail[i]=0;
	}j=0;
	FOR(i,1,n){
		while (j&&B[j+1]!=A[i]) j=fail[j];
		if (B[j+1]==A[i]) j++;
		if (!F[j]&&i-k+1>0) F[j]=i;
		if (j==m){
			_R=i;
			if (!_L) _L=i;
		}
	}rFOR(i,1,m) if (F[i]&&fail[i]){
		if (F[fail[i]]>F[i]||!F[fail[i]])
			F[fail[i]]=F[i];
	}
}
int pre[maxn],suf[maxn];
int main() {
	int i;
	scanf("%d%d%d",&n,&m,&k);
	scanf("%s%s",A+1,B+1);
	solve(pre);
	if (m<=k&&_L){
		int L,R;
		L=max(1,_L-k+1);R=n-k+1;
		if (L+k<=R){
			puts("Yes");
			printf("%d %d\n",L,R);
			return 0;
		}L=1;R=min(n-k+1,_R-m+1);
		if (L+k<=R){
			puts("Yes");
			printf("%d %d\n",L,R);
			return 0;
		}
	}
	reverse(A+1,A+1+n);
	reverse(B+1,B+1+m);
	solve(suf);
	// FOR(i,1,m) printf("%d ",pre[i]);
	// puts("");
	// FOR(i,1,m) printf("%d ",suf[i]);
	// puts("");
	FOR(i,max(1,m-k),min(m,k)) if (pre[i]&&suf[m-i]){
		int L=pre[i]-k+1,R=n-suf[m-i]+1;
		// dbg(L);dbgln(R);
		if (L+k<=R){
			puts("Yes");
			printf("%d %d\n",L,R);
			return 0;
		}
	}puts("No");
	return 0;
}
/*
5 3 2
aaaab
aaaa

8 3 4
bcbaaaax
bcb
*/
