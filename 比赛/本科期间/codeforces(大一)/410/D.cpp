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
int pos,k,sum1,sum2;
struct node{
	int x,y,i;
	bool operator <(const node &a)const{
		return x>a.x;
	}
}a[maxn];
int main()
{
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i].x),a[i].i=i;
	FOR(i,1,n) scanf("%d",&a[i].y);
	sort(a+1,a+n+1);
	printf("%d\n",n/2+1);
	printf("%d ",a[1].i);
	FOR(i,1,n/2) if (a[i*2].y>a[i*2+1].y) printf("%d ",a[i*2].i);
	else printf("%d ",a[i*2+1].i);
}
