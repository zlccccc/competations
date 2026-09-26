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
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}


vector<int> have[maxn];
LL inv[2000007];//inverse
LL fac[2000007];//Factorial
LL ans; 
LL C(int n,int m){
	return fac[n]*inv[m]%M*inv[n-m]%M; 
}
int main(){
	int q,i,j;
	FOR(i,2,2000000) if (have[i].empty())
		for (j=i;j<=2000000;j+=i)
			have[j].push_back(i);
	fac[0]=1; 
	FOR(i,1,2000000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,2000000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,2000000) inv[i]=inv[i]*inv[i-1]%M;
	scanf("%d",&q);
	FOR(i,1,q){
		LL x,y;
		scanf("%I64d%I64d",&x,&y);
		int X=x;
		ans=1;
		for (int v:have[X]){
			int cnt=0;
			while (x%v==0) x/=v,cnt++;
			ans=ans*C(cnt+y-1,y-1)%M;
//			printf("%d %d\n",cnt+y-1,y-1);
		}ans=ans*powMM(2ll,y-1)%M;
		printf("%I64d\n",ans);
	}
}
/*
*/
