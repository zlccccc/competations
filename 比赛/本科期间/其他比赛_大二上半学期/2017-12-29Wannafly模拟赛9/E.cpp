#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
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

int n,m,i,j;
bool mark[maxn];
int p[maxn],tot;
map<pair<int,int>,int> MP;
int check(int x,int val){
//	if (MP[make_pair(x,val)]) return MP[make_pair(x,val)];
	if (x==2) return val/2;
	int ret=val/x;
	for (int i=0;p[i]<x;i++){
		ret-=check(p[i],val/x);
	}
//	return MP[make_pair(x,val)]=ret;
	return ret;
}
int main(){
	int x,y,now;
	FOR(i,2,100000) if (!mark[i]){
		p[tot++]=i;
		for (j=i+i;j<=100000;j+=i) mark[j]=1;
	}int t0=0;
//	REP(i,tot) printf("%d ",p[i]);
	while (~scanf("%d%d",&x,&y)) {
		if (y<=30){
			int l=0,r=1000000001;
			while (l+1<r){
				int mid=(l+r)/2;
				if (check(y,mid)<x) l=mid;
				else r=mid;
			}if (r==1000000001) puts("0");
			else printf("%d\n",r);
		}else{
			for (now=y;now<=1000000000;now+=y){
				for(i=0;p[i]<y&&p[i]<now/p[i];i++) if (now%p[i]==0) break;
				if (p[i]==y||now%p[i]!=0) x--;
				if (!x) break;
			}if (x) puts("0");
			else printf("%d",now);
		}
	}
}
/*
10000000 47
100000 97
*/
