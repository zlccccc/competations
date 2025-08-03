#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=50000+7;
const double eps=0.00000001;
//const LL INF=0x3f3f3f3f;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b){
	LL ret=1;
	while (b){
		if (b&1) ret=ret*a%M;
		a=a*a%M;
		b>>=1;
	}
	return ret;
}
bitset<50007> now,ans;
bool A[maxn],B[maxn];
vector<int> fac[maxn];
int n,m,q,T;
int i,j,k;
int main()
{
	FOR(i,1,50000){
		for (j=i;j<=50000;j+=i) fac[j].push_back(i);
	}
	scanf("%d",&T);
	while (T--){
		scanf("%d%d%d",&n,&m,&q);
		now=0;
		ans=0;
		memset(A,0,sizeof(A));
		memset(B,0,sizeof(B));
		FOR(i,1,n){
			scanf("%d",&k);
			A[k]^=1;
		}
		FOR(i,1,m){
			scanf("%d",&k);
			B[k]^=1;
		}
		now[0]=(m&1);
		FOR(i,1,50000){
			now<<=1;
			for (int k:fac[i]){
				if (B[k]){
					now[k]=now[k]^1;
					now[0]=now[0]^1;
				}
			}
			if (A[i]){
				ans^=now;
			}
		}
		REP(i,q){
			int t;
			scanf("%d",&t);
			if (ans[t]==1) puts("1");
			else puts("0");
		}
	}
}
/*
*/
