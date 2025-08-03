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
const LL maxn=100+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,i;
int l[maxn],r[maxn];
int main(){
	while (~scanf("%d",&n)){
		int x,h;
		FOR(i,0,100) l[i]=INF,r[i]=-INF;
		REP(i,n) scanf("%d%d",&x,&h),l[h]=min(l[h],x),r[h]=max(r[h],x);
		int ans=0,L=INF,R=-INF;
		rFOR(i,0,100){
			L=min(l[i],L);R=max(r[i],R);
			if (R>=0&&L<=0) ans=max(ans,(R-L)*(R-L)*i);
		}
		printf("%.3lf\n",pi/4*ans);
	}
}
/*
*/
