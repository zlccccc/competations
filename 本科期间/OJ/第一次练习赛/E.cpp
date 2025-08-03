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
const LL maxn=5e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

#define MP make_pair
int n,m,i,j,k;
int s,t,ans1,ans2;
map<int,pair<int,pair<int,int> > > now;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		REP(i,n){
			int P,V;
			scanf("%d%d",&P,&V);
			auto &x=now[P];
			x.first++;
			if (x.second.first<V) x.second=MP(V,0);
			if (x.second.first==V) x.second.second++;
		}
		ans1=0;ans2=0;
		bool mark=0;
		while (now.size()){
			auto y=*now.begin();now.erase(now.begin());
			ans1=y.first;
			if (mark) {mark^=1;continue;}
			auto &x=now[y.first+y.second.second.first];
			x.first+=y.second.second.second;
			if (x.second.first<y.second.second.first) x.second=MP(y.second.second.first,0);
			if (x.second.first==y.second.second.first) x.second.second+=y.second.second.second;
			y.second.first-=y.second.second.second;
			ans2+=y.second.first;
			if (!y.second.first) mark^=1;
		}
		printf("%d %d\n",ans1,ans2);
	}
}
/*
*/
