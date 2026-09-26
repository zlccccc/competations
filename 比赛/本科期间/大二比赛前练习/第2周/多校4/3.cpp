#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}

LL n,T;
LL Ans,i,j;
LL l,r,k,D;
LL ans[maxn],val[maxn];
bool mark[maxn];
int main()
{
	mark[1]=0;
	FOR(i,2,1000000){
		for (j=i*2;j<=1000000;j+=i)
			mark[j]=1;
	}
	scanf("%d",&T);
	while (T--){
		scanf("%lld%lld%lld",&l,&r,&k);
		D=sqrt(r);
		Ans=0;
		FOR(i,l,r) ans[i-l]=1,val[i-l]=i;
		FOR(i,2,D){
			if (mark[i]) continue;
			for(j=(l/i+(l%i!=0))*i;j<=r;j+=i){
				LL t=0;
				while (val[j-l]%i==0) t++,val[j-l]/=i; 
				ans[j-l]=ans[j-l]*(t*k+1)%M;
			}
		}
		FOR(i,l,r){
			if (val[i-l]!=1) Ans=(Ans+(k+1)*ans[i-l])%M;
			else Ans=(Ans+ans[i-l])%M;
		}
		printf("%lld\n",Ans); 
	}
	return 0;
}
/*
*/
