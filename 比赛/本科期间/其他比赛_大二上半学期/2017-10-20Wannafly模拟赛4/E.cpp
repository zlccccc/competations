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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
 
LL pow5[107],pre[107];
LL a[107];
void solve(LL x){
	LL pos=0,ans=0,mark=1,xx=x;x++;
	while (x) a[pos++]=x%5,x/=5;
	while(pos--){
		if (pos&1){
			if (a[pos]&1){
				ans+=pre[pos]*(a[pos]/2+mark)+(pow5[pos]-pre[pos])*(a[pos]/2+(mark^1));
				mark^=1;
			}else{
				ans+=pow5[pos]*(a[pos]/2);
			}
		}else{
			if (mark) ans+=pre[pos]*a[pos];
			else ans+=(pow5[pos]-pre[pos])*a[pos];
		}
	}
	printf("%lld\n",xx+1-ans);
}
int main(){
	LL n,i;
	pow5[0]=1;pre[0]=0;
	FOR(i,1,107) pow5[i]=pow5[i-1]*5;
	FOR(i,1,107)
		if (i&1) pre[i]=pre[i-1]*5;
		else pre[i]=(pre[i-1]+2*pow5[i-1]);
//	FOR(i,1,20) printf("%lld : %lld,%lld\n",i,pow5[i],pre[i]);
	while (~scanf("%lld",&n)&&~n) solve(n);
}
/*
16->10000
*/
