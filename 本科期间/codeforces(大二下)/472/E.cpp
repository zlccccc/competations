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
#include <cassert>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,l,r;
pair<int,int> A[maxn];
int sum;
int F[maxn],ans;
int main(){
	int i,k;
	scanf("%d%d%d",&n,&l,&r);
	FOR(i,1,n) scanf("%d",&A[i].second),sum+=A[i].second,A[i].second=-A[i].second;
	swap(l,r);l=sum-l;r=sum-r;
	FOR(i,1,n) scanf("%d",&A[i].first);
	sort(A+1,A+1+n);
	FOR(i,1,sum) F[i]=-n;
	FOR(i,1,n){
		rFOR(k,0,sum){
			int t=k-A[i].second;
			F[t]=max(F[t],F[k]+(A[i].first&&(l<=t&&t<=r)));
		}
	}
	// dbg(l);dbgln(r);
	// FOR(i,1,sum) printf("%d ",F[i]);
	// puts("");
	FOR(i,1,sum) ans=max(ans,F[i]);
	printf("%d\n",ans);
}
/*
*/
