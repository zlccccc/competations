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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k;
vector<int> edge[27];
int cnt[1<<20|7];
int a[1<<20|7][27];
int main(){
	scanf("%d%d",&n,&m);
	int u,v;
	while (m--) scanf("%d%d",&u,&v),edge[--u].push_back(--v);
	REP(i,(1<<n)) cnt[i]=cnt[i>>1]+(i&1);
	a[0][0]=1;
	REP(i,n){
		REP(k,(1<<n)) if (cnt[k]==i){
//			printf("%d,%d %d\n",k,cnt[k],i);
			for (int v:edge[i]) if (!((k>>v)&1)){
				(a[k|(1<<v)][i+1]+=a[k][i])%=M;
			}
		}
	}
//	REP(k,1<<n)
//		REP(i,n) printf("%d,%d:%d\n",k,i,a[k][i]);
	printf("%d\n",a[(1<<n)-1][n]);
}
/*
*/
