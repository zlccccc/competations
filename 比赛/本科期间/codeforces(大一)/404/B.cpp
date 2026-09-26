#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

map<string,int> Q;
int ans,n,i;
int s1,s2,t1,t2;
int l,r;
int main(){ 
	scanf("%lld",&n);
	t1=INF;
	REP(i,n){
		scanf("%d%d",&l,&r);
		if (l>s1) s1=l;
		if (r<t1) t1=r;
	}
	scanf("%lld",&n);
	t2=INF;
	REP(i,n){
		scanf("%d%d",&l,&r);
		if (l>s2) s2=l;
		if (r<t2) t2=r;
	}
	ans=max(s1-t2,s2-t1);
	ans=max(ans,0);
	printf("%d",ans);
}
/*
*/
