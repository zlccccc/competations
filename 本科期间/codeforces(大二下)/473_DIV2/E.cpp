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

map<int,LL> MP;
LL solve(int dep,LL n,bool mark){
    if (dep==-1) return 0;
    if (mark&&MP[dep]) return MP[dep];
    LL ret;
    if (mark) ret=(1ll<<dep)+2*solve(dep-1,0,1);
    else {
        if ((n>>dep)&1){
            ret=(1ll<<dep)+solve(dep-1,0,1);
            ret+=solve(dep-1,n^(1ll<<dep),0);
        }else ret=solve(dep-1,n,0);
    }
//    dbg(dep);dbg(n);dbg(ret);dbgln(mark);
    if (mark) MP[dep]=ret;
    return ret;
}
LL n;
int main() {
	int i,j;
	while (~scanf("%I64d",&n)){
        n--;
        printf("%I64d\n",solve(50,n,0));
	}
	return 0;
}
/*
1000000000000
*/
