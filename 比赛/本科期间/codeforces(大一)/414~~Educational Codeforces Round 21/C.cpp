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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a*=a) ret=1ll*ret*a%M;return ret;}

struct node{
	int id,n;
	operator <(const node&A){
		if (n==A.n) return id<A.id;
		return n>A.n;
	}
}a[maxn];
int n,w,ww;
int b[maxn],c[maxn];
int i,mx;
int main(){
	scanf("%d%d",&n,&w);
	FOR(i,1,n) scanf("%d",&a[i].n),a[i].id=i;
	sort(a+1,a+1+n);
	rFOR(i,1,n){
		b[i]=max(b[i+1],a[i].n-a[i].n/2);
		w-=b[i];
		if (w<0||b[i]>a[i].n) return 0*puts("-1");
	}
	b[0]=INF;
	FOR(i,1,n){
		if (w==0) break;
		mx=min(b[i-1],a[i].n);
		if (mx-b[i]>w) b[i]+=w,w=0;
		else{
			w-=mx-b[i];
			b[i]=mx; 
		}
	}
	if (w>0) return 0*puts("-1");
	FOR(i,1,n) c[a[i].id]=b[i];
	FOR(i,1,n) printf("%d ",c[i]); 
}
