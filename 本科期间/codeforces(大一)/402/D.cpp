#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue> 
#include <cstring> 
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
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

LL n,m;
char s[N];
char a[N];
bool b[N];
LL de[N];
LL i,j,k,l,r,mid;
bool could(LL mid){
	LL i,j,k;
	REP(i,n) b[i]=0;
	FOR(i,1,mid) b[de[i]-1]=1;
	j=0;
	REP(i,n) if (!b[i]&&s[i]==a[j]) j++;
//	cout<<j<<mid<<' ';
	if (j>=m) return 1;
	return 0;
}
int main(){
	scanf("%s",&s);
	scanf("%s",&a);
	n=strlen(s);
	m=strlen(a);
	FOR(i,1,n) scanf("%I64d",de+i);
	l=0;r=n+1;
	while (l+1<r){
		mid=(l+r)/2;
		if (could(mid)) l=mid;
		else r=mid;
	}
	printf("%I64d",l);
}
/*
*/
