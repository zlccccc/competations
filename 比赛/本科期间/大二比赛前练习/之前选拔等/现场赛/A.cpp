#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const double eps=0.000000001;
const double pi=acos(-1);
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b){return a>0?a:-a;}

int n,m,T;
int i,j;
struct node{
	int i,xl,xr,yl,yr,x,y; 
}a[maxn];
bool cmp1(node a,node b){
	if (a.xr!=b.xr) return a.xr<b.xr;
	return a.xl<b.xl;
};
bool cmp2(node a,node b){
	if (a.yr!=b.yr) return a.yr<b.yr;
	return a.yl<b.yl;
};
bool cmp3(node a,node b){
	return a.i<b.i;
};
set<int> H;
int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		REP(i,n) scanf("%d%d%d%d",&a[i].xl,&a[i].xr,&a[i].yl,&a[i].yr),a[i].i=i;
		sort(a,a+n,cmp1);
		FOR(i,1,n) H.insert(i);
		REP(i,n){
			a[i].x=*H.lower_bound(a[i].xl);
			H.erase(a[i].x);
		}
		sort(a,a+n,cmp2);
		FOR(i,1,n) H.insert(i);
		REP(i,n){
			a[i].y=*H.lower_bound(a[i].yl);
			H.erase(a[i].y);
		}
		sort(a,a+n,cmp3);
		REP(i,n) printf("%d %d\n",a[i].x,a[i].y);
	}
}
