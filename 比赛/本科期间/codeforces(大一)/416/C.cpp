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
const LL maxn=5007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a*=a) ret=1ll*ret*a%M;return ret;}

#define x x_x
int n,m,T;
int i,j,k1,k2,t,kk;
int a[maxn];
int l[maxn],r[maxn],ans[maxn];//first,last
int main(){
	scanf("%d",&n);
	FOR(i,1,n){
		scanf("%d",&a[i]);
		if (l[a[i]]==0) l[a[i]]=i;
		r[a[i]]=i;
	}
	FOR(i,1,n){
		ans[i]=ans[i-1];
		t=0;kk=i;
		rFOR(j,1,i){
			kk=min(l[a[j]],kk);
			if (r[a[j]]>i) break;
			if (r[a[j]]==j) t^=a[j];
			if (kk==j) ans[i]=max(ans[i],ans[j-1]+t);
		}
	}
//	FOR(i,1,n) printf("%d ",ans[i]);
	printf("%d",ans[n]);
}
