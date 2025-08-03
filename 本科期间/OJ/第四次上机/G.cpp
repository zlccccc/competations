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
#include <functional>
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
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//ÑÓ³ÙÐÞ¸Ä 
int n,k;
int a[maxn],b[maxn],tot;
int i,j;
queue<pair<int,int> > Q;
int main(){
	int T;
	while (~scanf("%d%d",&n,&k)){
		tot=0;
		FOR(i,0,n) b[i]=INF;
		FOR(i,1,n) scanf("%d",&a[i]);
		while (Q.size()) Q.pop();
		FOR(i,1,n){
			if (Q.size()>=k){
				auto now=Q.front();
				b[now.first]=min(b[now.first],now.second);
				if (now.first==tot) tot++;
				Q.pop();
			}int pos=lower_bound(b,b+tot,a[i])-b;
			Q.push(make_pair(pos,a[i]));
//			printf("%d:\n",i);
//			REP(j,tot) printf("%d ",b[j]);puts("");
		}while (Q.size()){
			auto now=Q.front();
			b[now.first]=min(b[now.first],now.second);
			if (now.first==tot) tot++;
			Q.pop();
		}
//			printf("%d:\n",i);
//			REP(j,tot) printf("%d ",b[j]);puts("");
		printf("%d\n",tot);
	} 
}
/*
5 3
1 3 4 6 2
*/
