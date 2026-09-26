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
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

struct L_B{
	int A[20];int have_0;
	void clear(){memset(A,0,sizeof(A));have_0=0;}
	int XORMIN(int x){
		int i;
		rREP(i,20) if ((A[i]^x)<x) x^=A[i];
		return x;
	}
	void insert(int x){
		int i;
		if (!XORMIN(x)) have_0++;
		rREP(i,20) if ((x>>i)&1){
			if (!A[i]) A[i]=x;x^=A[i];
		}
	}
}A[maxn];
int n,q;
int a[maxn];
int main() {
	int i,j;
	scanf("%d%d",&n,&q);
	FOR(i,1,n) scanf("%d",&a[i]);
	FOR(i,1,n) {
        A[i]=A[i-1];
        A[i].insert(a[i]);
	}FOR(i,1,q){
	    int l,x;
        scanf("%d%d",&l,&x);
        if (A[l].XORMIN(x)!=0) puts("0");
        else printf("%d\n",powMM(2,A[l].have_0));
	}
	return 0;
}
/*
1000000000000
*/
