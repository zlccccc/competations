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
inline LL powMM(LL a,LL b){
    LL ret=1;
    while (b){
        if (b&1) ret=ret*a%M;
        a=a*a%M;
        b>>=1;
    }
    return ret;
}

int n,m;
int use[maxn],deg[maxn];
vector<int> edge[maxn];
int i,j,k,now;
int u,v;
int main(){
	scanf("%d %d\n",&n,&m);
	REP(i,m) scanf("%d%d",&u,&v),deg[u]++,deg[v]++,edge[u].push_back(v),edge[v].push_back(u);
//	FOR(i,1,n) printf("%d ",deg[i]);puts("");
	for (int i = 1; i <= n; ++i) use[i] = false;
	int ans = 0;
	while (true) {
	  int mx = -1, u;
	    for (int i = 1; i <= n; ++i) {
	      if (use[i])
	          continue;
	        if (deg[i] >= mx) {
	          mx = deg[i];
	            u = i;
	        }
	    }
	    if (mx <= 0)
	      break;
	    ++ans;
	    use[u] = true;
	    for (int v:edge[u])
	      --deg[v];
//	    printf("%d ",u);
	}
	printf("%d\n",ans);
}
/*
*/

