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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

map<int,int> HASH;
int calc(int now){
	if (HASH.count(now)) return HASH[now];
	set<int> mex;
	int MX=0,i,j;
	REP(i,30) if (now&(1<<i)) MX=max(MX,i);
	FOR(i,1,MX){
		int down=0;
		REP(j,30) if (now&(1<<j)){
			if (j==i) continue;
			if (j>i) down|=1<<(j-i);
			else down|=1<<j;
		}
		mex.insert(calc(down));
	}
	int ret=0;
	while (mex.count(ret)) ret++;
	return HASH[now]=ret;
}
int cnt;
int n,k;
int i,j;
int ans;
int val[maxn];
map<int,int> MP;//val,pos
int main(){
	scanf("%d",&n);
	FOR(i,1,n){
		scanf("%d",&k); 
		for(j=2;j*j<=k;j++){
			int tot=0;
			while (k%j==0) k/=j,tot++;
			if (tot){
				if (!MP.count(j)) MP[j]=++cnt;
				val[MP[j]]|=1<<tot;
			}
		}if (k!=1){
			if (!MP.count(k)) MP[k]=++cnt;
			val[MP[k]]|=1<<1;
		}
	}
	FOR(i,1,cnt) ans^=calc(val[i]);
	if (ans) puts("Mojtaba");
	else puts("Arpa");
}
/*
*/
