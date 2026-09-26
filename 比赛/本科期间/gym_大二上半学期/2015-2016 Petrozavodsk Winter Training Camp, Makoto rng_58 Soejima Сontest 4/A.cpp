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

const LL inf=1e18;
#define MP make_pair
LL p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
typedef pair<LL,LL> pii;
int n,m,tot,i;
LL ans[maxn];
set<LL> have;
priority_queue<pii> Q;
LL MAX,MAXX;
int main(){
	scanf("%d",&n);
	Q.push(MP(-1,1));
	while (Q.size()){
		auto now=Q.top();Q.pop();
		if (have.count(now.first)) continue;
		have.insert(now.first);
		if (now.second>=MAXX){
			ans[++tot]=-now.first;
//			printf("%-5lld - %3d ; %d\n",-now.first,now.second,tot);
			LL val=-now.first;
			REP(i,25){
				if (inf/p[i]<-now.first) break;
				int cnt=0;
				while(val%p[i]==0) cnt++,val/=p[i];cnt++;
				Q.push(MP(now.first*p[i],now.second/cnt*(cnt+1)));
			}
		}
//		printf("POS:%d %d %d\n",MAX,MAXX,now.second);
		MAXX=max(MAXX,now.second);
		if (MAX<MAXX) swap(MAX,MAXX);
	}
	if (n>tot) puts("-1");
	else printf("%I64d\n",ans[n]);
}
/*
*/
