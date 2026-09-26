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

int T;
__int128 m,L,q;
char buffer[20000000],*buf=buffer;
void read(__int128 &x){
	for(x=0;*buf<48;++buf);
	while(*buf>=48)x=x*10+*buf-48,++buf;
}
__int128 deg[maxn],freq[maxn];
__int128 A[maxn];
int main() {
	int i;
	fread(buffer,1,20000000,stdin);
	read(m);read(L);
	FOR(i,1,L) read(deg[i]),read(freq[i]),A[i]=deg[i];
	read(q);
	FOR(i,1,L) deg[i]=deg[i]*deg[i]*freq[i];
	FOR(i,1,L) deg[i]+=deg[i-1];
	rFOR(i,1,L) freq[i]+=freq[i+1];
	while (q--){
		__int128 a,b;
		read(a);read(b);
		int l=0,r=L+1;
		while (l+1<r){
			int mid=(l+r)/2;
			if (a*A[mid]*A[mid]<b*m) l=mid;
			else r=mid;
		}
		__int128 ans=a*deg[l]+b*m*freq[r];
//		__int128 ans=(__int128)INFF*10;
//		FOR(i,1,L+1) ans=min(ans,a*deg[i-1]+b*m*freq[i]);
		printf("%lld\n",(LL)ans);
	}
	return 0;
}
/*
5 4
1 1
2 1
3 1
4 1
5
1 1
3 2
2000 1
1 2000
2000 2000
*/
