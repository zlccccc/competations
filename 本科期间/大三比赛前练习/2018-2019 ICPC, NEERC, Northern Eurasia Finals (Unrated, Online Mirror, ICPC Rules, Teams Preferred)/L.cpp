#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define REP(I,N) for (I=0;I<N;I++)
const int inf=0x3f3f3f3f;
const int maxn=1e5+7;
typedef long long ll;

int A[maxn],MAX[maxn];
vector<int> more;
int main(){
	int n,k,i;
	scanf("%d%d",&n,&k);
	FOR(i,1,n) scanf("%d",&A[i]);
	ll ans=0;
	FOR(i,1,n) {
		int t;
		scanf("%d",&t);
		if (MAX[A[i]]==0) {
			MAX[A[i]]=t; k--;
		} else if (MAX[A[i]]<t) {
			more.push_back(MAX[A[i]]);
			MAX[A[i]]=t;
		} else {
			more.push_back(t);
		}
	}
	// for (int v:more) printf("%d ",v);
	sort(more.begin(), more.end());
	REP(i,k) ans+=more[i];
	printf("%lld\n",ans);

}