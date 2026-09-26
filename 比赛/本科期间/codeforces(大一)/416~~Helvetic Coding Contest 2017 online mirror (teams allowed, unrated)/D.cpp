#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
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
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


priority_queue<pair<int,int> > Q;
set<int> S;
int a[maxn];
int ans;
int i,n,m,k; 
int solve(){
	int i,j;
	double sum=0,cnt=0;
	REP(i,250) scanf("%d",&a[i]),sum+=a[i];
	sum=sum/250.0;
	REP(i,250) if (0.5*sum<=a[i]&&a[i]<=1.5*sum) cnt++;
	cnt=cnt/250.0;
	if (cnt>0.7) return 0*puts("poisson");
	return 0*puts("uniform");
}
int main(){
	scanf("%d",&n);
	REP(i,n) solve();
}
/*
*/
