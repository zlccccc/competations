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
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,a,b,k,f;
int i;
map<pair<string,string>,int> MP;
priority_queue<int> MAX;
int ans;
string u,v,tmp,tmpu,pre;
int main(){
	cin>>n>>a>>b>>k>>f;
	REP(i,n){
		cin>>u>>v;
		tmp=v;tmpu=u;
		if (u>v) swap(u,v);
		if (tmpu==pre) MP[make_pair(u,v)]+=b;
		else MP[make_pair(u,v)]+=a;
		pre=tmp;
	}
	for (pair<pair<string,string>,int> now:MP) MAX.push(now.second);
	REP(i,k){
//		if (MAX.empty()||MAX.top()<=f) break;
//		printf("%d->%d\n",MAX.top(),f);
		MAX.push(f);
		MAX.pop();
	}
	while (MAX.size()){
		ans+=MAX.top();
		MAX.pop();
	}
	printf("%d",ans);
}
/*
*/
