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

LL n,m;
LL i,j;
int ans;
vector<LL> A;
LL a[maxn],c[maxn];
inline void add(int l,int r,LL a,LL b){//l~r+=a+kb//f''(x)
	c[l]+=a;
	c[l+1]-=a;
	c[r+1]-=a;
	c[r+2]+=a;
	c[l+1]+=b;
	c[r+1]-=(r-l+1)*b;
	c[r+2]+=(r-l+1)*b;
	c[r+2]-=b;
}
int main(){
	scanf("%I64d",&n);
	FOR(i,1,n) scanf("%I64d",&a[i]);
	FOR(i,1,n){//->
		int x=a[i];
		if (x>=i){
			add(0,x-i,x-i,-1);
			add(x-i,n-i,0,1);
			add(n-i+1,n-1,x-1,-1);
		}
		else{
			add(0,n-i,i-x,1);
			add(n-i+1,n-i+x,x-1,-1);
			add(n-i+x,n-1,0,1);
		}
	}
	FOR(i,1,n-1) c[i]+=c[i-1];
	FOR(i,1,n-1) c[i]+=c[i-1];
	FOR(i,1,n-1) if (c[i]<c[ans]) ans=i;
	printf("%I64d %d\n",c[ans],ans);
}
/*
5
5 4 3 2 1
*/
