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

vector<int> H;
queue<int> Q[maxn];
int ans;
int n,k;
int a[maxn];
int main(){
	scanf("%d%d",&n,&k);
	int i;
	FOR(i,1,n) scanf("%d",&a[i]),H.push_back(a[i]);
	sort(H.begin(),H.end());
	H.erase(unique(H.begin(),H.end()),H.end());
	FOR(i,1,n) a[i]=lower_bound(H.begin(),H.end(),a[i])-H.begin();
	FOR(i,1,n){
		Q[a[i]].push(i);
		while (i-Q[a[i]].size()-Q[a[i]].front()+1>k) Q[a[i]].pop();
		ans=max(ans,(int)Q[a[i]].size());
	} 
	printf("%d\n",ans);
}
/*
8 2
1 2 1 2 2 3 2 2
*/
