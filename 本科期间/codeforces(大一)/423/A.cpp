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
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

int n,m,len; 
int i,j,t;
char a[maxn],ans[maxn];
int b[maxn];
int fa[maxn];
int mx;
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
int main(){
	scanf("%d",&n);
	FOR(i,1,3e6) fa[i]=i;
	while(n--){
		scanf("%s",a);
		len=strlen(a);
		scanf("%d",&m);
		while(m--){
			scanf("%d",&t);
			for(j=getfa(t);j<t+len;j=fa[j]=getfa(j+1)) {
				ans[j]=a[j-t];
				if (j>mx) mx=j;
			}
		}
	}
	FOR(i,1,mx){
		if (ans[i]) putchar(ans[i]);
		else putchar('a');
	}
}
