#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const LL M=1e9+7;
const LL N=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

int n,k,x;
int a[2002];
int b[2002];
int i,j;
bool mark;
int mx,mn;
int main(){
	scanf("%d%d%d",&n,&k,&x);
	REP(i,n) scanf("%d",&j),a[j]++;
	REP(i,k){
		mark=1;
		FOR(j,0,2000) if (a[j]){
			if (mark) a[j]--,b[j^x]++;
			mark=a[j]&1;
			b[j^x]+=a[j]>>1;
			a[j]-=a[j]>>1;
		}
		FOR(j,0,2000) if (b[j]) a[j]+=b[j],b[j]=0;
	}
	mn=-1;
	FOR(j,0,2000) if (a[j]){
		if (mn==-1) mn=j;
		mx=j;
//		printf("a[%d]=%d  ",j,a[j]);
	}
	printf("%d %d",mx,mn);
}
/*
5 1 2
9 6 11 15 5
2 100001 569
605 986
*/
