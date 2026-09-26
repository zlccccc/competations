#include <bits/stdc++.h>
using namespace std;
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define REP(I,N) for (I=0;I<N;I++)
typedef long long ll;
typedef pair<int,int> pii;
const int maxn=2e5+7;
const ll inf=0x3f3f3f3f;
const ll mod=998244353;
ll powMM(ll a,ll b){
	ll ret=1;
	for (;b;b>>=1,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}

ll fac[maxn];
ll inv[maxn];
ll f[maxn];
ll C(int n,int m){
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init(){
	int i; fac[0]=1;
	FOR(i,1,200000) fac[i]=fac[i-1]*i%mod;
	inv[0]=inv[1]=1;
	FOR(i,2,200000) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	FOR(i,1,200000) inv[i]=inv[i]*inv[i-1]%mod;
	f[0]=1; int j;
	FOR(i,1,2000) {
		f[i]=f[i-1];//1
		FOR(j,2,i) f[i]=(f[i]+f[i-j]*powMM(j,j-2)%mod*C(i-1,j-1))%mod;
	}
	FOR(i,1,10) printf("%lld ",f[i]);
}
int main(){
	init();
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		int n,m;
		int i;
		scanf("%d%d",&n,&m);
		ll all=0,ans=0;
		if (n>1){
			all=fac[n]*inv[2]%mod;
			ans=all*m%mod*m%mod;
			printf("0: %lld %lld\n",all,ans);//todo : change
		}
		FOR(i,1,n-1) {//in this; 边数
			ll now=C(n-2,i-1)*fac[i-1]%mod;//in_node:i-1
			ll now2=f[n-i-1];//不连
			now2=(now2+(i+1)*(f[n-i]-f[n-i-1]))%mod;//link
			printf(" now2: %lld + %lld * %d\n",f[n-i-1],f[n-i]-f[n-i-1],i+1);
			now=now*now2%mod;
			ans=(ans+now*i%mod*i)%mod;
			all=(all+now)%mod;
			printf("%d: %lld %lld\n",i,now,now*i%mod*i%mod);
		} printf("%lld\n",ans);
		ans=ans*C(n,2)%mod;
		ans=ans*powMM(all,mod-2)%mod;
		printf("%lld\n",ans);
	}
}