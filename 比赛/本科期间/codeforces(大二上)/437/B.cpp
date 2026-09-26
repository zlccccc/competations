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

vector<pair<LL,LL> > V;
LL n,s;
LL t[maxn],a[maxn],b[maxn];
LL ans=0,all,cnt;
void solve(){
	LL now=0,cur=0;V.clear();
	int i; 
	REP(i,n){
		if (b[i]-a[i]>=0){
			V.emplace_back(b[i]-a[i],t[i]);
			cur+=t[i];
		}now+=t[i]*a[i];
	}
	sort(V.begin(),V.end());
	cur=cur/s*s;
	rREP(i,V.size()){
		auto &x=V[i];
		now=now+x.first*min(x.second,cur);
		cur-=min(x.second,cur);
	}ans=max(ans,now);
//	printf("%d ",cur);
}
int main(){
	scanf("%I64d%I64d",&n,&s);
	int i;
	REP(i,n){
		scanf("%I64d%I64d%I64d",&t[i],&a[i],&b[i]);
		all+=t[i];
	}
	cnt=all/s+(all%s!=0);//¿ÉËã³ö²î 
	t[n]=cnt*s-all;a[n]=b[n]=0;n++;
	solve();
	REP(i,n) swap(a[i],b[i]);
	solve();
	printf("%I64d\n",ans);
}
/*
*/
