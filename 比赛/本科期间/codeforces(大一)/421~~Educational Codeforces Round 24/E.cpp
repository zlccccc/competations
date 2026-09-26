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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

map<int,LL> now,MP;
map<int,LL>::iterator it;
int n,m,k;
int a[maxn];
LL ans;
int i;
int main(){
	scanf("%d%d",&n,&k);
	REP(i,n) scanf("%d",&a[i]);
	REP(i,n){
		now.clear();
		for (it=MP.begin();it!=MP.end();it++) now[(*it).first/gcd((*it).first,a[i])]+=(*it).second;
		swap(MP,now);MP[k/gcd(k,a[i])]++;
		ans+=MP[1];
//		for (it=MP.begin();it!=MP.end();it++) printf("%d %d\n",(*it).first,(*it).second);
	}
	printf("%I64d",ans);
}
/*
*/
