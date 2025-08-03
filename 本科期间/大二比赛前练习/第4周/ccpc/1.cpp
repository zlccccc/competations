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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b){
    LL ret=1;
    while (b){
        if (b&1) ret=ret*a%M;
        a=a*a%M;
        b>>=1;
    }
    return ret;
}

int n,m;
int i,j,k,now;
int ans1[maxn],ans2[maxn];
int main(){
	n=100;m=0;//n为必选点 
	FOR(i,1,n/2) ans1[m]=i*2-1,ans2[m]=i*2,m++;
	k=2;
	j=1;
	FOR(i,n+1,INF){
		now=k;
		if (i==n*4) break;
		while (now--){
			if (j==n+1) j=1,now++,k++;
			ans1[m]=j++,ans2[m]=i,m++;
		}
	}
	printf("%d %d\n",n*4,m);
	REP(i,m) printf("%d %d\n",ans1[i],ans2[i]);
	printf("%d\n",n);
	FOR(i,1,n) printf("%d\n",i);
}
/*
*/

