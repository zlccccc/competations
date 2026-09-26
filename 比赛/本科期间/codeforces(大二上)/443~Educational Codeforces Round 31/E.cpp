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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//卡空间。。很难受  
int n,m,i,j;
bool a[1<<16|7],p[1<<16|7];
int id[1<<16|7],f[1<<16|7];
bool U[1<<17|7];
int fa[1<<17|7];
int now,ans;
inline int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
inline int nxt(){while (U[now]) now++;U[now]=1;return now;}
inline void uni(int x,int y){
	x=getfa(x),y=getfa(y);
	if (x!=y) ans--,fa[x]=y;
}
int main(){
	scanf("%d%d",&n,&m);
	REP(i,n){
		char t;getchar();
		REP(j,m/4){
			t=getchar();if ('A'<=t&&t<='Z') t=t-'A'+10;else t-='0';
			a[j<<2]=t>>3,a[j<<2|1]=(t>>2)&1,a[j<<2|2]=(t>>1)&1,a[j<<2|3]=t&1;
		}
		REP(j,m*2) U[j]=0;
		REP(j,m) U[f[j]]=1;now=1;
		REP(j,m*2) if (!U[j]) fa[j]=j;
		REP(j,m){
			if (a[j]){id[j]=nxt();ans++;}
			else id[j]=0;
		}
		REP(j,m) if (a[j]){
			if (j&&a[j-1]) uni(id[j-1],id[j]);
			if (p[j]) uni(f[j],id[j]);
		}
		REP(j,m) p[j]=a[j],f[j]=getfa(id[j]);
	}
	printf("%d\n",ans);
}/*
*/
