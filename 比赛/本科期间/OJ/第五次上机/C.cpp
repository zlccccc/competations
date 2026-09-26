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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

template<class T> 
bool read_d(T &num){
	char in;bool IsN=false;
	in=getchar();
	if (in==EOF) return false;
	while (in!= '-'&&(in<'0'||in>'9')) in=getchar();
	if (in=='-') {IsN=1;num=0;}
	else num=in-'0';
	while (in=getchar(),in>='0'&&in<='9') num=num*10+in-'0';
	if (IsN) num=-num;
	return 1;
}
int T,n,m; 
int a[maxn],p[maxn],h[maxn];
LL ans;
int cmp(int x,int y){
	return a[x]<a[y];
}
int main(){
	while (~scanf("%d",&n)){
		LL all=0;int i;
		FOR(i,1,n) read_d(a[i]),h[i]=0,p[i]=i;
		a[0]=a[n+1]=INF;
		sort(p+1,p+n+1,cmp);
		FOR(i,1,n){
			int pos=p[i];
			h[pos]=1;
			if (a[pos]>a[pos-1]) h[pos]=max(h[pos],h[pos-1]+1);
			if (a[pos]>a[pos+1]) h[pos]=max(h[pos],h[pos+1]+1);
			all+=h[pos];
		}
//		FOR(i,1,n) printf("%d ",h[i]);puts("");
		printf("%lld\n",all);
	}
}
/*
*/
