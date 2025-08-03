#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;

int n,m;
int i,j,k;
LL t;
multiset<LL> S[1<<6];
LL val[maxn][1<<6];
LL ans;
int main(){
	while (~scanf("%d%d",&n,&m)){
		FOR(i,1,n){
			scanf("%d",&k);
			if (k==0){
				memset(val[i],0,sizeof(val[i]));
				REP(j,m){
					scanf("%lld",&t);
					FOR(k,1,(1<<m)-1){
						if (k&(1<<j)) val[i][k]+=t;
						else val[i][k]-=t;
					}
				}
				FOR(k,1,(1<<m)-1) S[k].insert(val[i][k]);
			}else {
				scanf("%lld",&t);
				FOR(k,1,(1<<m)-1) S[k].erase(S[k].find(val[t][k]));
			}
			ans=0;
			FOR(k,1,(1<<m)-1) if (S[k].size()) ans=max(ans,(*S[k].rbegin())-(*S[k].begin()));
			printf("%lld\n",ans);
		}
		FOR(k,1,(1<<m)-1) S[k].clear();
	}
}
/*
*/
