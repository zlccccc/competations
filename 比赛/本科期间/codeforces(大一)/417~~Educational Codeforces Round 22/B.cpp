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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

#define x x_x
#define y y_y
LL n,m;
LL i,j;
LL a[maxn],b[maxn],tot1,tot2,tot;
LL ans;
vector<LL> V;
LL x,y,l,r;
int main(){
	scanf("%I64d%I64d%I64d%I64d",&x,&y,&l,&r);
	i=2e18;
	a[tot1++]=1;
	while (i/a[tot1-1]+1>x) {a[tot1]=a[tot1-1]*x;tot1++;}
	i=2e18;
	b[tot2++]=1;
	while (i/b[tot2-1]+1>y) {b[tot2]=b[tot2-1]*y;tot2++;}
	REP(i,tot1)
		REP(j,tot2) if (a[i]+b[j]>=l&&a[i]+b[j]<=r){
			V.push_back(a[i]+b[j]);
		}
	V.push_back(l-1);
	V.push_back(r+1);
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	ans=0;
//	REP(i,V.size()) printf("%I64d ",V[i]);
	REP(i,V.size()-1) ans=max(ans,V[i+1]-V[i]-1);
	printf("%I64d",ans);
}
