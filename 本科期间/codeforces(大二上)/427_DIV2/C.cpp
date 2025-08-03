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
const LL maxn=5007+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,X,Y;
int A[maxn];
int aski(int t){
	int ret,i,n=0;
	FOR(i,1,::n) if ((i>>t)&1) n++;
	if (!n) return 0;
	fflush(stdout);
	cout<<"? "<<n;
	FOR(i,1,::n) if ((i>>t)&1) cout<<" "<<i;
	cout<<"\n";
	cin>>ret;
	if (n&1) ret^=X;
	return ret;
}
int askn(int n){
	if (!n) return 0;
	int ret,i;
	fflush(stdout);
	cout<<"? "<<n;
	FOR(i,1,n) cout<<" "<<A[i];
	cout<<"\n";
	cin>>ret;
	if (n&1) ret^=X;
	return ret;
}
int l,r;
int all,now;
int main(){
	cin>>n>>X>>Y;
	int i;
	FOR(i,0,9) if (aski(i)) all^=1<<i,now=i;
	FOR(i,1,n) if (!((i>>now)&1)) A[++m]=i;
	l=0;r=m;
	while(l+1<r){
		int mid=(l+r)/2;
		if (!askn(mid)) l=mid;
		else r=mid;
	}
	cout<<"! "<<A[r]<<" "<<(A[r]^all);
}
/*
*/
