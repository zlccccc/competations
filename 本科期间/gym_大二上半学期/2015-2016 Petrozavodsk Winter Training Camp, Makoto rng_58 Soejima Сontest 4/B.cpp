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

#define MP make_pair
typedef pair<LL,int> pii;//len,pos
LL len[4][maxn];
int n,m;
LL ans;
set<pii> L[4],R[4];
int cnt;
int main(){
	scanf("%d",&n);
	int i,k;
	FOR(i,1,n){
		LL x,y;
		scanf("%I64d%I64d",&x,&y);
		len[0][i]=x+y;len[1][i]=x-y;
		len[2][i]=-x+y;len[3][i]=-x-y;
		if (i!=1) REP(k,4) L[k].insert(MP(len[k][i],i));
	}
	REP(k,4) R[k].insert(MP(len[k][1],0));
	ans=INFF;
	while (cnt+1!=n){
		int k=0;
		REP(i,4) if ((*R[i].rbegin()).first-(*L[i].begin()).first >
					 (*R[k].rbegin()).first-(*L[k].begin()).first) k=i;
//		printf("%d %d\n",)
		ans=min(ans,(*R[k].rbegin()).first-(*L[k].begin()).first);
		int now=(*L[k].begin()).second;
//		printf("%d;%d %d\n",ans,(*R[k].rbegin()).first-(*L[k].begin()).first,now);
		REP(i,4){
			L[i].erase(MP(len[i][now],now));
			R[i].insert(MP(len[i][now],now));
		}
		cnt++;
	}
	printf("%I64d\n",ans);
}
/*
*/
