#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
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
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a*=a) ret=1ll*ret*a%M;return ret;}

int n,m,t,f;
int i,j;
LL k,l;
priority_queue<LL> Q;
LL ans,all;
int main(){
	scanf("%d%d",&n,&f);
	REP(i,n){
		scanf("%d%d",&k,&l);
		ans+=min(l,k);
		if (k>=l) Q.push(0);
		else if (k*2>=l) Q.push(l-k);
		else Q.push(k);
	}
//	printf("%d ",ans);
	REP(i,f){
//		printf("%d ",Q.top());
		ans+=Q.top();
		Q.pop();
	}
	printf("%I64d",ans);
}
