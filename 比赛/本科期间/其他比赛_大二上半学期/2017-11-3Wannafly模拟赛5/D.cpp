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
const LL M=998244353;
const LL maxn=1.5e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int a[107],mark[107];
int ans;
vector<int> X,now;
void dfs(int x,int ii){
//	printf("dfs:%d %d\n",x,ii);
	if (ii==X.size()) now.push_back(x);
	int i;
	REP(i,X.size()){
		if (!mark[i]){
			mark[i]=1;
			dfs(x*10+X[i],ii+1);
			mark[i]=0;
		}
	}
}
int check(int x,int ii){
//	printf("%d %d\n",ii,x);
	if (ii==n) return x;
	int ret=0;
	x+=a[ii];
	X.clear();now.clear();
	while (x) X.push_back(x%10),x/=10;
	dfs(0,0);
	vector<int> NOW=now;
	for (int v:NOW) ret=max(ret,check(v,ii+1));
	return ret;
}
int main(){
	int i;
	scanf("%d",&n);
	REP(i,n) scanf("%d",&a[i]);
	printf("%lld\n",check(0,0));
}
/*
*/
