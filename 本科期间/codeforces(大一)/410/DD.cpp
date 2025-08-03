#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
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
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,m;
int ans,i,t;
int a[maxn],b[maxn],c[maxn];
LL sum1,sum2;
LL s1,s2;
bool judge(){
	sum1=sum2=0;
	FOR(i,1,n/2+1) sum1+=a[c[i]],sum2+=b[c[i]];
	return 2*sum1>s1&&2*sum2>s2;
}
int main()
{
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]),c[i]=i,s1+=a[i];
	FOR(i,1,n) scanf("%d",&b[i]),s2+=b[i];
	while (!judge()) random_shuffle(c+1,c+n+1);
	printf("%d\n",n/2+1);
	FOR(i,1,n/2+1) printf("%d ",c[i]);
}
