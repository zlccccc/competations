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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,ans;
int a[maxn];
int query(int i,int j){
	fflush(stdout);
	int ret;
	cout<<'?'<<' '<<i<<' '<<j<<'\n';
	cin>>ret;
	return ret;
}
int qq[maxn],q1[maxn],q2[maxn],q0;
int p[maxn],b[maxn],A[maxn];
bool mark[maxn];
int check(int x){
	int i;
	b[0]=x;
	REP(i,n-1) b[i+1]=b[i]^qq[i];
	REP(i,n) mark[i]=0;
	REP(i,n) p[b[i]]=i;
//	REP(i,n) printf("%d ",p[i]);puts(" --> p");
//	REP(i,n) printf("%d ",b[i]);puts(" --> b");
	REP(i,n) {if (b[i]>=n) return 0;if (mark[b[i]]) return 0;mark[b[i]]=1;}
//	puts("OK_1");
	REP(i,n-1) if ((p[i+1]^b[i])!=q1[i]) return 0;
//	puts("OK_2");
	REP(i,n-1) if ((p[i+1]^b[i+1])!=q2[i]) return 0;
//	puts("OK_3");
	if ((p[0]^b[0])!=q0) return 0;
	return 1;
}
int main(){
	cin>>n;
	int i,j;
	REP(i,n-1){
		q1[i]=query(i+1,i);
		q2[i]=query(i+1,i+1);
		qq[i]=q1[i]^q2[i];
	}q0=query(0,0);
	REP(i,n) if (check(i)){
		ans++;
		REP(j,n) A[j]=p[j];
	}
	printf("!\n%d\n",ans);
	REP(i,n) printf("%d ",A[i]);
}
/*
2 0 3 0 2 0 0
1 0 3 0 0
*/
