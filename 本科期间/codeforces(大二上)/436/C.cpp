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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

LL a,b,f,k;
LL nowb;
int ans;
int main(){
	int i,j;
	scanf("%I64d%I64d%I64d%I64d",&a,&b,&f,&k);
	nowb=b;nowb-=(f-0);if (nowb<0) return 0*puts("-1");
	FOR(i,1,k){
		if (i%2==1){
			if (i==k){
				if (nowb<(a-f)) ans++,nowb=b;
				nowb-=(a-f);
				if (nowb<0) return 0*puts("-1");
			}else{
				if (nowb<(a-f)*2) ans++,nowb=b;
				nowb-=(a-f)*2;
				if (nowb<0) return 0*puts("-1");
			}
		}else{
			if (i==k){
				if (nowb<(f-0)) ans++,nowb=b;
				nowb-=(f-0);
				if (nowb<0) return 0*puts("-1");
			}else{
				if (nowb<(f-0)*2) ans++,nowb=b;
				nowb-=(f-0)*2;
				if (nowb<0) return 0*puts("-1");
			}
		}
	}
	printf("%d\n",ans);
}
/*
2 1 1 1
*/
