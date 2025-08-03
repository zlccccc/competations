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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

struct node{
	int x1,x2,y1,y2;
	int cnt1,cnt2,cnt3,cnt4;
}t[maxn];
int n,m;
int a[maxn],b[maxn],c[maxn],d[maxn];
int cnt1,cnt2,cnt3,cnt4;
int i,j,k,ans;
int main(){
	scanf("%d%d%d",&k,&n,&m);
	REP(i,k){
		scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
		if (a[i]>c[i]) swap(a[i],c[i]);
		if (b[i]>d[i]) swap(b[i],d[i]);
		t[i].x1=a[i];t[i].x2=c[i];t[i].y1=b[i];t[i].y2=d[i];
	}
	sort(a,a+k);
	sort(b,b+k);
	sort(c,c+k);
	sort(d,d+k);
	REP(i,k) {t[i].cnt1=lower_bound(a,a+k,t[i].x2)-a;if (t[i].x1<t[i].x2) t[i].cnt1--;}
	REP(i,k) {t[i].cnt2=c+k-lower_bound(c,c+k,t[i].x1+1);if (t[i].x2>t[i].x1) t[i].cnt2--;}
	REP(i,k) {t[i].cnt3=lower_bound(b,b+k,t[i].y2)-b;if (t[i].y1<t[i].y2) t[i].cnt3--;}
	REP(i,k) {t[i].cnt4=d+k-lower_bound(d,d+k,t[i].y1+1);if (t[i].y2>t[i].y1) t[i].cnt4--;}
//	REP(i,k) printf("%d %d %d %d\n",t[i].cnt1,t[i].cnt2,t[i].cnt3,t[i].cnt4);
	scanf("%d%d%d%d",&cnt1,&cnt2,&cnt3,&cnt4);
	REP(i,k) if (t[i].cnt1==cnt1&&t[i].cnt2==cnt2&&t[i].cnt3==cnt3&&t[i].cnt4==cnt4) ans=i+1;
	if (ans>0) printf("%d",ans);
	else puts("-1");
}
/*
*/
