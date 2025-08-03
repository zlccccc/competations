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
const LL maxn=5e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,k;
int i,j;
char s[maxn];
int l,r,mid;
bool mark[maxn];
int len; 
bool check(int x){
	memset(mark,0,1<<x);
	int i,now=0,o=(1<<x)-1,cnt=0;
	REP(i,x-1){
		now=now<<1|(s[i]-'0');
	}rep(i,x-1,len){
		now=(now<<1|(s[i]-'0'))&o;
//		printf("%d %x;%x\n",cnt,now,o);
		if (!mark[now]) cnt++;
		mark[now]=1;
		if (cnt==(1<<x)) return 1; 
	}return 0;
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%s",s);
		len=strlen(s);
		l=1;r=min(23,len);
		while (l+1<r){
			mid=(l+r)/2;
			if (check(mid)) l=mid;
			else r=mid;
		}printf("%d\n",r);
	}
}
/*
*/
