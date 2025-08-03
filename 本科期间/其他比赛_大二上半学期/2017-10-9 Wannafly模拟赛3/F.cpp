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
const LL maxn=5e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//time-cnt(l->r)--->r
//r-cnt(l->r)>=k
#define MP make_pair 
vector<int> now[maxn];//time-cnt=now,cnt++
vector<pair<int,int> > init[maxn];
int ans;
int n,m;
int a[maxn];
int nowtime,to;//->toȫ 1 
int i;
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,m){
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		init[l].push_back(MP(r,k));
	}
	FOR(i,1,n){
		for (auto x:init[i]) if (x.first-x.second+1-nowtime>=0) now[x.first-x.second+1-nowtime].push_back(x.first);
		for (auto x:now[i-nowtime]) to=max(to,x);
		now[i-nowtime].clear();
		if (i<=to) nowtime++,ans++;
//		if (i<=to) printf("%d ",i);
//		printf("%d,%d\n",i,to);
	}
	printf("%d\n",ans);
}
/*
11 5
3 7 3
8 10 3
6 8 1
1 3 1
10 11 1
*/
