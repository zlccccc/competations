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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int i,j;
int n,m;
int all[maxn];
vector<int> nowans[maxn];
int ans;
struct node{
	int t,d,p,i;
	node(int _t=0,int _d=0,int _p=0,int _i=0):t(_t),d(_d),p(_p),i(_i){}
}a[maxn];
int cmp(node a,node b){
//	if (a.d-a.t==b.d-b.t) return a.d<b.d;
	return a.d>b.d;
}
int main(){
	int i,j;
	scanf("%d",&n);
	FOR(i,1,n){
		scanf("%d%d%d",&a[i].t,&a[i].d,&a[i].p);a[i].i=i;
	}
	sort(a+1,a+1+n,cmp); 
	FOR(j,1,n){
		FOR(i,1,a[j].d){
			if (i-a[j].t>=1&&all[i]+a[j].p>all[i-a[j].t]){
				all[i-a[j].t]=all[i]+a[j].p;
				nowans[i-a[j].t]=nowans[i];
				nowans[i-a[j].t].push_back(a[j].i);
			}
		}
		rFOR(i,1,2000) if (all[i+1]>all[i]) nowans[i]=nowans[i+1],all[i]=all[i+1];
	}
	printf("%d\n",all[1]);
	printf("%d\n",nowans[1].size());
	rREP(i,nowans[1].size()) printf("%d ",nowans[1][i]);
}
/*
*/
