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
const LL maxn=5e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const double eps=0.000001;

//维护val //left,right各一个 
int T;
set<int> S;
int a[maxn];
int pos[maxn];
set<int>::iterator it1,it2;
int l,r;
int n,k;
LL l0,l1,r0,r1;
LL ans;
int i,j;
int main()
{
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&k);
		ans=0;
		FOR(i,1,n) scanf("%d",&a[i]),pos[a[i]]=i;
		S.clear();
		S.insert(0);S.insert(n+1);
		rFOR(i,1,n){
			S.insert(pos[i]);
			it1=it2=S.lower_bound(pos[i]);
			l=0;
			REP(j,k+1){
				if (*it1==0) break;
				it1--;l++;
			}
			while (l+r<k){
				it2++;r++;
				if (*it2==n+1) break;
			}
			if (l+r<k) continue;
			l0=*it1;r0=*it2;
			printf("%d : %d %d %d %d\n",i,l0,l1,r0,r1);
			while (1){
				it1++;l--;
				it2++;r++;
				if (*it1==pos[i]) break;
				l1=*it1,r1=*it2;
				ans+=i*(r1-r0-1)*(l1-l0);
				l0=*it1;r0=*it2;
				if (*it2==n+1) break;
			}
		}
		printf("%lld",ans);
	}
	return 0;
}
/*
*/
