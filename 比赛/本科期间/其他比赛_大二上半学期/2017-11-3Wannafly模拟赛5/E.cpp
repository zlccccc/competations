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
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//Êú×Å¿¼ÂÇµÄ 
int n,m;
int i,j,k,t;
int val;
vector<int> H;
int a[maxn];
int ver[maxn],v[maxn],allv;//verÊú 
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]),H.push_back(a[i]);
	sort(H.begin(),H.end());H.erase(unique(H.begin(),H.end()),H.end());
	reverse(H.begin(),H.end());H.push_back(0);H.push_back(0);
	REP(k,H.size()-1){
		int h=H[k];
		i=1;
		while(i<=n){
			while (a[i]<h&&i<=n) i++;
			if (i>n) break;
			allv=0;
			for (j=i;a[j+1]>=h&&j+1<=n;j++) allv+=ver[j];allv+=ver[j];
			v[i]=min(j-i+1,allv+(H[k]-H[k+1]));
//			printf("change-%d %d allv=%d %d;%d %d\n",v[i],j-i+1,allv,allv+(H[k]-H[k+1]),H[k],H[k+1]);
			i=j+1;
		}
		FOR(i,1,n) ver[i]=v[i],v[i]=0;
//		FOR(i,1,n) printf("%d ",ver[i]);puts("");
	}
	printf("%d\n",ver[1]);
}
/*
6
1 5 3 3 5 1
*/
