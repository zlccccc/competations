#include<bits/stdc++.h>
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
using namespace std;
const int maxn=1<<15|7;
const int mod=1e9+7;
typedef long long ll;
int powMM(int a,int b) {
	int ret=1;
	for (;b;b>>=1,a=(ll)a*a%mod)
		if (b&1) ret=(ll)ret*a%mod;
	return ret;
}
int f[maxn],mul[maxn];
int mark[57],pos[57],value[57];
int l[57],r[57];
int main() {
	int i,n,m;
	scanf("%d%d",&n,&m);
	REP(i,m) scanf("%d%d",&l[i],&r[i]),l[i]--;
	REP(i,m) pos[i*2]=l[i],pos[i*2+1]=r[i];
	pos[m+m]=0; sort(pos,pos+m+m+1);
	int k=unique(pos,pos+m+m+1)-pos;
	int base=powMM(10,n-pos[k-1]);//right_side
	// printf("base0=%d; %d\n",base,pos[0]+n-pos[k-1]);
	REP(i,k-1) {
		int x=(ll)(powMM(10,pos[i+1]-pos[i])+mod-1)*powMM(9,mod-2)%mod;
		// printf("%d; x=%d\n",pos[i+1]-pos[i],x);
		value[i]=(ll)(x+1)*powMM(x,mod-2)%mod;
		base=(ll)base*x%mod;
	}
	// printf("base=%d\n",base);
	int sta,nxt,all=1<<m;
	REP(sta,all) {
		REP(i,k) mark[i]=0;
		REP(i,m) if ((sta>>i)&1) {
			mark[lower_bound(pos,pos+k,l[i])-pos]=1;
			mark[lower_bound(pos,pos+k,r[i])-pos]=1;
		} mul[sta]=1;
		REP(i,m) if (!((sta>>i)&1)){
			if (mark[lower_bound(pos,pos+k,l[i])-pos]) mul[sta]=0;
			if (mark[lower_bound(pos,pos+k,r[i])-pos]) mul[sta]=0;
		} f[sta]=mul[sta];
		if (mark[0]) mul[sta]=0;
		REP(i,k-1) if (mark[i]&&mark[i+1])
			mul[sta]=(ll)mul[sta]*value[i]%mod;
		mark[0]=1;
		REP(i,k-1) if (mark[i]&&mark[i+1])
			f[sta]=(ll)f[sta]*value[i]%mod;
		// printf("sta=%d; f=%lld x=%lld\n",sta,(ll)f[sta]*base%mod,(ll)mul[sta]*base%mod);
	} FOR(i,1,8) {
		rREP(sta,all) {
			for (nxt=sta; nxt; nxt=sta&(nxt-1))
				f[sta]=(f[sta]+(ll)f[sta^nxt]*mul[nxt])%mod;
		}
		// REP(sta,all) printf("%lld ",(ll)f[sta]*base%mod); puts("");
		// printf("%d: %lld\n",i,(ll)f[all-1]*base%mod);
	} printf("%lld\n",(ll)f[all-1]*base%mod);
	return 0;
}
/*
*/