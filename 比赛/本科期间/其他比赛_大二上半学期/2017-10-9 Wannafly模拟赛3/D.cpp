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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

bool mark[maxn];
vector<int> edge[maxn];
bool no;
int F4,F3;
void dfs(int x,int fa){
	mark[x]=1;
	if (edge[x].size()>4) no=1;
	if (edge[x].size()==4) F4++;
	if (edge[x].size()==3) F3++;
	for (int v:edge[x]) if (v!=fa){
		if (mark[v]) return;
		dfs(v,x);
	}
}
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	int i;
	if (m!=n-1) return 0*puts("NotValid");
	FOR(i,1,m){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(1,0);
	if (no) return 0*puts("NotValid");
	FOR(i,1,n) if (!mark[i]) return 0*puts("NotValid");
	if (F4+F3>1) return 0*puts("NotValid"); 
	if (F4) return 0*puts("X");
	if (F3) return 0*puts("Y");
	puts("I");
}
/*
*/
