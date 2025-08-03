
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
const LL M=10007;
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j,k;
int s,t,ans;
int cnt[maxn],maxv[maxn],maxcnt[maxn];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		s=-1,t=0;
		REP(i,n){
			int P,V;
			scanf("%d%d",&P,&V);
			cnt[P]++;
			if (maxv[P]<V) maxv[P]=V,maxcnt[P]=0;
			if (maxv[P]==V) maxcnt[P]++;
			t=max(t,P);
		}
		bool mark=0;ans=0;
		while (s<=t){
			s++;
			if (!cnt[s]) continue;
//			printf("%d %d %d %d %d\n",mark,s,cnt[s],maxv[s],maxcnt[s]); 
			if (!mark){
				t=max(t,s+maxv[s]);
				cnt[s+maxv[s]]+=maxcnt[s];cnt[s]-=maxcnt[s];
				if (maxv[s+maxv[s]]<maxv[s]) maxv[s+maxv[s]]=maxv[s],maxcnt[s+maxv[s]]=0;
				if (maxv[s+maxv[s]]==maxv[s]) maxcnt[s+maxv[s]]+=maxcnt[s];
				ans+=cnt[s];
				if (!cnt[s]) mark^=1;
			}else mark^=1;
		}
		FOR(i,0,t) cnt[i]=maxv[i]=maxcnt[i]=0;
		printf("%d %d\n",t,ans);
	}
}
/*
*/
