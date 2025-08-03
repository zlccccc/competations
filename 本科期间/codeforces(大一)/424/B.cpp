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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

inline int lowbit(int x){
	return x&-x;
}
int c[maxn];
int presum(int x){
	int ret=0;
	while (x){
		ret+=c[x];
		x-=lowbit(x);
	}
	return ret;
}
int sum(int l,int r){
	return presum(r)-presum(l-1);
}
void add(int x,int d){
	while (x<=100000){
		c[x]+=d;
		x+=lowbit(x);
	}
}
int a[maxn];
int n,now;
LL ans;
int i,j,k;
vector<int> V[maxn];
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]),V[a[i]].push_back(i);
	now=0;
	FOR(i,1,n) add(i,1);
	FOR(i,1,100000){
		j=0;
		while (j<V[i].size()&&V[i][j]<=now) j++;
		int t=j;
		while (j<V[i].size()){
//			printf("i=%d  1-> %d   %d\n",i,now,ans);
			if (now>V[i][j]){
				ans+=sum(now+1,n);
				ans+=sum(1,V[i][j]);
			}else{
				ans+=sum(now+1,V[i][j]);
			}
			now=V[i][j];
			add(V[i][j],-1);
//			printf("i=%d  1<= %d   %d\n",i,now,ans);
			j++;
		}
		REP(j,t){
//			printf("i=%d  2-> %d   %d\n",i,now,ans);
			if (now>V[i][j]){
				ans+=sum(now+1,n);
				ans+=sum(1,V[i][j]);
			}else{
				ans+=sum(now+1,V[i][j]);
			}
			now=V[i][j];
			add(V[i][j],-1);
//			printf("i=%d  2<= %d   %d\n",i,now,ans);
		}
	}
	printf("%I64d\n",ans);
}
/*
*/
