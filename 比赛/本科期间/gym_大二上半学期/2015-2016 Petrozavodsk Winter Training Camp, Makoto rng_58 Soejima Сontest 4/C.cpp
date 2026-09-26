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
const LL maxn=160000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,i,k;
const int MID=80000;
int a[maxn];
queue<int> Q[2];
int val[2][maxn];
int now;
int main(){
	scanf("%d",&n);
	REP(i,n) scanf("%d",&a[i]),a[i]*=2;
	FOR(i,0,2*MID) val[0][i]=val[1][i]=INF;
	val[0][MID]=0;Q[0].push(0);
	FOR(k,0,100000){
		if (Q[now].empty()) break;
		while (Q[now].size()){
			int t=Q[now].front();Q[now].pop();
			REP(i,n)
			if (MID+a[i]-t>=0&&MID+a[i]-t<=2*MID&&val[now^1][MID+a[i]-t]==INF){
//				printf("change::%d:%d,pos=%d\n",a[i]-t,k+1,MID+a[i]-t);
				val[now^1][MID+a[i]-t]=k+1;
				Q[now^1].push(a[i]-t);
			}
		}now^=1;
	}
	scanf("%d",&n);
	while (n--){
		int x,y;
		scanf("%d%d",&x,&y);
		int ans=min(val[0][MID+y-x],val[1][MID+y+x]);
		if (ans==INF) puts("-1");
		else printf("%d\n",ans);
	}
}
/*
*/
