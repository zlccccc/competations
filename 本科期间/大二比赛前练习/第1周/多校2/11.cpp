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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

int n;
int i,j;
LL ans;
int a[maxn],b[maxn];
set<pair<int,int> > S;
LL solve(int n){
	S.clear();
	REP(i,n) scanf("%d%d",&a[i],&b[i]),S.insert(make_pair(a[i],b[i]));
	ans=0;
	REP(i,n){
		REP(j,n){
			int x1=a[i],x2=a[j],y1=b[i],y2=b[j];
			if (x1>=x2) continue;
			if (y1>=y2) continue;
			if ((x1+x2+y1+y2)%2==1) continue;
			if (S.count(make_pair((x1+x2+y2-y1)/2,(y1+y2-x2+x1)/2))&&
				S.count(make_pair((x1+x2-y2+y1)/2,(y1+y2+x2-x1)/2))) ans++;
		}
	}
	printf("%d\n",ans);
}
int main(){
	while (~scanf("%d",&n)) solve(n);
}
/*
*/
