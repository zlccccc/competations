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
const LL maxn=4e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

typedef pair<int,LL> pii;
int n,l,m,k;
void Merge(pii *A,pii *B,int &now,int len,LL &DEL){
	int i,j;
	REP(i,len) A[now++]=B[i];
	j=0;
	REP(i,now){
		if (j&&A[i].first==A[j-1].first){
			A[j-1].second+=A[i].second;
			DEL+=A[j-1].second/k*k;A[j-1].second%=k;
			if (A[j-1].second==0) j--;
		}else A[j++]=A[i];
	}now=j;
}
int i,j;
bool mark;
pii A[maxn],B[maxn];
LL del,cnt,now,ans;
int main(){
	scanf("%d%d%d",&n,&k,&m);
	REP(i,n) scanf("%d",&A[i].first),A[i].second=1;
	cnt=n;l=0;
	FOR(i,0,31){
//		mark_0=0;
//		FOR(i,1,n-1) if (A[i]!=A[i+1]) mark_0=1;
//		if (mark_0) return 0*printf("%I64d\n",n*m%k);
		if ((m>>i)&1){ans+=cnt;now=0;if (l>=200000) now=del;else Merge(B,A,l,n,now);ans-=now;}
		if (!mark){del=0;Merge(A,A,n,n,del);if (n>=200000) mark=1;}
//		printf("l,n,m=%d %d %d; cnt=%d, now=%d, del=%d, ans=%d\n",l,n,m,cnt,now,del,ans);
//		REP(j,n) printf("%d-%d ",A[j].first,A[j].second);puts("< -- A");
//		REP(j,l) printf("%d-%d ",B[j].first,B[j].second);puts("< -- B");
		cnt=cnt*2-del;
	}
	printf("%I64d\n",ans);
}
/*
1 9 10
1
*/
