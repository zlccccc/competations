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
const LL maxn=(1<<20)+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

inline int FWT(int *A,int len,int inv){
	int i,j,k;
	int div=powMM(2ll,M-2);
	for(i=2;i<=len;i<<=1){
		for(j=0;j<len;j+=i){
			for(k=j;k<j+i/2;k++){
				if (inv==1){
					LL a=A[k],b=A[k+i/2];
					A[k]=(a+b)%M;
					A[k+i/2]=(a-b+M)%M;
				}else{
					LL a=A[k],b=A[k+i/2];
					A[k]=1ll*(a+b)*div%M;
					A[k+i/2]=1ll*(a-b+M)%M*div%M;
				}
			} 
		}
	}
}
int n,k;
int i,j;
char b[maxn];
int a[maxn],cnt[maxn];
int ans;
int main(){
	scanf("%d",&n);
	scanf("%s",b);
	REP(i,1<<n) a[i]=b[i]-'0';
	FWT(a,1<<n,1);
	REP(i,1<<n) a[i]=1ll*a[i]*a[i]%M;
	FWT(a,1<<n,-1);
	REP(i,1<<n) cnt[i]=cnt[i>>1]+(i&1);
	REP(i,1<<n) ans=(ans+a[i]*(1ll<<(n-cnt[i]))%M)%M;
	printf("%I64d\n",3ll*ans%M);
}
/*
*/
