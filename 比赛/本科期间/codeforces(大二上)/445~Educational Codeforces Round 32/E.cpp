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
const LL maxn=1e5+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int a[37];
vector<int> V1,V2;
int ans;
int calc(int x){
	int now=0,i;
	REP(i,n) if ((x>>i)&1) {
		now+=a[i];
		while (now>=m) now-=m;
	}return now;
}
int main(){
	int i;
	scanf("%d%d",&n,&m);
	int tmp=n-n/2;n/=2;
	REP(i,n) scanf("%d",&a[i]);
	REP(i,(1<<n)) V1.push_back(calc(i));
	n=tmp;
	REP(i,n) scanf("%d",&a[i]);
	REP(i,(1<<n)) V2.push_back(-calc(i));
	sort(V2.begin(),V2.end());
	for (int v:V1){
		auto it=upper_bound(V2.begin(),V2.end(),v-m);
		if (it!=V2.end()){
			int now=*it;
			ans=max(ans,(-now+v)%m);
		}it=upper_bound(V2.begin(),V2.end(),v-2*m);
		if (it!=V2.end()){
			int now=*it;
			ans=max(ans,(-now+v)%m);
		}
	}
	printf("%d\n",ans);
}
/*
*/
