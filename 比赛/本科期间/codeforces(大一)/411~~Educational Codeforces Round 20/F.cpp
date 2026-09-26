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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


int n,m;
int i,j,k;
map<int,int> MP[2];
map<int,int>::iterator ii;
int tot,t,ans;
int main(){
	printf("%d",tot);
	scanf("%d",&n);
	REP(i,n){
		scanf("%d",&t);
		MP[now].clear();
		for (ii=MP[now^1].begin();ii!=MP[now^1].end();ii++) MP[now][gcd(ii->first)]+=ii->second;
		ans=(ans+MP[now][1])%MOD;
	}
	printf("%d",ans);
}
/*
*/
