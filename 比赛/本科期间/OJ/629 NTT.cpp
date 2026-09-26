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
const LL maxn=4e5+7;
const double eps=0.00000001;
const double pi=acos(-1);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

const LL MOD=1945555039024054273;
const LL g=5;
LL mul ( LL x , LL y ) {
    return ( x * y - ( long long ) ( x / ( long double ) MOD * y + 1e-3 ) * MOD + MOD ) % MOD ;
}
LL poww(LL a,LL b){
	LL ret=1;
	for (;b;b>>=1ll,a=mul(a,a))
		if (b&1) ret=mul(ret,a);
	return ret;
}
void ntt(LL *A,int len,int inv){//抄的板子 
	int i,j,k;
	for (i=1,j=len/2;i<len-1;i++){
		if (i<j) swap(A[i],A[j]);
		k=len/2;
		while(j>=k){
			j-=k;
			k/=2;
		}if (j<k) j+=k;
	}
	for(i=2;i<=len;i<<=1){
		LL wn=poww(g,(MOD-1)/i);
		if (inv==-1) wn=poww(wn,MOD-2);
		for (j=0;j<len;j+=i){
			LL w=1;
			for (k=j;k<(j+i/2);k++){
				LL a=A[k],b=mul(w,A[k+i/2]);
				A[k]=(a+b)%MOD;
				A[k+i/2]=(a-b+MOD)%MOD;
				w=mul(w,wn);
			}
		}
	}
	if (inv==-1){
		LL vn=poww(len,MOD-2);
		REP(i,len) A[i]=mul(A[i],vn);
	}
}
//喵的没卡FFT... 
LL x1[maxn];
LL ans[maxn];
int main(){
	int n,q;
	int i,j,k;
	int T;
	scanf("%d",&T);
	int len=1;
	while(len<=200000) len<<=1;
	while (T--){
		scanf("%d%d",&n,&q);
		REP(i,len) ans[i]=x1[i]=0;
		REP(i,n) scanf("%d",&k),x1[k]++,ans[k*2]--;
		ntt(x1,len,1);
//		REP(i,len) printf("%lf %lf\n",x1[i].a,x1[i].b);
//		REP(i,len) printf("%lf %lf\n",x2[i].a,x2[i].b);
		REP(i,len) x1[i]=mul(x1[i],x1[i]);
		ntt(x1,len,-1);
		REP(i,len) ans[i]+=x1[i];
		REP(i,len) ans[i]/=2;
//		REP(i,20) printf("%d:%d ",i,ans[i]);puts("");
		REP(i,len-1) ans[i+1]+=ans[i];
		REP(i,q) scanf("%d",&k),printf("%lld\n",ans[k-1]);
	}
}
/*
*/
